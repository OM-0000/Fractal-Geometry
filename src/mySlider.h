// Copyright (c) 2026 Ossama Mostafa
// MIT License

#pragma once
#include <windows.h>
#include <cmath>


class mySlider
{
public:
	float min, max;
	float dx;
	float selected_value;

	int pos;
	int interval;
	int track_width;
	int slider_radius;

	int darkenSliderDrag;
	int darkenSliderHover;



	int style;
	COLORREF slider_color;
	COLORREF track_color;

	RECT boundary;
	RECT dragarea;

	mySlider(float _min, float _max, float _dx, int _width, int _style, COLORREF col_slider, COLORREF col_track);
	void inc();
	void dec();
	void calculateSelectedValue();
	void draw(HDC hdc);
	bool inSlider(POINT pt);//returns true if point is in the slider
	bool inDragarea(POINT pt);
	bool inTrackbar(POINT pt);
	void drag(POINT pt);
	void setValue(float val);
	void setPosition(float val); //calculates and sets position for the passed in value.
	void processScroll(POINT pt, int zdelta, int mult);
};

