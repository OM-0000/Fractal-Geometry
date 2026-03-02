// Copyright (c) 2026 Ossama Mostafa
// MIT License

#pragma once
#include <vector>

#include <Windows.h>
#include "BasicWindow.h"
#include "myToolBar.h"

struct page
{
	WCHAR* pg;
	int numChars;
};

class InfoWindow : public BasicWindow
{
private:
	RECT bottom_display;
public:
	InfoWindow(char* _label, int lbl_size);
	//~InfoWindow();
	WCHAR message[2560];
	std::vector<page>pages;
	int currPage;
	myToolBar* infoNavigation;

	bool containsMessage;
	int currentMessage_size;
	bool messageFormatted;

	void deletePointers();
	
	void CalculateLayout();
	void draw(HDC hdc, HWND hwnd);
	int processClick(POINT pt);
	void processDragging(POINT pt);
	void endDragging();
	bool setMessage(char* in_text, int size);
	void formatMessage(HDC hdc);

	void AddPage(char* in_text, int size);
	void setMessagefromPage(int idx);	
};

