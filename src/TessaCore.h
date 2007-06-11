#ifndef TESSACORE_H_INCLUDED
#define TESSACORE_H_INCLUDED

#include <wx/wx.h>
#include "LuaInterface.h"

class TessaCoreThread : wxThread, LuaInterface
{
    public:
        TessaCoreThread(wxEvtHandler* EventDestination, int id)
        {
            GUIThread = EventDestination;
            OurID = id;
           Create();
           Run();
        };
        ~TessaCoreThread() {};

    private:
        wxEvtHandler* GUIThread;
        int OurID;
        virtual ExitCode Entry();
    public:
        void PostEvent(int EventID, LuaTable* Data);
};

#define wxID_CORETHREAD (wxID_HIGHEST + 1)



#endif // TESSACORE_H_INCLUDED
