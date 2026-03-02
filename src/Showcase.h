// Copyright (c) 2026 Ossama Mostafa
// MIT License

#pragma once
#include <windows.h>
#include <cmath>
#include <string>

#include "myPropertySheet.h"
#include "myToolBar.h"
#include "InfoWindow.h"
#include "PictureViewer.h"
#include "LSystem.h"
#include "BarnsleyFernDemo.h"
#include "FractalTreeDemo.h"
#include "GoldenRationDemo.h"

class Showcase
{
private:
	RECT header;
	HWND m_hwnd;
	HDC m_hdc;
	COLORREF bgColor;
	WCHAR* header_text;
public:
	Showcase(HWND hwnd, HDC hdc);
	void setDC(HDC hdc);
	void init();
	void Draw();

	void processLclick(POINT cursor_location);	
	void processDrag(POINT pt);
	void endDrag();
	void mainResize(RECT clirect);
	void processScroll(POINT pt, int zdelta, int mult);


	float running_time;


	FractalTreeDemo *ftd;
	BarnsleyFernDemo* bfd;
	GoldenRationDemo* grd;



	myToolBar* mtb; //modules tool bar
	myToolBar* wtb; //windows tool bar
	myToolBar* navtb; //demo navigation tool bar
	int selected_module;
	void initWTB(int curmod);
	int closing_module; //the idx of the module that was just running and must be closed;
	void CloseModule();

	void button_events();

	

};

