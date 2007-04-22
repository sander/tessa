#ifndef LUAINTERFACE_H_INCLUDED
#define LUAINTERFACE_H_INCLUDED

extern "C" {
#include <lua5.1/lua.h>
#include <lua5.1/lauxlib.h>
#include <lua5.1/lualib.h>
}
#include "TessaGUIServices.h"

int lcPostEvent(lua_State* L);

typedef struct
{
    const char* contact; // Contact's UID (NOT JID!!!)
    int status;
    const char* string;

} CoreEventData;

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
            lua_State* L = luaL_newstate();
            luaL_openlibs(L);

            lua_pushlightuserdata(L, this);
            lua_pushcclosure(L, lcPostEvent, 1);
            lua_setglobal(L, "GUI_PostEvent");

            if(luaL_dofile(L, fn))
            {
                printf("Unrecoverable error in Tessa core script!\n\tError: %s\n", lua_tostring(L, -1));
                CoreEventData ErrorData = { NULL, 0, lua_tostring(L, -1) };
                PostEvent(TessaGUIServices::CoreError, &ErrorData);
            }
            return 0;
        }
    public:
        virtual void PostEvent(int EventID, CoreEventData* data) = 0;
};
#endif // LUAINTERFACE_H_INCLUDED
