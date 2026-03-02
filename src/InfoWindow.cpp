// Copyright (c) 2026 Ossama Mostafa
// MIT License

#include "InfoWindow.h"

InfoWindow::InfoWindow(char* _label, int lbl_size)
{

	m_dragging = false;
	containsMessage = false;
	messageFormatted = false;
	currentMessage_size = 0;
	tb_col = 0x0a0505;
	cl_col = 0xaa0a04;
	setTitle(_label, lbl_size);
	HRGN rgn = CreateRectRgn(clientarea.left, clientarea.top, clientarea.right, clientarea.bottom);	
	setClearRgn(rgn);

	
	infoNavigation = new myToolBar(bottom_display);
	char btnlbl_prev[] = { "Previous Page" };
	char btnlbl_next[] = { "Next Page" };
	infoNavigation->insertButton_horo(100, 50, btnlbl_prev, sizeof(btnlbl_prev) / sizeof(char), COLORREF(0x9aaa0a), COLORREF(0x0a0a0a));
	infoNavigation->insertButton_horo(100, 50, btnlbl_next, sizeof(btnlbl_next) / sizeof(char), COLORREF(0x0aaa0a), COLORREF(0x0a0a0a));

	
	close();
}
/*InfoWindow::~InfoWindow()
{
	for (int i = 0; i < pages.size(); i++)
	{
		delete pages[i].pg;
	}
	delete infoNavigation;
}
*/

void InfoWindow::deletePointers()
{
	for (int i = 0; i < pages.size(); i++)
	{
		delete pages[i].pg;
	}
	delete infoNavigation;
}

void InfoWindow::CalculateLayout()
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
	infoNavigation->brc = bottom_display;
	infoNavigation->calculateLayout();
}

void InfoWindow::draw(HDC hdc, HWND hwnd)
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
		SetBkColor(hdc, tb_col);
		SetTextColor(hdc, COLORREF(0xffffff));
		DrawText(hdc, title, -1, &titlebar, DT_LEFT);


		if (containsMessage)
		{
			if (!messageFormatted)
			{
				formatMessage(hdc);
			}
			SetBkColor(hdc, cl_col);
			RECT textRect = clientarea;
			textRect.top += 5;
			DrawText(hdc, message, -1, &textRect, DT_LEFT);
		}

		WCHAR footer[] = L"Page: ";
		DrawText(hdc, footer, -1, &bottom_display, DT_LEFT);
		infoNavigation->Draw(hdc);
	}
	
}

int InfoWindow::processClick(POINT pt)
{
	if (insideCloseButton(pt))
	{
		close();
	}
	if (insideWindow(pt))
	{
		infoNavigation->processClick(pt);
		if (infoNavigation->buttons[0].get_btnOn())
		{
			//Previous page button clicked
			setMessagefromPage(currPage - 1);
			infoNavigation->buttons[0].buttonState = 0;

		}
		if (infoNavigation->buttons[1].get_btnOn())
		{
			//Next page button clicked
			setMessagefromPage(currPage + 1);
			infoNavigation->buttons[1].buttonState = 0;
		}
		return 1;
	}



}
void InfoWindow::processDragging(POINT pt)
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
	}

}
void InfoWindow::endDragging()
{
	m_dragging = false;
}
bool InfoWindow::setMessage(char* in_text, int size)
{
	if (size < 2560) //2560 is the max size of the message/page.
	{
		for (int i = 0; i < size; i++)
		{
			message[i] = (WCHAR)in_text[i];
		}
		containsMessage = true;
		currentMessage_size = size;
		return true;
	}
	else
	{
		return false;
	}
}
void InfoWindow::formatMessage(HDC hdc)
{
	SIZE sz;
	LPSTR str = (LPSTR)message;
	GetTextExtentPoint32A(hdc, str, currentMessage_size, &sz);
	int numbreaks = sz.cx / cl_width;
	float char_to_wid = (float)cl_width / (float)sz.cx;
	int char_interval = char_to_wid * currentMessage_size;
	int idx = char_interval;
	int lostchars = 0;
	for (int i = 0; i < numbreaks; i++)
	{
		if (message[idx - 1] != '\n' && message[idx] != '\n' && message[idx + 1] != '\n')
		{
			if (message[idx - 1] != ' ' && message[idx] != ' ')
			{
				for (; message[idx - 1] != ' ' && idx - 1 != 0; idx--)
				{
					lostchars++;
				}
				if (lostchars > .8 * char_interval)
				{
					//The check condition for this fix is a lucky guess that might lead to a bug in the future.
					numbreaks++;
					lostchars = 0;
				}
			}

			if (message[idx] == ' ')
			{
				message[idx] = '\n';
			}
			else
			{
				WCHAR temp = message[idx];
				for (int j = idx; j < currentMessage_size; j++)
				{
					WCHAR second_temp = message[j + 1];
					message[j + 1] = temp;
					temp = second_temp;
				}
				message[idx] = '\n';
				currentMessage_size++;

			}

			idx += char_interval;

		}

	}
	messageFormatted = true;
}
void InfoWindow::AddPage(char* in_text, int size)
{
	if (size < 2560) //2560 is the max size of the message/page.
	{
		WCHAR* p_message = new WCHAR[size];
		for (int i = 0; i < size; i++)
		{
			p_message[i] = (WCHAR)in_text[i];
		}
		page p;
		p.pg = p_message;
		p.numChars = size;
		pages.push_back(p);
	}
}
void InfoWindow::setMessagefromPage(int idx)
{
	if (idx >= 0 && idx < pages.size())
	{
		messageFormatted = false;
		for (int i = 0; i < pages[idx].numChars; i++)
		{
			message[i] = pages[idx].pg[i];
		}
		containsMessage = true;
		currentMessage_size = pages[idx].numChars;
		currPage = idx;
	}

}