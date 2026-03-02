// Copyright (c) 2026 Ossama Mostafa
// MIT License

#include "PS_Item.h"

PS_Item::PS_Item(mySlider slider, char* in_text, int size)
{
	selector = new mySlider(slider.min, slider.max, slider.dx, slider.track_width, slider.style, slider.slider_color, slider.track_color);

	if (size < 128) //128 is the max size of the title
	{
		for (int i = 0; i < size; i++)
		{
			label[i] = (WCHAR)in_text[i];
		}
		label_size = size;
	}

	m_dragging = false;
	slider_left_bump = 1;
	value = selector->selected_value;
}

PS_Item::PS_Item(float initial_value, float _min, float _max, float _dx, int _width, int _style, COLORREF col_slider, COLORREF col_track, char* in_text, int size)
{
	selector = new mySlider(_min, _max, _dx, _width, _style, col_slider, col_track);

	if (size < 128) //128 is the max size of the title
	{
		for (int i = 0; i < size; i++)
		{
			label[i] = (WCHAR)in_text[i];
		}
		label_size = size;
	}
	selector->setValue(initial_value);
	updateValue();
	m_dragging = false;
	value = selector->selected_value;
}

SIZE PS_Item::getText_pixellength(HDC hdc)
{
	SIZE tsize;
	LPSTR str = (LPSTR)label;
	GetTextExtentPoint32A(hdc, str, label_size, &tsize);
	return tsize;
}

void PS_Item::Draw(HDC hdc)
{
	SetBkColor(hdc, bgColor);
	SetTextColor(hdc, textColor);
	RECT brc;
	brc.left = topleft.x;
	brc.top = topleft.y;
	brc.right = bottomright.x;
	brc.bottom = bottomright.y;


	//the brc is the rectange for the whole item, so it should scale its three elements (i.e. field name, slider, currrent value) to fit in the brc.
	//For now, I'm just going to add each element one after the other giving each what it ideally needs to be fully drawn.

	SIZE tsize;
	LPSTR str = (LPSTR)label;
	GetTextExtentPoint32A(hdc, str, label_size, &tsize);

	
	int wid = brc.right - brc.left;

	RECT labelRect;
	labelRect.left = brc.left;
	labelRect.right = brc.left + slider_left_bump;
	labelRect.top = brc.top;
	labelRect.bottom = brc.bottom;
	DrawText(hdc, label, -1, &labelRect, DT_LEFT);

	RECT sliderRect;
	int padding = 15;
	sliderRect.left = labelRect.right + padding;
	sliderRect.right = sliderRect.left + selector->track_width;
	sliderRect.top = brc.top - padding;
	sliderRect.bottom = brc.bottom - padding;
	selector->boundary = sliderRect;
	selector->draw(hdc);

	RECT currVal;
	updateValue();
	writeCurrValue();
	str = (LPSTR)currVal_text;
	GetTextExtentPoint32A(hdc, (LPSTR)label, sizeof(currVal_text) / sizeof(WCHAR), &tsize);
	currVal.left = sliderRect.right + padding;
	currVal.right = currVal.left + tsize.cx;
	currVal.top = brc.top;
	currVal.bottom = brc.bottom;
	DrawText(hdc, currVal_text, -1, &currVal, DT_LEFT);
}

void PS_Item::writeCurrValue()
{
	//should convert the float, value, to text and store in currVal_text.
	//char str[] = { "Heaveno" };
	std::string vstr;
	vstr = std::to_string(value);
	for (int i = 0; i < 32; i++)
	{
		currVal_text[i] = '\0';
	}
	for (int i = 0; i < vstr.size(); i++)
	{
		currVal_text[i] = vstr[i];
	}
	
}

void PS_Item::updateValue()
{
	value = selector->selected_value;
}

void PS_Item::processScroll(POINT pt, int zdelta, int mult)
{
	selector->processScroll(pt, zdelta, mult);
}