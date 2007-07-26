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

// Used to represent a Lua table
typedef std::map<std::string, LuaValue> LuaTable;

// For Lua to post events to the GUI
int lcPostEvent(lua_State* L);
// For Lua to retrieve GUI events
void PostLuaEvent(std::string name, LuaTable& data);

// Posting events to Lua...
int FireLuaEvent(char* name, const std::map<std::string, LuaValue>* m); // Must only be called from main thread
void PostLuaEvent(std::string name, LuaTable& data); // Thread-safe


extern lua_State* L;

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
        virtual void PostEvent(int EventID, LuaTable* data) = 0;
};
#endif // LUAINTERFACE_H_INCLUDED
