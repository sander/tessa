/***************************************************************
 * Name:      tessaMain.h
 * Purpose:   Defines Application Frame
 * Author:    Matthew Wild (mwild1@gmail.com)
 * Created:   2007-04-19
 * Copyright: Matthew Wild (http://code.google.com/p/tessa)
 * License:
 **************************************************************/

#ifndef TESSAMAIN_H
#define TESSAMAIN_H

#include "tessaApp.h"

//(*Headers(tessaRoster)
#include <wx/frame.h>
#include <wx/menu.h>
#include <wx/statusbr.h>
#include <wx/treectrl.h>
//*)

class tessaRoster: public wxFrame
{
	public:

		tessaRoster(wxWindow* parent,wxWindowID id = -1);
		virtual ~tessaRoster();

	private:

		//(*Handlers(tessaRoster)
		void OnQuit(wxCommandEvent& event);
		void OnAbout(wxCommandEvent& event);
		void SvcContactStatusChanged(wxCommandEvent& event);
		//*)

		//(*Identifiers(tessaRoster)
		static const long idMenuQuit;
		static const long idMenuAbout;
		static const long ID_ROSTERSTATUSBAR;
		static const long idMenuStatusOffline;
        static const long idMenuStatusOnline;
        static const long idMenuStatusAway;
        static const long idMenuStatusNA;
        static const long idMenuStatusDND;
        static const long idMenuStatusChat;

		//*)

		//(*Declarations(tessaRoster)
		wxTreeCtrl* RosterList;
		wxMenuBar* MenuBar;
		wxStatusBar* StatusBar;

		wxMenu *MainMenu, *StatusMenu;

		wxTreeItemId RosterRootNode;
		//*)

		DECLARE_EVENT_TABLE()
};

#endif // TESSAMAIN_H
