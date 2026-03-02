// Copyright (c) 2026 Ossama Mostafa
// MIT License

#include "FractalTreeDemo.h"
void FractalTreeDemo::init()
{
	ls.init();
	//Info Window
	char infoTitle[] = { "Fractal Geometry and the Metabolism of Trees" };
	myinfo = new InfoWindow(infoTitle, sizeof(infoTitle) / sizeof(char));
	myinfo->tb_topleft.x = 200;
	myinfo->tb_topleft.y = 100;
	myinfo->cl_height = 600;
	myinfo->cl_width = 600;
	myinfo->CalculateLayout();

	char infoMessage[] = { "     Fractals are a kind of geometric pattern which generally involve repeating patterns as you zoom in closer to them. This quality is called self-similarity. An example is the Mandelbrot set. Fractals and other geometric patterns are relevant to morphology, which is a branch of biology which studies the forms of living structures. This demo contains two fractal trees which are constructed using L-Systems. An L-system is a kind of grammar for constructing an output string out of an input string. It works by iteratively feeding previous inputs (starting with an initial axiom string) and using rules to replace certain variables with other strings. For example, in the first fractal tree, 1 is replaced with 11. The resulting string can be used as instructions for a graphics application to draw, as it is used here to draw trees. Sometimes such instructions can be considered hereditary instructions from which an organism may read in constructing itself. \nThe L-system was actually created by a biologist, Aristid Lindenmayer, in 1968. He used them to describe and model plant cells and growth processes. He wrote a paper in 1968 titled \"Mathematical Models for Cellular Interactions in Development\". He constructed computational models for \"a particular branching filamentous organism\"; for example \"a particular red alga, Callithamnion roseum\"(source 1, pg 9). It seems he was trying to model the growth of filaments in cells. The system he describes is very complicated and obscure, way more so than what it takes to write simple fractal trees, but it seems to me that a similar principle of iterative growth is at work in the construction of outputs from smaller starting points that describe the state of a complex \nsystem." };
	myinfo->AddPage(infoMessage, sizeof(infoMessage) / sizeof(char));
	myinfo->setMessagefromPage(0);
	char infoMessage2[] = { "Another practical application of fractal geometry is in the use of fractal dimension to identify plants species. In \"Plant Identification Based on Fractal Refinement Technique(FRT)\" by Antony Jobin et al., a method for identifying plant spcies by analyzing leaf images is described. \"Fractal dimensions can be used in a more general sense referring to any of the dimensions commonly used to characterize fractals.\"(Jobin 2). Using a box counting method on pictures of leaves(e.g. a part of a picture of a leaf that contains a point of interest for analysis is isolated, filled with boxes and counted; aka \"pixel covering method\"), the fractal dimension of a particular leaf sample can be derived. By taking into account the fractal dimension of leaves, computer algorithms can identify a plant species by analyzing leaf pictures with 84% accuracy, according to the authors of the paper. This new method which includes analysis of the countour structure of leaves, like previous methods, but also specifies leaf samples according to properties of their nervure(veins), \"ultimately brought up the accuracy rate from \n74% to 84%\"(Jobin 3)." };
	myinfo->AddPage(infoMessage2, sizeof(infoMessage2) / sizeof(char));

	myinfo->close();


	//Picture Window
	char root[] = { "./bitmaps/" };
	picWin.setRoot(root, sizeof(root) / sizeof(char));
	//
	char picTitle[] = { "Pictures for Fractal Trees" };
	picWin.init(200, 100, 600, 600, picTitle, sizeof(picTitle) / sizeof(char));
	picWin.CalculateLayout();
	char pic1_cap[] = { "Photo from wikipedia commons." };
	char ppath[] = { "tree_branches.bmp" };	
	picWin.AddSlide(ppath, sizeof(ppath) / sizeof(char), pic1_cap, sizeof(pic1_cap) / sizeof(char));
	picWin.setPathfromSlide(0);
	char pic2_cap[] = { "Callithamnion roseum, computationally modelled by Lindenmayer in 1968" };
	char ppath2[] = { "algae.bmp" };
	picWin.AddSlide(ppath2, sizeof(ppath2) / sizeof(char), pic2_cap, sizeof(pic2_cap) / sizeof(char));
	char pic5_cap[] = { "Fractal patterns in leaf veins/nervure" };
	char ppath5[] = { "leaf_fractal.bmp" };
	picWin.AddSlide(ppath5, sizeof(ppath5) / sizeof(char), pic5_cap, sizeof(pic5_cap) / sizeof(char));
	char pic6_cap[] = { "Leaf species used in study on identifying plants by leaves with computer algorithms (Jobin et al)" };
	char ppath6[] = { "leaves_used.bmp" };
	picWin.AddSlide(ppath6, sizeof(ppath6) / sizeof(char), pic6_cap, sizeof(pic6_cap) / sizeof(char));
	char pic3_cap[] = { "A Mandelbrot fractal." };
	char ppath3[] = { "Mandelbrot_400x.bmp" };
	picWin.AddSlide(ppath3, sizeof(ppath3) / sizeof(char), pic3_cap, sizeof(pic3_cap) / sizeof(char));
	char pic4_cap[] = { "These flowers also exhibit self-similarity at smaller scales, i.e. they exhibit fractal geometry." };
	char ppath4[] = { "fractal_flowers.bmp" };
	picWin.AddSlide(ppath4, sizeof(ppath4) / sizeof(char), pic4_cap, sizeof(pic4_cap) / sizeof(char));

	sli = new slide(); //initialize slide pointer

}
void FractalTreeDemo::DrawFractalTree(HDC hdc, HWND hwnd)
{
	for (int i = numWindows - 1; i > -1; i--)
	{
		drawWindow(k[i], hdc, hwnd);
	}

	if (picWin.closed)
	{
		sli->drawPic = false;
	}

	RECT clirc;
	GetClientRect(hwnd, &clirc);
	POINT center;
	center.x = (clirc.right - clirc.left) / 2;
	center.y = (clirc.bottom - clirc.top) / 2;
	POINT seed;
	seed.x = center.x;
	seed.y = center.y + 400;
	ls.Draw(hdc, hwnd, seed);
}

