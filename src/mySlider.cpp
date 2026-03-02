// Copyright (c) 2026 Ossama Mostafa
// MIT License

#include "mySlider.h"


mySlider::mySlider(float _min, float _max, float _dx, int _width, int _style, COLORREF col_slider, COLORREF col_track)
{
	min = _min;
	max = _max;
	dx = _dx;
	track_width = _width;
	slider_radius = 0.05 * track_width;
	style = _style;
	slider_color = col_slider;
	track_color = col_track;


	interval = 20;
	pos = 0;

	darkenSliderDrag = 0;
	darkenSliderHover = 0;
	calculateSelectedValue();
}
void mySlider::calculateSelectedValue()
{
	float adj_pos = pos - slider_radius;
	float adj_width = track_width - 2 * slider_radius;

	//float inter = ((float)pos / (float)track_width) * (float)((float)max - (float)min);	
	float inter = (adj_pos / adj_width) * (float)((float)max - (float)min);
	float r = std::round(inter / dx);
	selected_value = r * dx + min;
	if (selected_value < min)
	{
		selected_value = min;
	}
	if (selected_value > max)
	{
		selected_value = max;
	}
}

void mySlider::setValue(float val)
{
	if (val >= min && val <= max)
	{
		float r = (val - min) / dx;
		float inter = r * dx;
		float ratio = inter / (float)((float)max - (float)min);
		float adj_pos = ratio * (track_width - 2 * slider_radius);
		pos = adj_pos + slider_radius;
		calculateSelectedValue();
	}
}
void mySlider::setPosition(float val)
{
	if (val >= min && val <= max)
	{
		float r = (val - min) / dx;
		float inter = r * dx;
		float ratio = inter / (float)((float)max - (float)min);
		float adj_pos = ratio * (track_width - 2 * slider_radius);
		pos = adj_pos + slider_radius;
	}
}
void mySlider::processScroll(POINT pt, int zdelta, int mult)
{
	if (inTrackbar(pt))
	{
		if (zdelta > 0 && selected_value <max)
		{
			selected_value += mult * dx;
		}
		else if (zdelta < 0 && selected_value > min)
		{
			selected_value -= mult * dx;
		}
		setPosition(selected_value);
	}
	
}
void mySlider::inc()
{
	pos += interval;
}
void mySlider::dec()
{
	pos -= interval;
}


void mySlider::draw(HDC hdc)
{
	int boundary_height = boundary.bottom - boundary.top;

	if (style == 0)
	{
		//Rectangle slider


		COLORREF currColor = slider_color;
		if (darkenSliderHover == 1)
		{
			currColor /= 2;
		}
		if (darkenSliderDrag > 0 && darkenSliderDrag < 3)
		{
			currColor /= 2;
			darkenSliderDrag = (darkenSliderDrag + 1) % 3;
		}


		RECT trackbar;
		trackbar.left = boundary.left;
		trackbar.right = boundary.right;
		trackbar.top = boundary.top + 0.25 * boundary_height;
		trackbar.bottom = boundary.bottom - 0.25 * boundary_height;

		RECT slider;

		int slider_center = pos + trackbar.left;
		slider.left = slider_center - slider_radius;
		slider.right = slider_center + slider_radius;
		slider.top = trackbar.top;
		slider.bottom = trackbar.bottom;



		dragarea.left = slider.left - 50;
		dragarea.right = slider.right + 50;
		dragarea.top = slider.top - 25;
		dragarea.bottom = slider.bottom + 25;

		HBRUSH tBrush = CreateSolidBrush(track_color);
		HBRUSH sBrush = CreateSolidBrush(currColor);

		FillRect(hdc, &trackbar, tBrush);
		FillRect(hdc, &slider, sBrush);
		DeleteObject(tBrush);
		DeleteObject(sBrush);
	}
}

bool mySlider::inSlider(POINT pt)
{
	RECT ctb; //current track boundary
	ctb.left = boundary.left + pos - slider_radius;
	ctb.right = boundary.left + pos + slider_radius;
	ctb.top = boundary.top;
	ctb.bottom = boundary.bottom;

	if (pt.x >= ctb.left && pt.x <= ctb.right && pt.y >= ctb.top && pt.y <= ctb.bottom)
	{
		darkenSliderHover = 1;
		return true;
	}
	else
	{
		darkenSliderHover = 0;
		return false;
	}

}
bool mySlider::inDragarea(POINT pt)
{
	if (pt.x >= dragarea.left && pt.x <= dragarea.right && pt.y >= dragarea.top && pt.y <= dragarea.bottom)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool mySlider::inTrackbar(POINT pt)
{
	int boundary_height = boundary.bottom - boundary.top;
	RECT trackbar;
	trackbar.left = boundary.left;
	trackbar.right = boundary.right;
	trackbar.top = boundary.top + 0.25 * boundary_height;
	trackbar.bottom = boundary.bottom - 0.25 * boundary_height;


	if (pt.x >= trackbar.left && pt.x <= trackbar.right && pt.y >= trackbar.top && pt.y <= trackbar.bottom)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void mySlider::drag(POINT pt)
{
	//This function assumes that a correct drag event is happening in this slider and that the pt parameter is the location of the cursor.
	if ((pt.x - slider_radius >= boundary.left) && (pt.x + slider_radius <= boundary.right))
	{
		pos = pt.x - boundary.left;
		calculateSelectedValue();
		darkenSliderDrag = 1;
	}
}