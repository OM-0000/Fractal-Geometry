// Copyright (c) 2026 Ossama Mostafa
// MIT License

#include "myPropertySheet.h"
myPropertySheet::myPropertySheet()
{
	close();
	close_override = false;
	m_dragging = false;
	selected = false;
	tb_col = 0x0a0505;
	cl_col = 0xaa0a04;
	HRGN rgn = CreateRectRgn(clientarea.left, clientarea.top, clientarea.right, clientarea.bottom);
	setClearRgn(rgn);

}
void myPropertySheet::init(int topx, int topy, int _cl_height, int _cl_width, char* _title, int _title_sz)
{
	tb_topleft.x = topx;
	tb_topleft.y = topy;
	cl_height = _cl_height;
	cl_width = _cl_width;
	setTitle(_title, _title_sz);
	close();
}
void myPropertySheet::CalculateLayout()
{
	int tb_height = .05 * cl_width;

	titlebar.left = tb_topleft.x;
	titlebar.right = tb_topleft.x + cl_width;
	titlebar.top = tb_topleft.y;
	titlebar.bottom = tb_topleft.y + tb_height;


	dragbuffer.left = titlebar.left - 100;
	dragbuffer.right = titlebar.right + 100;
	dragbuffer.top = titlebar.top - 100;
	dragbuffer.bottom = titlebar.bottom + 100;


	clientarea.left = titlebar.left;
	clientarea.right = titlebar.right;
	clientarea.top = titlebar.bottom;
	clientarea.bottom = clientarea.top + cl_height;

	close_button.right = titlebar.right;
	close_button.left = titlebar.right - .05 * cl_width;
	close_button.top = titlebar.top;
	close_button.bottom = titlebar.bottom;

	bottom_display.bottom = clientarea.bottom;
	bottom_display.top = bottom_display.bottom - cl_height * .1;
	bottom_display.left = clientarea.left;
	bottom_display.right = clientarea.right;	

}

void myPropertySheet::draw(HDC hdc, HWND hwnd)
{
	if (!closed)
	{
		CalculateLayout();

		COLORREF red = 0x0000aa;
		HBRUSH tbBrush = CreateSolidBrush(tb_col);
		HBRUSH clBrush = CreateSolidBrush(cl_col);
		HBRUSH redBrush = CreateSolidBrush(red);

		FillRect(hdc, &titlebar, tbBrush);
		FillRect(hdc, &clientarea, clBrush);
		FillRect(hdc, &close_button, redBrush);
		RECT window;
		window.left = clientarea.left;
		window.right = clientarea.right;
		window.top = titlebar.top;
		window.bottom = clientarea.bottom;
		if (selected)
		{
			HBRUSH whiteBrush = CreateSolidBrush(COLORREF(0xffffff));
			FrameRect(hdc, &window, whiteBrush);
			DeleteObject(whiteBrush);
		}

		DeleteObject(tbBrush);
		DeleteObject(clBrush);
		DeleteObject(redBrush);

		int max = 0;
		for (int i = 0; i < items.size(); i++)
		{
			LONG cx = items[i].getText_pixellength(hdc).cx;
			if (cx > max)
			{
				max = cx;
			}
		}


		int ps_height = 50;
		int padding = 10;
		for (int i = 0; i < items.size(); i++)
		{
			items[i].slider_left_bump = max;

			items[i].topleft.x = clientarea.left + padding;
			items[i].topleft.y = clientarea.top + i * ps_height + (i + 1) * padding;
			items[i].bottomright.y = clientarea.top + (i + 1) * ps_height + (i + 1) * padding;
			items[i].bottomright.x = clientarea.right - padding;
			items[i].Draw(hdc);
		}



		SetBkColor(hdc, tb_col);
		SetTextColor(hdc, COLORREF(0xffffff));
		DrawText(hdc, title, -1, &titlebar, DT_LEFT);
	}
	

}
int myPropertySheet::processClick(POINT pt)
{
	if (insideCloseButton(pt))
	{
		close();
		close_override = true;
	}
	if (insideWindow(pt))
	{
		return 1;
	}
}
void myPropertySheet::processDragging(POINT pt)
{
	if (selected)
	{
		//This is called when the main window detects a drag event. Since this property sheet is one of the items for which dragging is a possibility, the main window calls this function to see if it needs to facilitate dragging for this object.
		if (insideTitleBar(pt) && m_dragging == false)
		{
			//This checks if the point passed along by the main was inside the titlebar of the property sheet as well as if dragging was not already occurring.
			//If both of these are true, it means that the user is trying to drag the property sheet window to relocate it. So the m_dragging variable is set to true. This tells the property sheet that so long as this function is being
			//called, the user is dragging the window.
			m_dragging = true;
			drag_x = pt.x - titlebar.left;
			drag_y = pt.y - titlebar.top;
		}
		if (m_dragging && insideDragArea(pt))
		{
			//Since a drag event was sensed and m_dragging is true, and the end condition is false (i.e., insideDragArea is true), a window drag start has occurred and not yet ended, therefore it is currently happening.
			//So,that means the location of the window should be moved to the point (with an offset). The point paramter is the cursor location at the instant of the processDragging function.
			tb_topleft.x = pt.x - drag_x;
			tb_topleft.y = pt.y - drag_y;
		}
		//So this works for sensing the drag event for moving the window. But this property sheet also needs to handle drag events for moving the controls within it, that is the selectors (sliders) of its items.
		//This code should check through all the items in the property sheet's list and see if the drag condition is met for any of those items.
		for (int i = 0; i < items.size(); i++)
		{
			if (items[i].selector->inSlider(pt) && items[i].m_dragging == false)
			{
				items[i].m_dragging = true;
				item_idx = i;
				break;
			}
		}
		if (item_idx >= 0 && item_idx < items.size())
		{
			if (items[item_idx].m_dragging && items[item_idx].selector->inDragarea(pt))
			{
				items[item_idx].selector->drag(pt);
				items[item_idx].updateValue();
			}
		}
	}


}

void myPropertySheet::endDragging()
{
	m_dragging = false;
	for (int i = 0; i < items.size(); i++)
	{
		items[i].m_dragging = false;
	}
}

void myPropertySheet::Add_Item(PS_Item it)
{
	items.push_back(it);
}

void myPropertySheet::get_item_value(int idx, void* val)
{
	*static_cast<float*>(val) = items[idx].value;
}

RECT myPropertySheet::getBottomRect()
{
	return bottom_display;
}

void myPropertySheet::processScroll(POINT pt, int zdelta, int mult)
{
	for (int i = 0; i < items.size(); i++)
	{
		items[i].processScroll(pt, zdelta, mult);
	}
}