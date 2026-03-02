// Copyright (c) 2026 Ossama Mostafa
// MIT License

#include "Showcase.h"
Showcase::Showcase(HWND hwnd, HDC hdc)
{
	m_hwnd = hwnd;
	m_hdc = hdc;
	selected_module = 0;
}
void Showcase::setDC(HDC hdc)
{
	m_hdc = hdc;
}
void Showcase::init()
{
	running_time = 0;

	bgColor = COLORREF(0xbf905d);

	RECT clirect;
	GetClientRect(m_hwnd, &clirect);
	header.left = clirect.left;
	header.right = clirect.left + 100;
	header.top = clirect.top;
	header.bottom = clirect.top + 50;
		
	header_text = new WCHAR[8];
	header_text[0] = 'M';
	header_text[1] = 'o';
	header_text[2] = 'd';
	header_text[3] = 'u';
	header_text[4] = 'l';
	header_text[5] = 'e';
	header_text[6] = 's';
	header_text[7] = '\0';






	//Initialize modules toolbar

	RECT mtb_rect;
	mtb_rect.left = header.right;
	mtb_rect.top = header.top;
	mtb_rect.right = clirect.right;
	mtb_rect.bottom = header.bottom;
	mtb = new myToolBar(mtb_rect);
	
	char mtb_btn1_lbl[] = { "Fractal Trees" };
	mtb->insertButton_horo(100, 50, mtb_btn1_lbl, sizeof(mtb_btn1_lbl) / sizeof(char), COLORREF(0xaaaaaa), COLORREF(0x0a0a0a));
	char mtb_btn2_lbl[] = { "Barnsley Fern" };
	mtb->insertButton_horo(100, 50, mtb_btn2_lbl, sizeof(mtb_btn2_lbl) / sizeof(char), COLORREF(0xaaaaaa), COLORREF(0x0a0a0a));
	char mtb_btn3_lbl[] = { "Golden Ratio" };
	mtb->insertButton_horo(100, 50, mtb_btn3_lbl, sizeof(mtb_btn3_lbl) / sizeof(char), COLORREF(0xaaaaaa), COLORREF(0x0a0a0a));


	initWTB(selected_module);


}

void Showcase::initWTB(int curmod)
{
	RECT clirect;
	GetClientRect(m_hwnd, &clirect);
	delete wtb;



	if (curmod == 0)
	{
		//Init fractal trees module
		RECT wtb_rect;
		wtb_rect.left = clirect.left;
		wtb_rect.top = header.bottom;
		wtb_rect.right = clirect.right;
		wtb_rect.bottom = wtb_rect.top + 50;
		wtb = new myToolBar(wtb_rect);

		char wtb_btn1_lbl[] = { "Fractal Trees Info(Essay)" };
		wtb->insertButton_horo(200, 50, wtb_btn1_lbl, sizeof(wtb_btn1_lbl) / sizeof(char), COLORREF(0xaaaaaa), COLORREF(0x0a0a0a));
		char wtb_btn2_lbl[] = { "Fractal Tree Property Sheet" };
		wtb->insertButton_horo(200, 50, wtb_btn2_lbl, sizeof(wtb_btn2_lbl) / sizeof(char), COLORREF(0xaaaaaa), COLORREF(0x0a0a0a));
		char wtb_btn3_lbl[] = { "Pictures" };
		wtb->insertButton_horo(200, 50, wtb_btn3_lbl, sizeof(wtb_btn3_lbl) / sizeof(char), COLORREF(0xaaaaaa), COLORREF(0x0a0a0a));
		ftd = new FractalTreeDemo();
		ftd->init();
	}
	if (curmod == 1)
	{
		//Init Barnsley Fern module
		RECT wtb_rect;
		wtb_rect.left = clirect.left;
		wtb_rect.top = header.bottom;
		wtb_rect.right = clirect.right;
		wtb_rect.bottom = wtb_rect.top + 50;
		wtb = new myToolBar(wtb_rect);

		char wtb_btn1_lbl[] = { "Barnsley Fern Info(Essay)" };
		wtb->insertButton_horo(200, 50, wtb_btn1_lbl, sizeof(wtb_btn1_lbl) / sizeof(char), COLORREF(0xaaaaaa), COLORREF(0x0a0a0a));
		char wtb_btn2_lbl[] = { "Barnsley Fern Property Sheet" };
		wtb->insertButton_horo(200, 50, wtb_btn2_lbl, sizeof(wtb_btn2_lbl) / sizeof(char), COLORREF(0xaaaaaa), COLORREF(0x0a0a0a));
		char wtb_btn3_lbl[] = { "Pictures" };
		wtb->insertButton_horo(200, 50, wtb_btn3_lbl, sizeof(wtb_btn3_lbl) / sizeof(char), COLORREF(0xaaaaaa), COLORREF(0x0a0a0a));
		bfd = new BarnsleyFernDemo();
		bfd->init();
	}
	if (curmod == 2)
	{
		//Init Golden Ratio module
		RECT wtb_rect;
		wtb_rect.left = clirect.left;
		wtb_rect.top = header.bottom;
		wtb_rect.right = clirect.right;
		wtb_rect.bottom = wtb_rect.top + 50;
		wtb = new myToolBar(wtb_rect);

		char wtb_btn1_lbl[] = { "Golden Ratio Info(Essay)" };
		wtb->insertButton_horo(200, 50, wtb_btn1_lbl, sizeof(wtb_btn1_lbl) / sizeof(char), COLORREF(0xaaaaaa), COLORREF(0x0a0a0a));
		char wtb_btn2_lbl[] = { "Golden Ratio Property Sheet" };
		wtb->insertButton_horo(200, 50, wtb_btn2_lbl, sizeof(wtb_btn2_lbl) / sizeof(char), COLORREF(0xaaaaaa), COLORREF(0x0a0a0a));
		char wtb_btn3_lbl[] = { "Pictures" };
		wtb->insertButton_horo(200, 50, wtb_btn3_lbl, sizeof(wtb_btn3_lbl) / sizeof(char), COLORREF(0xaaaaaa), COLORREF(0x0a0a0a));
		grd = new GoldenRationDemo();
		grd->init();
	}
}

