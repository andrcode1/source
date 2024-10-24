#include "App.h"
#include <wx/wx.h>
#include "MainFrame.h"

wxIMPLEMENT_APP(App);

bool App::OnInit() {
	MainFrame* mainFrame = new MainFrame("Calculator");
	mainFrame->SetClientSize(x_frame, y_frame);
	mainFrame->Center();
	mainFrame->Show();
	return true;
}
