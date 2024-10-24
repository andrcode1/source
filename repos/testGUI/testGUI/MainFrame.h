#pragma once
#include <wx/wx.h>
#include "App.h"

using namespace std;

class MainFrame : public wxFrame
{
public:
	MainFrame(const wxString& title);
private:
	void OnButtonClicked(wxCommandEvent& event);
	void CreateUI();

	wxPanel* panel;
	wxTextCtrl* display_input;
	wxTextCtrl* display_output;
	wxBoxSizer* vbox;
	wxGridSizer* gridSizer;

	string input;
	int bracket_counter;

	wxDECLARE_EVENT_TABLE();
};