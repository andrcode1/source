#include "MainFrame.h"
#include "StandardCalculator.h"
#include <wx/wx.h>

using namespace std;

MainFrame::MainFrame(const wxString& title): wxFrame(nullptr, wxID_ANY, title), input(""), bracket_counter(0) {
	panel = new wxPanel(this);
	CreateUI();
}

enum IDs
{
	ID_BUTTON_C = 2,
	ID_BUTTON_BRACKETS = 3,
	ID_BUTTON_AC = 4,
	ID_BUTTON_DIVIDE = 5,
	ID_BUTTON_7 = 6,
	ID_BUTTON_8 = 7,
	ID_BUTTON_9 = 8,
	ID_BUTTON_MULTIPLY = 9,
	ID_BUTTON_4 = 10,
	ID_BUTTON_5 = 11,
	ID_BUTTON_6 = 12,
	ID_BUTTON_MINUS = 13,
	ID_BUTTON_1 = 14,
	ID_BUTTON_2 = 15,
	ID_BUTTON_3 = 16,
	ID_BUTTON_PLUS = 17,
	ID_BUTTON_00 = 18,
	ID_BUTTON_0 = 19,
	ID_BUTTON_DOT = 20,
	ID_BUTTON_EQUAL = 21,
	ID_BUTTON_BACKSPACE = 22,
	ID_BUTTON_MENU = 23,
	ID_BUTTON_HISTORY = 24
};

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
    EVT_BUTTON(ID_BUTTON_C, MainFrame::OnButtonClicked)
	EVT_BUTTON(ID_BUTTON_BRACKETS, MainFrame::OnButtonClicked)
	EVT_BUTTON(ID_BUTTON_AC, MainFrame::OnButtonClicked)
	EVT_BUTTON(ID_BUTTON_DIVIDE, MainFrame::OnButtonClicked)
	EVT_BUTTON(ID_BUTTON_7, MainFrame::OnButtonClicked)
	EVT_BUTTON(ID_BUTTON_8, MainFrame::OnButtonClicked)
	EVT_BUTTON(ID_BUTTON_9, MainFrame::OnButtonClicked)
	EVT_BUTTON(ID_BUTTON_MULTIPLY, MainFrame::OnButtonClicked)
	EVT_BUTTON(ID_BUTTON_4, MainFrame::OnButtonClicked)
	EVT_BUTTON(ID_BUTTON_5, MainFrame::OnButtonClicked)
	EVT_BUTTON(ID_BUTTON_6, MainFrame::OnButtonClicked)
	EVT_BUTTON(ID_BUTTON_MINUS, MainFrame::OnButtonClicked)
	EVT_BUTTON(ID_BUTTON_1, MainFrame::OnButtonClicked)
	EVT_BUTTON(ID_BUTTON_2, MainFrame::OnButtonClicked)
	EVT_BUTTON(ID_BUTTON_3, MainFrame::OnButtonClicked)
	EVT_BUTTON(ID_BUTTON_PLUS, MainFrame::OnButtonClicked)
	EVT_BUTTON(ID_BUTTON_00, MainFrame::OnButtonClicked)
	EVT_BUTTON(ID_BUTTON_0, MainFrame::OnButtonClicked)
	EVT_BUTTON(ID_BUTTON_DOT, MainFrame::OnButtonClicked)
	EVT_BUTTON(ID_BUTTON_EQUAL, MainFrame::OnButtonClicked)
	EVT_BUTTON(ID_BUTTON_BACKSPACE, MainFrame::OnButtonClicked)
	EVT_BUTTON(ID_BUTTON_MENU, MainFrame::OnButtonClicked)
	EVT_BUTTON(ID_BUTTON_HISTORY, MainFrame::OnButtonClicked)
wxEND_EVENT_TABLE()

void MainFrame::OnButtonClicked(wxCommandEvent& event)
{	
    wxButton* button = dynamic_cast<wxButton*>(event.GetEventObject());
    if (button)
    {
        wxString label = button->GetLabel();
		long insertionPoint = display_output->GetInsertionPoint();
		if (label == "AC")
		{ 
			display_output->Clear();
			display_input->Clear();
			bracket_counter = 0;
			input.clear();
		}
		else if (label == "C")
		{
			display_output->Clear();
			bracket_counter = 0;
			input.clear();
		}
		else if (label == "( )")
		{
			if (bracket_counter % 2 == 0)
			{
				display_output->WriteText("(");
				input.insert(insertionPoint, "(");
				bracket_counter++;
			}
			else
			{
				display_output->WriteText(")");
				input.insert(insertionPoint, ")");
				bracket_counter++;
			}
		}
		else if (label == "=")
		{	
			double result = CalculateExpression(input);
			display_output->Clear();
			display_input-> Clear();
			display_input->AppendText(input + " = ");

			input = to_string(result); // convert result to string

			input.erase(input.find_last_not_of('0') + 1, string::npos); // remove trailing zeros
			input.erase(input.find_last_not_of('.') + 1, string::npos);

			display_output->AppendText(input); // display result
			bracket_counter = 0;
		}
		else if (event.GetId() == ID_BUTTON_BACKSPACE)
		{
			if (insertionPoint > 0)
			{
				if ((input[insertionPoint - 1] == '(') or (input[insertionPoint - 1] == ')'))
				{
					bracket_counter--; // Check if we remove a bracket
				}
				input.erase(insertionPoint - 1, 1);
				display_output->Remove(insertionPoint - 1, insertionPoint);
				display_output->SetInsertionPoint(insertionPoint - 1);
			}
		}
		else if ((event.GetId() == ID_BUTTON_HISTORY) or (event.GetId() == ID_BUTTON_MENU))
		{
			display_input->Clear();
			display_input->AppendText("Coming soon!");
			input.clear();
		}
		else
		{
			display_output->WriteText(label);
			input.insert(insertionPoint, label.ToStdString());
			display_output->SetInsertionPoint(insertionPoint + label.Length());
		}
    }
}


