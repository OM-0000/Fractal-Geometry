// Copyright (c) 2026 Ossama Mostafa
// MIT License

#pragma once
#include "mySlider.h"
#include <string>
class PS_Item
{
public:
	WCHAR label[128];
	int label_size;
	int type; //0-int, 1-float, 2-bool, 3-text
	float value;
	WCHAR currVal_text[32];
	mySlider* selector;
	POINT topleft;
	POINT bottomright;
	COLORREF bgColor;
	COLORREF textColor;



	int slider_left_bump; //This is the distance from left of brc of all the sliders. set by the property sheet, defaults to width/3. 




	BOOL m_dragging;
	PS_Item(mySlider slider, char* in_text, int size);
	PS_Item(float initial_value, float _min, float _max, float _dx, int _width, int _style, COLORREF col_slider, COLORREF col_track, char* in_text, int size);
	void writeCurrValue();
	void updateValue();

	void Draw(HDC hdc);

	void processScroll(POINT pt, int zdelta, int mult);

	SIZE getText_pixellength(HDC hdc);
};