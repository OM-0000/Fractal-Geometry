// Copyright (c) 2026 Ossama Mostafa
// MIT License

#pragma once
#include <ctime>
#include <Windows.h>
#include "myPropertySheet.h"
#include "InfoWindow.h"
#include "PictureViewer.h"

using namespace std;

#define NUMWINDOWS 3

struct barnsleyProps
{
	int numIter = 100000;
	float f2a = .85;
	float f2b = .04;
	float f2c = -.04;
	float f2d = .85;
	float f2e = 0;
	float f2f = 1.6;
	int colors_on = 0;
	float scale = -50;
	int presets = 0;
};

struct currentState
{
	float f1a = 0;
	float f1b = 0;
	float f1c = 0;
	float f1d = .16;
	float f1e = 0;
	float f1f = 0;

	float f2a = .85;
	float f2b = .04;
	float f2c = -.04;
	float f2d = .85;
	float f2e = 0;
	float f2f = 1.60;

	float f3a = .20;
	float f3b = -.26;
	float f3c = .23;
	float f3d = .23;
	float f3e = 0;
	float f3f = 1.60;

	float f4a = -.15;
	float f4b = .28;
	float f4c = .26;
	float f4d = .24;
	float f4e = 0;
	float f4f = .44;
};

class BarnsleyFernDemo
{
public:
	myPropertySheet ps_Barnsley;
	myToolBar* tb;
	barnsleyProps bp;
	
	InfoWindow* myinfo;
	PictureViewer picWin;
	slide* sli;

	void init();	
	void updateBP();
	void DrawBarnsleyFern(HDC hdc, HWND hwnd);

	void drawWindow(int k, HDC hdc, HWND hwnd);
	int numWindows = NUMWINDOWS;
	int k[NUMWINDOWS] = { 0, 1, 2 }; //draw order key
	/*	
	* 0 - Barnsley, 1 - Infosheet, 2- picture window
	*/

	currentState cs; //this is used for animating the fern

	float running_time;
	float timer_one;
	float time_two;
	bool animation = false;

	void button_events();
	void animate_presets();
	void open_propsheet();
	void open_info();
	void open_pic();
	void processLclick(POINT cursor);
	void processDragging(POINT cursor);
	void processScroll(POINT pt, int zdelta, int mult);
	void endDrag();

	void cleanup();

	int concatenateCharArrays(char* str, char* c1, char* c2, int sz1, int sz2);
};

