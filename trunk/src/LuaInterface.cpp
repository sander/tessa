#include "LuaInterface.h"

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include <queue>

lua_State* L;
static std::queue<std::pair<std::string, LuaTable> > MessageQueue; // A queue of events waiting to be passed to Lua

wxCriticalSection csMessageQueue;


// This is GUI_PostEvent function in Lua, used to send the GUI messages
int lcPostEvent(lua_State* L)
{
    LuaInterface* IFObject = (LuaInterface*) lua_touserdata(L, lua_upvalueindex(1)); // Here we get the address of the interface
    LuaTable Event;
    if(!lua_isnumber(L, 1) || !lua_istable(L, 2))
    {
        printf("Invalid parameters passed to GUI_PostEvent()\n");
        lua_pushboolean(L, false);// Return false (error) invalid types were passed
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
    IFObject->PostEvent(id, &Event);
    return 0;
}

// This function triggers a core event in Lua. It takes a std::map that will be converted to a Lua table
int FireLuaEvent(char* name, const std::map<std::string, LuaValue>* m)
{
    lua_getglobal(L, "events");
    lua_getfield(L, -1, "fire");

    lua_getglobal(L, "events");
    lua_pushstring(L, name);

    if(m)
    {
        lua_newtable(L); // Create a new table that will be passed to the event handlers

        std::map<std::string, LuaValue>::const_iterator it;
        for (it=m->begin(); it != m->end(); it++)
        {
            std::string name = (*it).first;
            LuaValue value = (*it).second;

            switch(value.GetType())
            {
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
    }
    else
    {
        lua_pushnil(L);
    }

    if(lua_pcall(L, 3, 0, 0))
    {
        printf("%s\n", lua_tostring(L, -1));
        lua_pop(L, 1);
    }
    lua_pop(L, 1);

    return 0;
}


// Pushes a GUI event to Lua
void PostLuaEvent(std::string name, LuaTable& data)
{
    std::pair<std::string, LuaTable> event;

    event.first = name;
    event.second = data;
    csMessageQueue.Enter();
    MessageQueue.push(event);
    csMessageQueue.Leave();
}


// Lua uses this to retrieve GUI events
int lcGetGUIEvent(lua_State* L)
{
    if(MessageQueue.empty())
        return 0;

    std::pair<std::string, LuaTable> event;

    csMessageQueue.Enter();
    event = MessageQueue.front();
    csMessageQueue.Leave();

    lua_pushstring(L, event.first.c_str());

    // Push the map, as a Lua table
    lua_newtable(L); // Create a new table that will be passed to the event handlers
    LuaTable::const_iterator it;
    for (it=event.second.begin(); it != event.second.end(); it++)
    {
        std::string name = (*it).first;
        LuaValue value = (*it).second;
        switch(value.GetType())
        {
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


int LuaInterface::RunScript(char* fn)
{
    ::L = luaL_newstate();
    luaL_openlibs(L);

    lua_pushlightuserdata(L, this);
    lua_pushcclosure(L, lcPostEvent, 1);
    lua_setglobal(L, "GUI_PostEvent");
    lua_pushnumber(L, (int)FireLuaEvent);
    lua_setglobal(L, "FireLuaEvent");

    lua_register(L, "GUI_GetEvent", lcGetGUIEvent);

    if(luaL_dofile(L, fn))
    {
        printf("Unrecoverable error in Tessa core script!\n\tError: %s\n", lua_tostring(L, -1));
        LuaTable ErrorData;
        ErrorData["string"] = lua_tostring(L, -1);
        PostEvent(TessaGUIServices::CoreError, &ErrorData);
    }
    return 0;
}
