
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
    CoreEventData *dupData = new CoreEventData(*Data);
    evt.SetString(::wxString(dupData["string"], wxConvUTF8));
    evt.SetClientData((void*)dupData);
    wxPostEvent(GUIThread, evt);
}
