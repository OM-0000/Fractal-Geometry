// Copyright (c) 2026 Ossama Mostafa
// MIT License

#include "PictureViewer.h"

PictureViewer::PictureViewer()
{
	m_dragging = false;
	tb_col = 0x0a0505;
	cl_col = 0xaa0a04;
	picNavigation = new myToolBar(bottom_display);
	char btnlbl_prev[] = { "Previous Slide" };
	char btnlbl_next[] = { "Next Slide" };
	picNavigation->insertButton_horo(100, 50, btnlbl_prev, sizeof(btnlbl_prev) / sizeof(char), COLORREF(0x9aaa0a), COLORREF(0x0a0a0a));
	picNavigation->insertButton_horo(100, 50, btnlbl_next, sizeof(btnlbl_next) / sizeof(char), COLORREF(0x0aaa0a), COLORREF(0x0a0a0a));


	containsCaption = false;
	containsPicture = false;
	captionFormatted = false;
	currentCaption_size = 0;
	currentPath_size = 0;
	root_size = 0;
	close();
}
void PictureViewer::init(int topx, int topy, int _cl_height, int _cl_width, char* _title, int _title_sz)
{
	tb_topleft.x = topx;
	tb_topleft.y = topy;
	cl_height = _cl_height;
	cl_width = _cl_width;
	setTitle(_title, _title_sz);
	close();
}
/*
PictureViewer::~PictureViewer()
{
	for (int i = 0; i < slides.size(); i++)
	{
		delete slides[i].bmpath;
	}
	delete picNavigation;
}
*/
void PictureViewer::deletePointers()
{
	for (int i = 0; i < slides.size(); i++)
	{
		delete slides[i].bmpath;
	}
	delete picNavigation;
}
void PictureViewer::CalculateLayout()
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

	caption_rect.bottom = bottom_display.top;
	caption_rect.left = bottom_display.left;
	caption_rect.right = bottom_display.right;
	caption_rect.top = caption_rect.bottom - cl_height * .1;
	
	
	picNavigation->brc = bottom_display;
	picNavigation->calculateLayout();
	
}
void PictureViewer::draw(HDC hdc, HWND hwnd, slide* sl)
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


		if (containsPicture)
		{			
			sl->drawPic = true;
			sl->x = clientarea.left + 5;
			sl->y = clientarea.top + 5;
			sl->width = clientarea.right - sl->x;
			sl->height = caption_rect.top - sl->y;
			sl->bmpath = path;
			sl->numChars = currentPath_size;
		}
		else
		{
			sl->drawPic = false;
		}
		if (containsCaption)
		{
			if (!captionFormatted)
			{
				formatCaption(hdc);
			}
			SetBkColor(hdc, cl_col);
			RECT textRect = caption_rect;
			textRect.top += 5;
			DrawText(hdc, caption, -1, &textRect, DT_LEFT);
		}

		picNavigation->Draw(hdc);
	}
}
int PictureViewer::processClick(POINT pt)
{
	if (insideCloseButton(pt))
	{
		closed = true;
	}
	if (insideWindow(pt))
	{
		picNavigation->processClick(pt);
		if (picNavigation->buttons[0].get_btnOn())
		{
			//Previous page button clicked
			setPathfromSlide(currSlide - 1);
			picNavigation->buttons[0].buttonState = 0;

		}
		if (picNavigation->buttons[1].get_btnOn())
		{
			//Next page button clicked
			setPathfromSlide(currSlide + 1);
			picNavigation->buttons[1].buttonState = 0;
		}
		return 1;
	}
}
void PictureViewer::processDragging(POINT pt)
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
void PictureViewer::endDragging()
{
	m_dragging = false;
}

void PictureViewer::AddSlide(char* _path, int psize, char* _caption, int csize)
{
	//note: path null to caption argument if you don't want to use a caption

	if (psize < 2560) //2560 is the max size of the path.
	{
		WCHAR* p_path = new WCHAR[psize];
		for (int i = 0; i < psize; i++)
		{
			p_path[i] = (WCHAR)_path[i];
		}
		slide p;
		p.bmpath = p_path;
		p.numChars = psize;
		
		if (caption && csize < 1000)
		{
			WCHAR* p_caption = new WCHAR[csize];
			for (int i = 0; i < csize; i++)
			{
				p_caption[i] = _caption[i];
			}
			p.caption = p_caption;
			p.cap_size = csize;
		}
		slides.push_back(p);
	}
}
void PictureViewer::setRoot(char* _path, int size)
{
	if (size < 256) //256 is the max size of the root.
	{
		for (int i = 0; i < size; i++)
		{
			root[i] = _path[i];
		}
		root_size = size;
	}
}
bool PictureViewer::setPath(char* _path, int size)
{
	if (size < 2560) //2560 is the max size of the path.
	{
		for (int i = 0; root[i] != '\0'; i++)
		{
			path[i] = (WCHAR)root[i];			
		}
		for (int i = 0; i < size; i++)
		{
			path[i+root_size-1] = (WCHAR)_path[i];
		}
		containsPicture = true;
		currentPath_size = size;
		return true;
	}
	else
	{
		return false;
	}
}
void PictureViewer::setPathfromSlide(int idx)
{
	if (idx >= 0 && idx < slides.size())
	{		
		for (int i = 0; root[i] != '\0'; i++)
		{
			path[i] = (WCHAR)root[i];
		}
		for (int i = 0; i < slides[idx].numChars; i++)
		{
			path[i+root_size-1] = slides[idx].bmpath[i];
		}
		containsPicture = true;
		currentPath_size = slides[idx].numChars;
		currSlide = idx;

		if (slides[idx].cap_size > 0)
		{
			for (int i = 0; i < slides[idx].cap_size; i++)
			{
				caption[i] = slides[idx].caption[i];
			}
			containsCaption = true;
			currentCaption_size = slides[idx].cap_size;
			captionFormatted = false;
		}
		else
		{
			containsCaption = false;
			currentCaption_size = 0;
			captionFormatted = false;
		}
	}
}

bool PictureViewer::setCaption(char* in_text, int size)
{
	if (size < 1000) //1000 is the max size of the caption.
	{
		for (int i = 0; i < size; i++)
		{
			caption[i] = (WCHAR)in_text[i];
		}
		containsCaption = true;
		currentCaption_size = size;
		return true;
	}
	else
	{
		return false;
	}
}

void PictureViewer::formatCaption(HDC hdc)
{
	SIZE sz;
	LPSTR str = (LPSTR)caption;
	GetTextExtentPoint32A(hdc, str, currentCaption_size, &sz);
	int numbreaks = sz.cx / cl_width;
	float char_to_wid = (float)cl_width / (float)sz.cx;
	int char_interval = char_to_wid * currentCaption_size;
	int idx = char_interval;
	int lostchars = 0;
	for (int i = 0; i < numbreaks; i++)
	{
		if (caption[idx - 1] != '\n' && caption[idx] != '\n' && caption[idx + 1] != '\n')
		{
			if (caption[idx - 1] != ' ' && caption[idx] != ' ')
			{
				for (; caption[idx - 1] != ' ' && idx - 1 != 0; idx--)
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

			if (caption[idx] == ' ')
			{
				caption[idx] = '\n';
			}
			else
			{
				WCHAR temp = caption[idx];
				for (int j = idx; j < currentCaption_size; j++)
				{
					WCHAR second_temp = caption[j + 1];
					caption[j + 1] = temp;
					temp = second_temp;
				}
				caption[idx] = '\n';
				currentCaption_size++;

			}

			idx += char_interval;

		}

	}
	captionFormatted = true;
}