/***************************************************************
 * Name:      tessaApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Matthew Wild (mwild1@gmail.com)
 * Created:   2007-04-19
 * Copyright: Matthew Wild (http://code.google.com/p/tessa)
 * License:
 **************************************************************/

#ifdef WX_PRECOMP //
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "tessaApp.h"

//(*AppHeaders
#include "tessaMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(tessaApp);

bool tessaApp::OnInit()
{
	//(*AppInitialize
	bool wxsOK = true;
	wxInitAllImageHandlers();
	if ( wxsOK )
	{
	    tessaRoster* RosterWindow = new tessaRoster(NULL);
	    RosterWindow->Show();
	    SetTopWindow(RosterWindow);

	    // Now, initialise Lua thread
	    CoreThread = new TessaCoreThread(RosterWindow, wxID_CORETHREAD);

	}
	//*)
	return wxsOK;

}


