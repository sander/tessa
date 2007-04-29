
#include <wx/wx.h>

#include "TessaCore.h"
#include "TessaGUIServices.h"

void TessaLuaInterface(LuaInterface* Interface);

wxThread::ExitCode TessaCoreThread::Entry()
{
    RunScript("scripts/core.lua");
}

void TessaCoreThread::PostEvent(int EventID, CoreEventData* Data)
{
    wxCommandEvent evt(EventID, OurID);
    evt.SetString(::wxString(Data->string, wxConvUTF8));
    wxPostEvent(GUIThread, evt);
}
