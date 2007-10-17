#include "TessaSRMM.h"


BEGIN_EVENT_TABLE(TessaConversation, wxWindow)
  EVT_SIZE    (           TessaConversation::OnSize)
END_EVENT_TABLE()


TessaConversation::TessaConversation(wxWindow *parent, wxWindowID id)
{
    // Create frame window
    wxWindow::Create((wxWindow*)parent,id, wxDefaultPosition, parent->GetClientSize(),wxDEFAULT_FRAME_STYLE,_T("Conversation"));

    // Create splitter
    m_Splitter.Create(this, -1, wxPoint(0,0), GetClientSize(), wxSP_3D, _T("ConversationSplit"));


    m_Splitter.Show();



    // Create sub-windows
    m_MessageLog.Create(&m_Splitter, -1, _T("Messages"), wxPoint(0,0), wxSize(GetClientSize().x, 100), wxTE_MULTILINE);
    m_InputArea.Create(&m_Splitter, -1, _T("Hello!"), wxPoint(0,0), wxSize(GetClientSize().x, 100), wxTE_MULTILINE);

    m_Splitter.SplitHorizontally(&m_MessageLog, &m_InputArea, -100);

    m_Splitter.Show();

}

void TessaConversation::OnSize(wxSizeEvent& evt)
{
    m_Splitter.SetSize(evt.GetSize());
}


int TessaSRMMSystem::NewConversation(wxString Contact, wxString PreferredContainer)
{
    TessaContainer* cont = new TessaContainer(Contact);
    TessaConversation* conv = new TessaConversation(cont, -1);
    cont->Show();
    conv->Show();
    Conversations[Contact] = conv;
    Containers[PreferredContainer] = cont;
    return 0;
}
