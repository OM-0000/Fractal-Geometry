// Copyright (c) 2026 Ossama Mostafa
// MIT License

#pragma once
#include <windows.h>
#include <vector>

#include "myButton.h"
struct tbItem
{
	RECT brc;
};


class myToolBar
{
public:
	RECT brc;
	std::vector<tbItem> items;
	std::vector<myButton> buttons;

	myToolBar(RECT boundary);
	int padding;

	bool horozontal_layout; //true by default

	void insertButton_horo(int width, int height, char* _btn_label, int _label_size, COLORREF _bcolor, COLORREF _tColor);
	void insertButton_vert(int width, int height, char* _btn_label, int _label_size, COLORREF _bcolor, COLORREF _tColor);
	void Draw(HDC hdc);

	void processClick(POINT pt);

	void calculateLayout();
};
