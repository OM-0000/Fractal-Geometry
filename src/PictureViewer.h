// Copyright (c) 2026 Ossama Mostafa
// MIT License

#pragma once
#include <vector>

#include "BasicWindow.h"
#include "myToolBar.h"

struct slide
{
	int x, y; //top left of drawing area
	int width, height; //..of the drawing area
	bool drawPic = false;
	WCHAR* bmpath;
	int numChars;
	WCHAR* caption;
	int cap_size = -1;
};

class PictureViewer : public BasicWindow
{
private:
	RECT caption_rect;
public:
	PictureViewer();
	//~PictureViewer();
	void deletePointers();
	void init(int topx, int topy, int _cl_height, int _cl_width, char* _title, int _title_sz);
	char root[256];
	int root_size;
	WCHAR path[2560];
	std::vector<slide> slides;
	int currSlide;
	myToolBar* picNavigation;

	bool containsPicture;
	int currentPath_size;

	WCHAR caption[1000];
	bool containsCaption;
	int currentCaption_size;
	bool captionFormatted;
		
	void CalculateLayout();
	void setRoot(char* _path, int size);
	void draw(HDC hdc, HWND hwnd, slide* sl);
	int processClick(POINT pt);
	void processDragging(POINT pt);
	bool setPath(char* _path, int size);
	void endDragging();

	void AddSlide(char* _path, int psize, char* _caption, int csize);
	void setPathfromSlide(int idx); //this also sets the caption if the slide has a caption

	bool setCaption(char* in_text, int size);
	void formatCaption(HDC hdc);
};

