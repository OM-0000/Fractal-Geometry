// Copyright (c) 2026 Ossama Mostafa
// MIT License

#pragma once
#include "DynStack.h"
#include <Windows.h>
#include <string>
#include <cmath>
#include "myPropertySheet.h"

using namespace std;
struct drawinfo
{
	int x, y;
	float angle;
	drawinfo(int _x, int _y, float _angle)
	{
		x = _x;
		y = _y;
		angle = _angle;
	}
};

struct functionVariables
{
	int itr = 0;
	float branchsize = 50;
	float leafsize = 25;	
	int dy = 0;
	int dx = 0;
	float dtheta = 45;
	int fidx = 0;
};

class LSystem
{
public:
	myPropertySheet propsheet;
	functionVariables fv;
	
	
	
	void Draw(HDC hdc, HWND hwnd, POINT origin);
	string applyLS(string input);
	POINT findPoint(int xs, int ys, float angle, int linesize);

	int fractal_idx;
	string current_code;
	bool code_written;
	int last_itr;
	int last_fractal;
	
	
	
	
	void init();
	void updateFV();
	void processClick(POINT pt);
	void processDrag(POINT pt);
	void processScroll(POINT pt, int zdelta, int mult);
	void endDrag();
};