void FractalTreeDemo::drawWindow(int k, HDC hdc, HWND hwnd)
{
	if (k == 0)
	{
		ls.propsheet.draw(hdc, hwnd);
	}
	if (k == 1)
	{
		myinfo->draw(hdc, hwnd);
	}
	if (k == 2)
	{
		picWin.draw(hdc, hwnd, sli);
	}
}

void FractalTreeDemo::open_propsheet()
{
	ls.propsheet.open();
}
void FractalTreeDemo::open_info()
{
	myinfo->open();
}
void FractalTreeDemo::open_pic()
{
	picWin.open();
}
void FractalTreeDemo::processLclick(POINT cursor)
{
	if (ls.propsheet.processClick(cursor) == 1)
	{
		ls.propsheet.selected = 1;
		myinfo->selected = 0;
		//floating the draw key of the selected window to the top so that the window will be drawn first
		int idx = -1;
		for (int i = 0; i < numWindows; i++)
		{
			if (k[i] == 0)
			{
				idx = i;
				break;
			}
		}
		for (int i = idx; i > 0; i--)
		{
			int temp = k[i];
			k[i] = k[i - 1];
			k[i - 1] = temp;
		}
	}
	else if (myinfo->processClick(cursor) == 1)
	{
		ls.propsheet.selected = 0;
		myinfo->selected = 1;
		//floating the draw key of the selected window to the top so that the window will be drawn first
		int idx = -1;
		for (int i = 0; i < numWindows; i++)
		{
			if (k[i] == 1)
			{
				idx = i;
				break;
			}
		}
		for (int i = idx; i > 0; i--)
		{
			int temp = k[i];
			k[i] = k[i - 1];
			k[i - 1] = temp;
		}
	}
	else if (picWin.processClick(cursor) == 1)
	{
		ls.propsheet.selected = 0;
		myinfo->selected = 0;
		picWin.selected = 1;
		//floating the draw key of the selected window to the top so that the window will be drawn first
		int idx = -1;
		for (int i = 0; i < numWindows; i++)
		{
			if (k[i] == 2)
			{
				idx = i;
				break;
			}
		}
		for (int i = idx; i > 0; i--)
		{
			int temp = k[i];
			k[i] = k[i - 1];
			k[i - 1] = temp;
		}
	}
}
void FractalTreeDemo::processDragging(POINT cursor)
{
	ls.propsheet.processDragging(cursor);
	myinfo->processDragging(cursor);
	picWin.processDragging(cursor);
}
void FractalTreeDemo::endDrag()
{
	ls.propsheet.endDragging();
	myinfo->endDragging();
	picWin.endDragging();
}
void FractalTreeDemo::processScroll(POINT pt, int zdelta, int mult)
{
	ls.processScroll(pt, zdelta, mult);
}
void FractalTreeDemo::cleanup()
{
	if (myinfo)
	{
		delete myinfo;
	}
}
