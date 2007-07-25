#include "luathread.h"

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include <QtCore>

extern LuaThread *lt;

int lcPostEvent(lua_State* L) {
  // This is GUI_postEvent function in Lua, used to send the GUI messages

  LuaTable Event;

  if(!lua_isnumber(L, 1) || !lua_istable(L, 2)) {
    qDebug() << "Invalid parameters passed to GUI_postEvent()";

    // Return false (error) invalid types were passed
    lua_pushboolean(L, false);

    return 1;
  }
  int id = (int)lua_tonumber(L, 1);
  lua_getfield(L, 2, "contact");
  Event["contact"] = (char*)lua_tostring(L, -1);
  lua_getfield(L, 2, "string");
  Event["string"] = (char*)lua_tostring(L, -1);
  lua_getfield(L, 2, "status"); // Really should use lua_opt for this
  Event["status"] = (int)lua_tonumber(L, -1);
  printf("Posting event %d to GUI...\n", id);
  lt->postEvent(id, &Event);
  return 0;
}

// Lua uses this to retrieve GUI events
int lcGetGUIEvent(lua_State* L) {
  if (lt->queueIsEmpty())
    return 0;

  LuaEvent event = lt->dequeueEvent();

  lua_pushstring(L, event.first.c_str());

  // Push the map, as a Lua table
  // Create a new table that will be passed to the event handlers
  lua_newtable(L); 
  LuaTable::const_iterator it;
  for (it=event.second.constBegin(); it != event.second.constEnd(); it++) {
    std::string name = it.key();
    LuaValue value = it.value();
    switch(value.GetType()) {
      case LuaValue::NUMBER:
        lua_pushnumber(L, value.GetNumber());
        break;
      case LuaValue::STRING:
        lua_pushstring(L, value.GetString().c_str());
        break;
      case LuaValue::BOOLEAN:
        lua_pushboolean(L, value.GetBool());
        break;
      default:
        continue;
    }
    lua_setfield(L, -2, name.c_str());
  }
  return 2;
}

LuaThread::LuaThread() {
  eventQueue = new QQueue<LuaEvent>;
}

void LuaThread::run() {
  exec();
}

void LuaThread::enqueueEvent(LuaEvent event) {
  QMutexLocker locker(&mutex);
  eventQueue->enqueue(event);
}

LuaEvent LuaThread::dequeueEvent() {
  QMutexLocker locker(&mutex);
  return eventQueue->dequeue();
}

bool LuaThread::queueIsEmpty() {
  return eventQueue->isEmpty();
}

void LuaThread::runScript(char *fileName) {
  L = luaL_newstate();
  luaL_openlibs(L);

  lua_pushlightuserdata(L, this);
  lua_pushcclosure(L, lcPostEvent, 1);
  lua_setglobal(L, "GUI_PostEvent");
  lua_pushnumber(L, (long)FireLuaEvent);
  lua_setglobal(L, "FireLuaEvent");

  lua_register(L, "GUI_GetEvent", lcGetGUIEvent);

  if (luaL_dofile(L, fileName)) {
    qDebug() << "Unrecoverable error in Tessa core script!\n\tError: "
             << lua_tostring(L, -1);
    LuaTable errorData;
    errorData["string"] = lua_tostring(L, -1);
    //postEvent(TessaGUIServices::CoreError, &errorData);
  }
}

// This function triggers a core event in Lua. It takes a std::map that will
// be converted to a Lua table
int FireLuaEvent(char* name, const LuaTable* m) {
  lua_State *L = lt->L;

  lua_getglobal(L, "events");
  lua_getfield(L, -1, "fire");

  lua_getglobal(L, "events");
  lua_pushstring(L, name);

  if (m) {
    // Create a new table that will be passed to the event handlers
    lua_newtable(L);

    LuaTable::const_iterator it;
    for (it=m->begin(); it != m->end(); it++) {
      std::string name = it.key();
      LuaValue value = it.value();

      switch(value.GetType()) {
        case LuaValue::NUMBER:
          lua_pushnumber(L, value.GetNumber());
          break;
        case LuaValue::STRING:
          lua_pushstring(L, value.GetString().c_str());
          break;
        case LuaValue::BOOLEAN:
          lua_pushboolean(L, value.GetBool());
          break;
        default:
          continue;
      }

      lua_setfield(L, -2, name.c_str());
    }
  } else {
    lua_pushnil(L);
  }

  if(lua_pcall(L, 3, 0, 0)) {
    qDebug() << lua_tostring(L, -1);
    lua_pop(L, 1);
  }
  lua_pop(L, 1);

  return 0;
}

// Pushes a GUI event to Lua
void LuaThread::postLuaEvent(std::string name, LuaTable& data) {
  LuaEvent event;
  event.first = name;
  event.second = data;
  lt->enqueueEvent(event);
}
