/***************************************************************
 * Name:      tessaApp.h
 * Purpose:   Defines Application Class
 * Author:    Matthew Wild (mwild1@gmail.com)
 * Created:   2007-04-19
 * Copyright: Matthew Wild (http://code.google.com/p/tessa)
 * License:
 **************************************************************/

#ifndef TESSAAPP_H
#define TESSAAPP_H

#include <wx/wxprec.h>

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "TessaCore.h"

class tessaApp : public wxApp
{
    private:
        TessaCoreThread* CoreThread;
	public:
		virtual bool OnInit();
};

#endif // tessaAPP_H
