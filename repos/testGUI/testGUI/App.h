#pragma once
#include <wx/wx.h>

class App : public wxApp 
{
public:

	static const int x_frame = 425;
	static const int y_frame = 600;
	bool OnInit();
};