void Showcase::CloseModule()
{
	//When about to switch modules, this function must be called to close the previously running module.
	if (closing_module == 0)
	{
		ftd->cleanup();
		delete ftd;
	}
	else if (closing_module == 1)
	{
		bfd->cleanup();
		delete bfd;
	}
	else if (closing_module == 2)
	{
		grd->cleanup();
		delete grd;
	}
}

void Showcase::button_events()
{
	//Process mtb buttons
	if (mtb->buttons[0].get_btnOn())
	{
		if (selected_module != 0)
		{
			closing_module = selected_module;
			CloseModule();
			selected_module = 0;
			initWTB(selected_module);
		}
		mtb->buttons[0].buttonState = 0;
	}
	if (mtb->buttons[1].get_btnOn())
	{
		if (selected_module != 1)
		{
			closing_module = selected_module;
			CloseModule();
			selected_module = 1;
			initWTB(selected_module);
		}		
		mtb->buttons[1].buttonState = 0;
	}
	if (mtb->buttons[2].get_btnOn())
	{
		if (selected_module != 2)
		{
			closing_module = selected_module;
			CloseModule();
			selected_module = 2;
			initWTB(selected_module);
		}
		mtb->buttons[2].buttonState = 0;
	}

	//Process wtb buttons
	if (selected_module == 0)
	{
		//This means Fractal Tree is running
		if (wtb->buttons[0].get_btnOn())
		{
			ftd->open_info();
			wtb->buttons[0].buttonState = 0;
		}
		if (wtb->buttons[1].get_btnOn())
		{
			ftd->open_propsheet();
			wtb->buttons[1].buttonState = 0;
		}
		if (wtb->buttons[2].get_btnOn())
		{
			ftd->open_pic();
			wtb->buttons[2].buttonState = 0;
		}
	}
	if (selected_module == 1)
	{
		//This means Barnsley Fern is running
		if (wtb->buttons[0].get_btnOn())
		{
			bfd->open_info();
			wtb->buttons[0].buttonState = 0;
		}
		if (wtb->buttons[1].get_btnOn())
		{
			bfd->open_propsheet();
			wtb->buttons[1].buttonState = 0;
		}
		if (wtb->buttons[2].get_btnOn())
		{
			bfd->open_pic();
			wtb->buttons[2].buttonState = 0;
		}
	}
	if (selected_module == 2)
	{
		//This means Golden Ratio is running
		if (wtb->buttons[0].get_btnOn())
		{
			grd->open_info();
			wtb->buttons[0].buttonState = 0;
		}
		if (wtb->buttons[1].get_btnOn())
		{
			grd->open_propsheet();
			wtb->buttons[1].buttonState = 0;
		}
		if (wtb->buttons[2].get_btnOn())
		{
			grd->open_pic();
			wtb->buttons[2].buttonState = 0;
		}
	}
	

}


