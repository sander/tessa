#include <map>
#include <wx/wx.h>
#include <wx/frame.h>
#include <wx/splitter.h>
#include <wx/window.h>
#include <wx/textctrl.h>



class TessaContainer : public wxFrame
{
    private:
    wxString m_Name;

    public:
    TessaContainer(wxString& Name) : wxFrame(NULL, -1, Name + _T(" - Tessa"))
    {
        m_Name = Name;
    }
    //~TessaContainer();

    private:
    wxString m_name;
    // Child

};

class TessaConversation : public wxWindow
{
    public:
    TessaConversation(wxWindow *parent, wxWindowID id);
    // ~TessaConversation();

    void OnSize(wxSizeEvent& evt);

    private:
     TessaContainer* m_ParentContainer;

    wxSplitterWindow m_Splitter;
    wxTextCtrl m_MessageLog;
    wxTextCtrl m_InputArea;

    DECLARE_EVENT_TABLE()
};

class TessaSRMMSystem
{
    private:
    std::map<wxString, TessaContainer*> Containers;
    std::map<wxString, TessaConversation*> Conversations;

    bool m_GlobalTabs;

    public:
    bool SetTabs(bool fEnableTabs)
    {
        return m_GlobalTabs = fEnableTabs;
    }

    int NewConversation(wxString Contact, wxString PreferredContainer);
    int AddMessageToConversation(wxString Contact, wxString Message, bool ShowNick = true);
    int SetConversationContainer(wxString Contact);
    int CloseConversation(wxString Contact);
};

