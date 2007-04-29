/***************************************************************
 * Name:      tessaMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Matthew Wild (mwild1@gmail.com)
 * Created:   2007-04-19
 * Copyright: Matthew Wild (http://code.google.com/p/tessa)
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "tessaMain.h"

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*InternalHeaders(tessaRoster)
#include <wx/bitmap.h>
#include <wx/font.h>
#include <wx/fontenum.h>
#include <wx/fontmap.h>
#include <wx/image.h>
#include <wx/intl.h>
#include <wx/settings.h>
//*)

#include "TessaGUIServices.h"

//(*IdInit(tessaRoster)
const long tessaRoster::idMenuQuit = wxNewId();
const long tessaRoster::idMenuAbout = wxNewId();
const long tessaRoster::ID_ROSTERSTATUSBAR = wxNewId();

const long tessaRoster::idMenuStatusOffline = wxNewId();
const long tessaRoster::idMenuStatusOnline = wxNewId();
const long tessaRoster::idMenuStatusAway = wxNewId();
const long tessaRoster::idMenuStatusNA = wxNewId();
const long tessaRoster::idMenuStatusDND = wxNewId();
const long tessaRoster::idMenuStatusChat = wxNewId();

//*)

BEGIN_EVENT_TABLE(tessaRoster,wxFrame)
	//(*EventTable(tessaRoster)
	EVT_MENU    (tessaRoster::idMenuQuit, tessaRoster::OnQuit)
	EVT_COMMAND (wxID_CORETHREAD, TessaGUIServices::ContactStatusChanged, tessaRoster::SvcContactStatusChanged)
	//*)
END_EVENT_TABLE()

tessaRoster::tessaRoster(wxWindow* parent,wxWindowID id)
{
	Create(parent,id,_T("Tessa IM"),wxDefaultPosition,wxSize(200, 500),wxDEFAULT_FRAME_STYLE,_T("wxFrame"));
	StatusBar = new wxStatusBar(this,ID_ROSTERSTATUSBAR,0,_T("ID_ROSTERSTATUSBAR"));
	SetStatusBar(StatusBar);
	StatusBar->SetStatusText(_T("Offline"));

	// Menus

    MenuBar = new wxMenuBar;

    MainMenu = new wxMenu();
    StatusMenu = new wxMenu();

    MenuBar->Append(MainMenu, _T("Menu")); MenuBar->Append(StatusMenu, _T("Status"));

    MainMenu->Append(idMenuQuit, _T("E&xit"), _T("Disconnect, and exit Tessa"));

    StatusMenu->Append(idMenuStatusOffline, _T("Offline"));
    StatusMenu->Append(idMenuStatusOnline, _T("Online"));
    StatusMenu->Append(idMenuStatusAway, _T("Away"));
    StatusMenu->Append(idMenuStatusNA, _T("Not Available"));
    StatusMenu->Append(idMenuStatusDND, _T("Do Not Disturb"));
    StatusMenu->Append(idMenuStatusChat, _T("Free for a chat"));

    SetMenuBar(MenuBar);


    RosterList = new wxTreeCtrl(this, -1, wxPoint(0,0), GetClientSize(), wxTR_FULL_ROW_HIGHLIGHT|wxTR_NO_LINES|wxTR_HIDE_ROOT|wxTR_SINGLE);

    RosterRootNode = RosterList->AddRoot(_T("Roster"));
}

tessaRoster::~tessaRoster()
{
	//(*Destroy(tessaRoster)
	//*)
}

void tessaRoster::OnQuit(wxCommandEvent& event)
{
    Close();
}

void tessaRoster::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

// GUI Services

void tessaRoster::SvcContactStatusChanged(wxCommandEvent& event)
{
    printf("t%d\n", event.GetEventType());
    RosterList->AppendItem(RosterRootNode, event.GetString());
}
