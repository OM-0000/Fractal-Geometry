// Copyright (c) 2026 Ossama Mostafa
// MIT License

#pragma once
#include <windows.h>
#include <windowsx.h>
#include <objidl.h>
#include <cmath>


#include "Vector.h"
#include "myPoint.h"
#include "BasicWindow.h"
#include "myPropertySheet.h"
#include "Showcase.h"

//Windows stuff___________________________________________________________________________________________________________________________________________________________

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL InitializeTimer(HWND hwnd);
POINT cursor_location;
int cursor_down = 0;
int dragging = 0;
//________________________________________________________________________________________________________________________________________________________________________
Showcase* sc;
void buildSC(HDC hdc, HWND hwnd);
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, PSTR, INT iCmdShow)
{
	HWND hwnd;
	MSG msg;
	WNDCLASS wndClass;


	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = WndProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance;
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = TEXT("BioProject");

	RegisterClass(&wndClass);
	INT XPOS = 1000;
	INT YPOS = 0;
	INT XSIZE = 920;
	INT YSIZE = 1000;

	hwnd = CreateWindow(
		TEXT("BioProject"),				//Window class name
		TEXT("Pinnation, Geometry, Plants"),		//Window caption
		WS_OVERLAPPEDWINDOW,		//Window style
		XPOS,						//initial x position
		YPOS,						//initial y position
		XSIZE,						//initial x size
		YSIZE,						//initial y size
		NULL,						//parent window handle
		NULL,						//window menu handle
		hInstance,					//program instance handle
		NULL						//creation paramters
	);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);


	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

void buildSC(HDC hdc, HWND hwnd)
{
	sc = new Showcase(hwnd, hdc);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT cli_rect;
	GetClientRect(hwnd, &cli_rect);

	switch (message)
	{
	case WM_CREATE:
	{
		InitializeTimer(hwnd);
		hdc = GetDC(hwnd);
		buildSC(hdc, hwnd);
		sc->init();

	}
	return 0;
	break;
	case WM_LBUTTONDOWN:
	{
		int x, y;
		x = GET_X_LPARAM(lParam);
		y = GET_Y_LPARAM(lParam);
		POINT pt;
		pt.x = x;
		pt.y = y;
		cursor_down = 1;
		sc->processLclick(pt);
	}
	break;
	case WM_LBUTTONUP:
	{
		cursor_down = 0;
		dragging = 0;
		sc->endDrag();
	}
	break;
	case WM_MOUSEMOVE:
	{
		int x, y;
		x = GET_X_LPARAM(lParam);
		y = GET_Y_LPARAM(lParam);
		cursor_location.x = x;
		cursor_location.y = y;
		if (cursor_down && dragging == 0)
		{
			dragging = 1;
		}
		if (dragging)
		{
			sc->processDrag(cursor_location);
			
		}
	}
	break;
	case WM_MOUSEWHEEL:
	{
		INT zDelta = GET_WHEEL_DELTA_WPARAM(wParam);
		UINT fwKeys = GET_KEYSTATE_WPARAM(wParam);

		int mult = 1;
		if (fwKeys == MK_SHIFT)
		{
			mult = 10;
		}

		sc->processScroll(cursor_location, zDelta, mult);
	}
	break;
	return 0;
	break;
	case WM_TIMER:
		sc->running_time += .3;
		InvalidateRect(hwnd, (const RECT*)&cli_rect, FALSE);
	case WM_PAINT:		
		BeginPaint(hwnd, &ps);
		sc->Draw();
		EndPaint(hwnd, &ps);
		return 0;
		break;
	case WM_SIZE:
		GetClientRect(hwnd, &cli_rect);
		sc->mainResize(cli_rect);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
		break;
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}


}

BOOL InitializeTimer(HWND hwnd)
{
	SetTimer(hwnd, 100, (1000 / 30), NULL);

	return TRUE;
}