// Copyright (c) 2026 Ossama Mostafa
// MIT License

#pragma once
#include "BasicWindow.h"
#include "PS_Item.h"
#include <vector>
class myPropertySheet : public BasicWindow
{
private:
	std::vector<PS_Item> items;
	int item_idx;//this saves the index of the item whose slider is being dragged.
public:
	myPropertySheet();
	void init(int topx, int topy, int _cl_height, int _cl_width, char* _title, int _title_sz);
	void CalculateLayout();

	void draw(HDC hdc, HWND hwnd);

	int processClick(POINT pt);
	void processDragging(POINT pt);
	void endDragging();
	void Add_Item(PS_Item it);
	void get_item_value(int idx, void* val);
	RECT getBottomRect();
	void processScroll(POINT pt, int zdelta, int mult);

};

