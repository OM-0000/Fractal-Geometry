// Copyright (c) 2026 Ossama Mostafa
// MIT License

#include "BasicWindow.h"

void BasicWindow::open()
{
	if (closed)
	{
		POINT start;
		start.x = 0;
		start.y = 0;
		tb_topleft = start;
		closed = false;
	}
	
}
void BasicWindow::close()
{
	
	POINT closedloc;
	closedloc.x = -2000;
	closedloc.y = -2000;
	tb_topleft = closedloc;
	closed = true;
	CalculateLayout();
	
	
}

bool BasicWindow::setTitle(char* in_text, int size)
{
	if (size < 128) //128 is the max size of the title
	{
		for (int i = 0; i < size; i++)
		{
			title[i] = (WCHAR)in_text[i];
		}
		return true;
	}
	else
	{
		return false;
	}
}
BOOL BasicWindow::insideWindow(POINT pt)
{
	if (pt.x >= titlebar.left && pt.x <= titlebar.right && pt.y >= titlebar.top && pt.y <= clientarea.bottom)
	{
		return true;
	}
	else
	{
		return false;
	}
}

BOOL BasicWindow::insideCloseButton(POINT pt)
{
	if (pt.x >= close_button.left && pt.x <= close_button.right && pt.y >= close_button.top && pt.y <= close_button.bottom)
	{
		return true;
	}
	else
	{
		return false;
	}
}

BOOL BasicWindow::insideDragArea(POINT pt)
{
	if (pt.x >= dragbuffer.left && pt.x <= dragbuffer.right && pt.y >= dragbuffer.top && pt.y <= dragbuffer.bottom && !insideCloseButton(pt))
	{
		return true;
	}
	else
	{
		return false;
	}
}

BOOL BasicWindow::insideTitleBar(POINT pt)
{
	if (pt.x >= titlebar.left && pt.x <= titlebar.right && pt.y >= titlebar.top && pt.y <= titlebar.bottom && !insideCloseButton(pt))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void BasicWindow::setClearRgn(HRGN rgn)
{
	clear_rgn = rgn;
}