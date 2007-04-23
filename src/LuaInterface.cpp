#include "LuaInterface.h"

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

int lcPostEvent(lua_State* L)
{
    LuaInterface* IFObject = (LuaInterface*) lua_touserdata(L, lua_upvalueindex(1));
    CoreEventData Event;
    if(!lua_isnumber(L, 1) || !lua_istable(L, 2))
    {
        lua_pushboolean(L, false);
        return 1;
    }
    int id = lua_tonumber(L, 1);
    lua_getfield(L, 2, "contact");
    Event.contact = lua_tostring(L, -1);
    lua_getfield(L, 2, "string");
    Event.string = lua_tostring(L, -1);
    lua_getfield(L, 2, "status"); // Really should use lua_opt for this
    Event.status = lua_tonumber(L, -1);
    IFObject->PostEvent(id, &Event);
    return 0;
}
