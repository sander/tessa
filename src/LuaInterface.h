#ifndef LUAINTERFACE_H_INCLUDED
#define LUAINTERFACE_H_INCLUDED

extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}
#include "TessaGUIServices.h"

#include <map>
#include <string>
//#include <gloox/TessaInterface.h>
#include "../bindings/gloox/TessaInterface.h"

int lcPostEvent(lua_State* L);
int FireLuaEvent(char* name, const std::map<std::string, LuaValue>* m);

extern lua_State* L;

typedef std::map<std::string, LuaValue> CoreEventData;

class LuaInterface
{
    public:

        LuaInterface()
        {
        }
        virtual ~LuaInterface()
        {
        }
    protected:
        int RunScript(char* fn)
        {
            ::L = luaL_newstate();
            luaL_openlibs(L);

            lua_pushlightuserdata(L, this);
            lua_pushcclosure(L, lcPostEvent, 1);
            lua_setglobal(L, "GUI_PostEvent");
            printf("FLE: %p, %d\n", FireLuaEvent, FireLuaEvent);
            lua_pushnumber(L, (int)FireLuaEvent);
            lua_setglobal(L, "FireLuaEvent");

            if(luaL_dofile(L, fn))
            {
                printf("Unrecoverable error in Tessa core script!\n\tError: %s\n", lua_tostring(L, -1));
                CoreEventData ErrorData;
                ErrorData["string"] = lua_tostring(L, -1);
                PostEvent(TessaGUIServices::CoreError, &ErrorData);
            }
            return 0;
        }
    public:
        virtual void PostEvent(int EventID, CoreEventData* data) = 0;
};
#endif // LUAINTERFACE_H_INCLUDED
