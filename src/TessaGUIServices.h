#ifndef TESSAGUISERVICES_H_INCLUDED
#define TESSAGUISERVICES_H_INCLUDED

#include <wx/wx.h>

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
