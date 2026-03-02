// Copyright (c) 2026 Ossama Mostafa
// MIT License

#pragma once
#include <Windows.h>
class myButton
{
public:
	POINT topleft; //topleft corner
	int width, height;
	RECT brc;
	WCHAR label[128];
	COLORREF btnColor;
	COLORREF textColor;


	int buttonState;
	int darkenButton;

	myButton(POINT _topleft, int _width, int _height, char* _label, int lbl_size, COLORREF _bcolor, COLORREF _tColor);
	BOOL inButton(POINT pt);
	void toggleButton();
	void processClick(POINT pt);

	void Draw(HDC hdc);
	void CalculateRect();
	bool setLabel(char* in_text, int size);

	bool get_btnOn();
};

