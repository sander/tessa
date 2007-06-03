#include "LuaInterface.h"

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

lua_State* L;

// This is GUI_PostEvent function in Lua
int lcPostEvent(lua_State* L)
{
    LuaInterface* IFObject = (LuaInterface*) lua_touserdata(L, lua_upvalueindex(1)); // Here we get the address of the interface
    CoreEventData Event;
    if(!lua_isnumber(L, 1) || !lua_istable(L, 2))
    {
        lua_pushboolean(L, false);// Return false (error) invalid types were passed
        return 1;
    }
    int id = lua_tonumber(L, 1);
    lua_getfield(L, 2, "contact");
    Event["contact"] = lua_tostring(L, -1);
    lua_getfield(L, 2, "string");
    Event["string"] = lua_tostring(L, -1);
    lua_getfield(L, 2, "status"); // Really should use lua_opt for this
    Event["status"] = (int)lua_tonumber(L, -1);
    IFObject->PostEvent(id, &Event);
    return 0;
}

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
