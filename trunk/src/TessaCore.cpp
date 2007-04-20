
#include <wx/wx.h>

#include "TessaCore.h"
#include "TessaGUIServices.h"


wxThread::ExitCode TessaCoreThread::Entry()
{
    wxCommandEvent evt(TessaGUIServices::ContactStatusChanged, OurID);
    evt.SetString(_T("TobiasFar!"));
    wxPostEvent(GUIThread, evt);
    while(1) {};
}
