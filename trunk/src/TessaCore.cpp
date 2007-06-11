
#include <wx/wx.h>

#include "TessaCore.h"
#include "TessaGUIServices.h"
#include "../bindings/gloox/TessaInterface.h"

void TessaLuaInterface(LuaInterface* Interface);

DEFINE_EVENT_TYPE(wxEVT_LUA_EVENT)

wxThread::ExitCode TessaCoreThread::Entry()
{
    return (wxThread::ExitCode)RunScript("scripts/core.lua");
}

void TessaCoreThread::PostEvent(int EventID, LuaTable* Data)
{
    wxCommandEvent evt(wxEVT_LUA_EVENT, OurID);
    LuaTable *dupData = new LuaTable(*Data);
    evt.SetInt(EventID);
    evt.SetString(::wxString((*dupData)["string"].GetString().c_str(), wxConvUTF8));
    evt.SetClientData((void*)dupData);
    wxPostEvent(GUIThread, evt);
}