void Showcase::Draw()
{
	RECT clirect;
	GetClientRect(m_hwnd, &clirect);
	HDC memdc = CreateCompatibleDC(m_hdc);
	HBITMAP hmem_map = CreateCompatibleBitmap(m_hdc, clirect.right - clirect.left, clirect.bottom - clirect.top);
	HBITMAP oldbm = (HBITMAP)SelectObject(memdc, hmem_map);
	
	HBRUSH bgBrush = CreateSolidBrush(bgColor);
	FillRect(memdc, &clirect, bgBrush);

	SetBkColor(memdc, bgColor);
	SetTextColor(memdc, 0x000000);
	DrawText(memdc, header_text, -1, &header, DT_LEFT);

	POINT center;
	center.x = (clirect.right - clirect.left) / 2;
	center.y = (clirect.bottom - clirect.top) / 2;


	button_events();
	mtb->Draw(memdc);
	wtb->Draw(memdc);


	HBITMAP hBitmap;
	BITMAP bitmap;
	HGDIOBJ oldBitmap;
	LPCWSTR p;
	slide s;
	
	hBitmap = (HBITMAP)LoadImageW(NULL, L"", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	bool drawBM = false;
	if (selected_module == 0)
	{
		ftd->DrawFractalTree(memdc, m_hwnd);
		if (ftd->sli->drawPic)
		{
			p = (LPCWSTR)ftd->sli->bmpath;
			hBitmap = (HBITMAP)LoadImageW(NULL, p, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
			s.x = ftd->sli->x;
			s.y = ftd->sli->y;
			s.height = ftd->sli->height;
			s.width = ftd->sli->width;
			drawBM = true;
		}
		else
		{
			hBitmap = NULL;
		}
	}
	if (selected_module == 1)
	{
		bfd->DrawBarnsleyFern(memdc, m_hwnd);
		bfd->running_time = running_time;
		if (bfd->sli->drawPic)
		{
			p = (LPCWSTR)bfd->sli->bmpath;
			hBitmap = (HBITMAP)LoadImageW(NULL, p, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
			s.x = bfd->sli->x;
			s.y = bfd->sli->y;
			s.height = bfd->sli->height;
			s.width = bfd->sli->width;
			drawBM = true;
		}
		else
		{
			hBitmap = NULL;
		}
	}
	if (selected_module == 2)
	{
		grd->DrawVogel(memdc, m_hwnd);
		if (grd->sli->drawPic)
		{
			p = (LPCWSTR)grd->sli->bmpath;
			hBitmap = (HBITMAP)LoadImageW(NULL, p, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
			s.x = grd->sli->x;
			s.y = grd->sli->y;
			s.height = grd->sli->height;
			s.width = grd->sli->width;
			drawBM = true;
		}
		else
		{
			hBitmap = NULL;
		}
	}



	
	
	
	
	BitBlt(m_hdc, clirect.left, clirect.top, clirect.right - clirect.left, clirect.bottom - clirect.top, memdc, clirect.left, clirect.top, SRCCOPY);
	SelectObject(memdc, oldbm);
	DeleteObject(hmem_map);

	if (drawBM)
	{
		oldBitmap = SelectObject(memdc, hBitmap);
		GetObject(hBitmap, sizeof(bitmap), &bitmap);
		BitBlt(m_hdc, s.x, s.y, s.width, s.height, memdc, 0, 0, SRCCOPY);
		SelectObject(memdc, oldBitmap);
		DeleteObject(hBitmap);
	}

	DeleteObject(memdc);
	DeleteObject(bgBrush);
}

void Showcase::processLclick(POINT cursor_location)
{
	//Should figure out what the click is intended for by determining whether a selection event is occurring or a different input event is occurring.
	//Should also determine which window or control is supposed to handle the event, it shouldn't be assumed that all windows are supposed to handle the click event.

	for (int i = 0; i < mtb->buttons.size(); i++)
	{
		mtb->processClick(cursor_location);
	}
	for (int i = 0; i < wtb->buttons.size(); i++)
	{
		wtb->processClick(cursor_location);
	}

	if (selected_module == 0)
	{
		ftd->processLclick(cursor_location);
	}
	if (selected_module == 1)
	{
		bfd->processLclick(cursor_location);
	}
	if (selected_module == 2)
	{
		grd->processLclick(cursor_location);
	}

}
void Showcase::processDrag(POINT pt)
{
	//Should call process drag events for all existing, open, selected windows
	if (selected_module == 0)
	{
		ftd->processDragging(pt);
	}
	if (selected_module == 1)
	{
		bfd->processDragging(pt);
	}
	if (selected_module == 2)
	{
		grd->processDragging(pt);
	}
}
void Showcase::endDrag()
{
	//Should end drag events for all existing windows.
	if (selected_module == 0)
	{
		ftd->endDrag();
	}
	if (selected_module == 1)
	{
		bfd->endDrag();
	}
	if (selected_module == 2)
	{
		grd->endDrag();
	}
}
void Showcase::mainResize(RECT clirect)
{
	//called when the main window resizes.
	//A good time to recalculate some windows/controls
	mtb->brc.right = clirect.right;
	wtb->brc.right = clirect.right;
}

void Showcase::processScroll(POINT pt, int zdelta, int mult)
{
	if (selected_module == 0)
	{
		ftd->processScroll(pt, zdelta, mult);
	}
	if (selected_module == 1)
	{
		bfd->processScroll(pt, zdelta, mult);
	}
	if (selected_module == 2)
	{
		grd->processScroll(pt, zdelta, mult);
	}
}