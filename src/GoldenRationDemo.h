// Copyright (c) 2026 Ossama Mostafa
// MIT License

#pragma once
#include <Windows.h>
#include "myPropertySheet.h"
#include "InfoWindow.h"
#include "PictureViewer.h"

using namespace std;

#define NUMWINDOWS 3


struct vogelProps
{
	int i_max = 500;
	int scale = 15;
	int constantOne = 2;
	int constantTwo = 2;
	int colorson = 0;
};

class GoldenRationDemo
{
public:
	myPropertySheet ps_vogel;
	vogelProps vp;

	InfoWindow* myinfo;
	PictureViewer picWin;
	slide* sli;

	void init();
	void updateVP();
	void DrawVogel(HDC hdc, HWND hwnd);

	void drawWindow(int k, HDC hdc, HWND hwnd);
	int numWindows = NUMWINDOWS;
	int k[NUMWINDOWS] = { 0, 1, 2 }; //draw order key
	/*
	* 0 - propsheet, 1 - Infosheet, 2- picture window
	*/

	void DrawVogelEquation(POINT origin, HDC memdc);
	float vogel_equation(int floret_idx, int scale);


	
	void open_propsheet();
	void open_info();
	void open_pic();
	void processLclick(POINT cursor);
	void processDragging(POINT cursor);
	void processScroll(POINT pt, int zdelta, int mult);
	void endDrag();

	void cleanup();
};