void MainFrame::CreateUI()
{
    vbox = new wxBoxSizer(wxVERTICAL);

	panel->SetBackgroundColour(wxColour(25, 25, 25));

	wxFont font(20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);

	wxInitAllImageHandlers();
	wxBitmap Menu_image(wxT("D:\\source\\repos\\testGUI\\testGUI\\menuimage.png"), wxBITMAP_TYPE_PNG);
	wxBitmapButton* Menu = new wxBitmapButton(panel, ID_BUTTON_MENU, Menu_image, wxPoint(0,0), wxSize(45, 45), wxBORDER_SIMPLE);

	wxStaticText* standardText = new wxStaticText(panel, wxID_ANY, "Standard", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
	standardText->SetForegroundColour(wxColour(255, 255, 255));
	standardText->SetFont(font);

	wxBitmap history_image(wxT("D:\\source\\repos\\testGUI\\testGUI\\historyimage.png"), wxBITMAP_TYPE_PNG);
	wxBitmapButton* History = new wxBitmapButton(panel, ID_BUTTON_HISTORY, history_image, wxDefaultPosition, wxSize(45, 45), wxBORDER_SIMPLE);

	// Hbox for Menu button, Calculator Type and History button
	wxBoxSizer* hbox = new wxBoxSizer(wxHORIZONTAL);
	hbox->Add(Menu, 0, wxALIGN_LEFT | wxALL, 10);
	hbox->AddStretchSpacer(1); // Add a stretchable space
	hbox->Add(standardText, 0, wxALIGN_CENTER_VERTICAL | wxALL, 10);
	hbox->AddStretchSpacer(1); // Add a stretchable space
	hbox->Add(History, 0, wxALIGN_CENTER_VERTICAL | wxALL, 10);

	vbox->Add(hbox, 0, wxEXPAND | wxALL, 10);

    display_input = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(425, 50), wxTE_RIGHT | wxTE_READONLY | wxBORDER_NONE);
	display_output = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(425, 75), wxTE_RIGHT | wxTE_READONLY | wxBORDER_NONE);

	display_input->SetFont(font);
	display_output->SetFont(font);

	display_input->SetBackgroundColour(wxColour(25, 25, 25));
	display_input->SetForegroundColour(wxColour(255, 255, 255));
	display_output->SetBackgroundColour(wxColour(25, 25, 25));
	display_output->SetForegroundColour(wxColour(255, 255, 255));

	vbox->Add(display_input, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);
    vbox->Add(display_output, 0, wxEXPAND | wxLEFT | wxRIGHT, 10);

    wxBitmap backspace_image(wxT("D:\\source\\repos\\testGUI\\testGUI\\backspace1.png"), wxBITMAP_TYPE_PNG);

    wxBitmapButton* backspace = new wxBitmapButton(panel, ID_BUTTON_BACKSPACE, backspace_image, wxDefaultPosition, wxSize(80, 50), wxBORDER_NONE);
	backspace->SetBackgroundColour(wxColour(25, 25, 25));
    vbox->Add(backspace, 0, wxALIGN_RIGHT | wxRIGHT, 10);
	backspace->Bind(wxEVT_BUTTON, &MainFrame::OnButtonClicked, this);

    gridSizer = new wxGridSizer(5, 4, 5, 5);

	wxString buttons[] = {"C", "( )", "AC", "/", "7", "8", "9", "*", "4", "5", "6", "-", "1", "2", "3", "+", "00", "0", ".", "="};
	int ids[] = { ID_BUTTON_C, ID_BUTTON_BRACKETS, ID_BUTTON_AC, ID_BUTTON_DIVIDE,
			  ID_BUTTON_7, ID_BUTTON_8, ID_BUTTON_9, ID_BUTTON_MULTIPLY,
			  ID_BUTTON_4, ID_BUTTON_5, ID_BUTTON_6, ID_BUTTON_MINUS,
			  ID_BUTTON_1, ID_BUTTON_2, ID_BUTTON_3, ID_BUTTON_PLUS,
			  ID_BUTTON_00, ID_BUTTON_0, ID_BUTTON_DOT, ID_BUTTON_EQUAL };
	for (size_t i = 0; i < sizeof(buttons) / sizeof(buttons[0]); ++i)
	{
		wxButton* button = new wxButton(panel, ids[i], buttons[i], wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE);
		button->SetBackgroundColour(wxColour(25, 25, 25));
		button->SetBackgroundColour(wxColour(255, 140, 0));
		button->SetForegroundColour(wxColour(255, 255, 255));

		wxFont font = button->GetFont();
		font.SetWeight(wxFONTWEIGHT_BOLD);
		font.SetPointSize(15);
		button->SetFont(font);

		gridSizer->Add(button, 0, wxEXPAND);
		button->Bind(wxEVT_BUTTON, &MainFrame::OnButtonClicked, this);
	}

    vbox->Add(gridSizer, 1, wxEXPAND | wxALL, 10);
    panel->SetSizer(vbox);
}