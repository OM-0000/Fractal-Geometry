// Copyright (c) 2026 Ossama Mostafa
// MIT License

#pragma once
#include <Windows.h>
class BasicWindow
{
protected:
	RECT titlebar;
	RECT clientarea;
	RECT close_button;
	RECT dragbuffer;
	RECT bottom_display;
	HRGN clear_rgn; //the part of the window that isn't covered.
	int drag_x; //the distance from the left of the titlebar to the point where the drag event was initiated.
	int drag_y;
public:
	WCHAR title[128];
	POINT tb_topleft;// title bar top left corner
	//POINT cl_topleft; // client area top left
	int cl_width;
	int cl_height;
	COLORREF tb_col;
	COLORREF cl_col;

	//~BasicWindow();
	virtual void CalculateLayout() = 0;

	bool closed;
	bool close_override;
	bool m_dragging;

	bool selected;


	void open();
	void close();
	bool setTitle(char* in_text, int size);

	BOOL insideWindow(POINT pt);
	BOOL insideCloseButton(POINT pt);
	BOOL insideDragArea(POINT pt);
	BOOL insideTitleBar(POINT pt);

	void setClearRgn(HRGN rgn);
};

