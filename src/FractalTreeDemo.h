// Copyright (c) 2026 Ossama Mostafa
// MIT License

#pragma once
#include <Windows.h>
#include "myPropertySheet.h"
#include "InfoWindow.h"
#include "LSystem.h"
#include "PictureViewer.h"

#define NUMWINDOWS 3

class FractalTreeDemo
{
public:
	LSystem ls;
	InfoWindow* myinfo;
	PictureViewer picWin;

	slide* sli;

	void init();
	void DrawFractalTree(HDC hdc, HWND hwnd);

	void drawWindow(int k, HDC hdc, HWND hwnd);
	int numWindows = NUMWINDOWS;
	int k[NUMWINDOWS] = { 0, 1, 2}; //draw order key
	/*
	* 0 - Barnsley, 1 - Infosheet
	*/

	void open_propsheet();
	void open_info();
	void open_pic();
	void processLclick(POINT cursor);
	void processDragging(POINT cursor);
	void endDrag();
	void processScroll(POINT pt, int zdelta, int mult);

	void cleanup();

};

