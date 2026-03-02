// Copyright (c) 2026 Ossama Mostafa
// MIT License

#include "myButton.h"


myButton::myButton(POINT _topleft, int _width, int _height, char* _label, int lbl_size, COLORREF _bcolor, COLORREF _tColor)
{
	topleft = _topleft;
	width = _width;
	height = _height;
	btnColor = _bcolor;
	textColor = _tColor;
	setLabel(_label, lbl_size);
	buttonState = 0;
}
BOOL myButton::inButton(POINT pt)
{
	if (pt.x >= brc.left && pt.x <= brc.right && pt.y >= brc.top && pt.y <= brc.bottom)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void myButton::toggleButton()
{
	buttonState = (buttonState + 1) % 2;
	if (buttonState)
	{
		darkenButton = 1;
	}
}
void myButton::processClick(POINT pt)
{
	if (inButton(pt))
	{
		toggleButton();
	}
}

void myButton::Draw(HDC hdc)
{
	CalculateRect();
	COLORREF currColor = btnColor;
	if (darkenButton > 0 && darkenButton < 5)
	{
		currColor /= 2;
		darkenButton = (darkenButton + 1) % 5;
	}
	HBRUSH btnBrush = CreateSolidBrush(currColor);
	FillRect(hdc, &brc, btnBrush);
	DeleteObject(btnBrush);
	HBRUSH blackBrush = CreateSolidBrush(COLORREF(0x000000));
	FrameRect(hdc, &brc, blackBrush);
	DeleteObject(blackBrush);
	SetBkColor(hdc, currColor);
	SetTextColor(hdc, textColor);
	DrawText(hdc, label, -1, &brc, DT_LEFT);
}
void myButton::CalculateRect()
{
	brc.left = topleft.x;
	brc.right = topleft.x + width;
	brc.top = topleft.y;
	brc.bottom = topleft.y + height;
}

bool myButton::setLabel(char* in_text, int size)
{
	if (size < 128) //128 is the max size of the title
	{
		for (int i = 0; i < size; i++)
		{
			label[i] = (WCHAR)in_text[i];
		}
		return true;
	}
	else
	{
		return false;
	}
}

bool myButton::get_btnOn()
{
	return buttonState;
}