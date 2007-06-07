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
        int RunScript(char* fn);
    public:
        virtual void PostEvent(int EventID, CoreEventData* data) = 0;
};
#endif // LUAINTERFACE_H_INCLUDED
