/*
 * LuaInterface is Tessa's C++ interface to its Lua scripts.
 * Copyright (C) 2007  Matthew Wild
 * Modified by Sander Dijkhuis.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef LUAINTERFACE_H
#define LUAINTERFACE_H

extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}
#include "tessaguiservices.h"

#include <map>
#include <string>
#include <gloox/TessaInterface.h>

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

#endif
