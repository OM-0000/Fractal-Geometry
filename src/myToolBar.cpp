// Copyright (c) 2026 Ossama Mostafa
// MIT License

#include "myToolBar.h"

void myToolBar::calculateLayout()
{
	//Only need to call this if the tool bar moves and the buttons need to be moved with it.
	int dx = 0;
	int dy = 0;
	int tb_width = brc.right - brc.left;
	int tb_height = brc.bottom - brc.top;
	int numButtons = buttons.size();
	for (int i = 0; i < numButtons; i++)
	{
		buttons[i].topleft.x = brc.left + dx;
		buttons[i].topleft.y = brc.top + dy;
		if (horozontal_layout)
		{
			buttons[i].width = tb_width / numButtons - padding;
			buttons[i].height = tb_height;
			dx += buttons[i].width + padding;
		}
		else
		{
			buttons[i].width = tb_width;
			buttons[i].height = tb_height / numButtons - padding;
			dy += buttons[i].height + padding;
		}
	}

}

void myToolBar::Draw(HDC hdc)
{
	for (int i = 0; i < buttons.size(); i++)
	{
		buttons[i].Draw(hdc);
	}

	HPEN blkPen = CreatePen(PS_SOLID, 2, COLORREF(0x000000));
	SelectObject(hdc, blkPen);
	MoveToEx(hdc, brc.left, brc.bottom, NULL);
	LineTo(hdc, brc.right, brc.bottom);
	DeleteObject(blkPen);
}

void myToolBar::processClick(POINT pt)
{
	for (int i = 0; i < buttons.size(); i++)
	{
		buttons[i].processClick(pt);
	}
}

myToolBar::myToolBar(RECT boundary)
{
	brc.left = boundary.left;
	brc.right = boundary.right;
	brc.top = boundary.top;
	brc.bottom = boundary.bottom;
	horozontal_layout = true;
	padding = 0;
}

void myToolBar::insertButton_horo(int width, int height, char* _btn_label, int _label_size, COLORREF _bcolor, COLORREF _tColor)
{
	//new button will be insert to the right of the previous one
	POINT btn_loc;
	int lastidx = buttons.size() - 1;
	if (lastidx < 0)
	{
		btn_loc.x = brc.left;
		btn_loc.y = brc.top;
	}
	else
	{
		btn_loc.x = buttons[lastidx].topleft.x + buttons[lastidx].width;
		btn_loc.y = brc.top;
	}
	myButton nButton(btn_loc, width, height, _btn_label, _label_size, _bcolor, _tColor);
	buttons.push_back(nButton);
}

void myToolBar::insertButton_vert(int width, int height, char* _btn_label, int _label_size, COLORREF _bcolor, COLORREF _tColor)
{
	//new button will be inserted below the previous one
	POINT btn_loc;
	int lastidx = buttons.size() - 1;
	if (lastidx < 0)
	{
		btn_loc.x = brc.left;
		btn_loc.y = brc.top;
	}
	else
	{
		btn_loc.x = brc.left;
		btn_loc.y = buttons[lastidx].topleft.y + buttons[lastidx].height;

	}
	myButton nButton(btn_loc, width, height, _btn_label, _label_size, _bcolor, _tColor);
	buttons.push_back(nButton);
}
