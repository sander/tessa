/*
 * luathread.cpp is a part of the Momple frontend to Tessa.
 * Copyright (C) 2007  Sander Dijkhuis
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

#include "luathread.h"

#include <QtCore>

int LuaThread::putLuaToSleep(lua_State *lL) {
  unsigned long msecs = (unsigned long) lua_tonumber(lL, 1);
  lt->msleep(msecs);
  return 0;
}

void LuaThread::run() {
  L = luaL_newstate();
  luaL_openlibs(L);

  lua_register(L, "sleep", putLuaToSleep);

  if(luaL_dofile(L, "scripts/core.lua")) {
    qDebug() << "Unrecoverable error in Tessa core script!";
    qDebug() << "  Error:" << lua_tostring(L, -1);
  }

  exec();
}
