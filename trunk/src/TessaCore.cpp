
#include <wx/wx.h>

#include "TessaCore.h"
#include "TessaGUIServices.h"

void TessaLuaInterface(LuaInterface* Interface);

wxThread::ExitCode TessaCoreThread::Entry()
{
    wxCommandEvent evt(TessaGUIServices::ContactStatusChanged, OurID);
    evt.SetString(_T("TobiasFar!"));
    wxPostEvent(GUIThread, evt);
    evt.SetString(_T("niekie2!"));
    wxPostEvent(GUIThread, evt);
    RunScript("scripts/core.lua");
    while(1) {};
}

void TessaCoreThread::PostEvent(int EventID, CoreEventData* Data)
{
    wxCommandEvent evt(EventID, OurID);
    evt.SetString(::wxString(Data->string, wxConvUTF8));
    wxPostEvent(GUIThread, evt);
}
