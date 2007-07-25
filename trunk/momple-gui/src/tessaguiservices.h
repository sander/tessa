/*
 * TessaGUIServices is a part of the Tessa IM client.
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

#ifndef TESSAGUISERVICES_H_INCLUDED
#define TESSAGUISERVICES_H_INCLUDED

// Events *raised* by the GUI
#define COREEVT_SETSTATUS "Events/GUI/SetStatus"

// Events *handled* by the GUI
DECLARE_EVENT_TYPE(wxEVT_LUA_EVENT, -1)

namespace TessaGUIServices
{
    enum
    {
        CoreError,
        UpdateContactStatus
    };
}

#endif // TESSAGUISERVICES_H_INCLUDED
