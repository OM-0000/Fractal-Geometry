// Copyright (c) 2026 Ossama Mostafa
// MIT License

#include "BarnsleyFernDemo.h"

void BarnsleyFernDemo::init()
{
	srand((unsigned)time(0)); //random num seed for Barnsley fern

	//Initializing each UI element used for this demo.

	//Init propsheet
	ps_Barnsley.tb_topleft.x = 100;
	ps_Barnsley.tb_topleft.y = 100;
	ps_Barnsley.cl_height = 650;
	ps_Barnsley.cl_width = 550;
	ps_Barnsley.CalculateLayout();
	char title_barns[] = { "Barnsley Fern Property Sheet" };
	ps_Barnsley.setTitle(title_barns, sizeof(title_barns) / sizeof(char));

	//Init labels and items for propsheet
	char bf_lbl_itrs[] = { "Iterations" };
	PS_Item bf_psitem_itrs(40000,0, 150000, 1000.00f, 200, 0, COLORREF(0xffffff), COLORREF(0x0a0a0a), bf_lbl_itrs, sizeof(bf_lbl_itrs) / sizeof(char));
	bf_psitem_itrs.bgColor = ps_Barnsley.cl_col;
	bf_psitem_itrs.textColor = 0xa0ffff;
	ps_Barnsley.Add_Item(bf_psitem_itrs);

	
	char bf_lbl_scale[] = { "Scale" };
	PS_Item bf_psitem_scale(-50,-1000, 1000, 1.0f, 200, 0, COLORREF(0xffffff), COLORREF(0x0a0a0a), bf_lbl_scale, sizeof(bf_lbl_scale) / sizeof(char));
	bf_psitem_scale.bgColor = ps_Barnsley.cl_col;
	bf_psitem_scale.textColor = 0xa0ffff;
	ps_Barnsley.Add_Item(bf_psitem_scale);

	
	char bf_lbl_colorson[] = { "Colors" };
	PS_Item bf_psitem_colorson(0,0, 1, 1.0f, 200, 0, COLORREF(0xffffff), COLORREF(0x0a0a0a), bf_lbl_colorson, sizeof(bf_lbl_colorson) / sizeof(char));
	bf_psitem_colorson.bgColor = ps_Barnsley.cl_col;
	bf_psitem_colorson.textColor = 0xa0ffff;
	ps_Barnsley.Add_Item(bf_psitem_colorson);

	
	char bf_lbl_f2a[] = { "f2a" };
	PS_Item bf_psitem_f2a(.85 ,- 2.2, 7, 0.0001f, 300, 0, COLORREF(0xffffff), COLORREF(0x0a0a0a), bf_lbl_f2a, sizeof(bf_lbl_f2a) / sizeof(char));
	bf_psitem_f2a.bgColor = ps_Barnsley.cl_col;
	bf_psitem_f2a.textColor = 0xa0ffff;
	ps_Barnsley.Add_Item(bf_psitem_f2a);

	
	char bf_lbl_f2b[] = { "f2b" };
	PS_Item bf_psitem_f2b(.04 ,- 2.2, 7, 0.0001f, 300, 0, COLORREF(0xffffff), COLORREF(0x0a0a0a), bf_lbl_f2b, sizeof(bf_lbl_f2b) / sizeof(char));
	bf_psitem_f2b.bgColor = ps_Barnsley.cl_col;
	bf_psitem_f2b.textColor = 0xa0ffff;
	ps_Barnsley.Add_Item(bf_psitem_f2b);

	
	char bf_lbl_f2c[] = { "f2c" };
	PS_Item bf_psitem_f2c(-.04 ,- 2.2, 7, 0.0001f, 300, 0, COLORREF(0xffffff), COLORREF(0x0a0a0a), bf_lbl_f2c, sizeof(bf_lbl_f2c) / sizeof(char));
	bf_psitem_f2c.bgColor = ps_Barnsley.cl_col;
	bf_psitem_f2c.textColor = 0xa0ffff;
	ps_Barnsley.Add_Item(bf_psitem_f2c);

	
	char bf_lbl_f2d[] = { "f2d" };
	PS_Item bf_psitem_f2d(.85 ,- 2.2, 7, 0.0001f, 300, 0, COLORREF(0xffffff), COLORREF(0x0a0a0a), bf_lbl_f2d, sizeof(bf_lbl_f2d) / sizeof(char));
	bf_psitem_f2d.bgColor = ps_Barnsley.cl_col;
	bf_psitem_f2d.textColor = 0xa0ffff;
	ps_Barnsley.Add_Item(bf_psitem_f2d);

	
	char bf_lbl_f2e[] = { "f2e" };
	PS_Item bf_psitem_f2e(0 ,- 2.2, 7, 0.0001f, 300, 0, COLORREF(0xffffff), COLORREF(0x0a0a0a), bf_lbl_f2e, sizeof(bf_lbl_f2e) / sizeof(char));
	bf_psitem_f2e.bgColor = ps_Barnsley.cl_col;
	bf_psitem_f2e.textColor = 0xa0ffff;
	ps_Barnsley.Add_Item(bf_psitem_f2e);

	
	char bf_lbl_f2f[] = { "f2f" };
	PS_Item bf_psitem_f2f(1.60 ,-2.2, 7, 0.0001f, 300, 0, COLORREF(0xffffff), COLORREF(0x0a0a0a), bf_lbl_f2f, sizeof(bf_lbl_f2f) / sizeof(char));
	bf_psitem_f2f.bgColor = ps_Barnsley.cl_col;
	bf_psitem_f2f.textColor = 0xa0ffff;
	ps_Barnsley.Add_Item(bf_psitem_f2f);

	char bf_lbl_pre[] = { "Presets" };
	PS_Item bf_psitem_pre(1,0,5,1.0f,200,0, COLORREF(0xffffff), COLORREF(0x0a0a0a), bf_lbl_pre, sizeof(bf_lbl_pre) / sizeof(char));
	bf_psitem_pre.bgColor = ps_Barnsley.cl_col;
	bf_psitem_pre.textColor = 0xa0ffff;
	ps_Barnsley.Add_Item(bf_psitem_pre);
	
	//Get bottom rect for ps_Barnsley (propsheet) and use that to initialize a toolbar to that bottom rect (used to hold the animate presets button)
	RECT tbrect = ps_Barnsley.getBottomRect();
	tb = new myToolBar(tbrect);

	//Declare label for button and use tb.insertButton_horo(...) to insert a new button in a horozontal sense (new buttons fill out to the right).
	char tb_btn1_lbl[] = { "Animate Presets" };
	tb->insertButton_horo(100, 50, tb_btn1_lbl, sizeof(tb_btn1_lbl) / sizeof(char), COLORREF(0xaaaaaa), COLORREF(0x0a0a0a));

	//Close the propsheet so the module begins with that window in the closed state
	ps_Barnsley.close();

	//Info Window
	char infoTitle[] = { "Fractals and the Barnsley Fern" };
	myinfo = new InfoWindow(infoTitle, sizeof(infoTitle) / sizeof(char));
	myinfo->tb_topleft.x = 200;
	myinfo->tb_topleft.y = 100;
	myinfo->cl_height = 600;
	myinfo->cl_width = 600;
	myinfo->close();
	myinfo->CalculateLayout();

	//Add page with my written description to infowindow. Text is internally split up and justified by the info window.
	char infoMessage[] = { "The Barnsley fern is an iteratively generated fractal geometry which looks like a fern plant. I implemented this system in this demonstration. It assigns a probability to the application of four functions which produce the basic leaflet pattern; each function corresponds to different segments of the fern. The new drawing locations are calculated using the previous drawing location as an input in the iterative formula. The Barnsley fern was made by Michael Barnsley, a mathematician. In their paper \"V-variable Fractals and Superfractals\", Barnsley et al. sought to make IFSs more flexible and faster to compute. Barnsley and his colleagues describe how to generate V-variable fractals, which they introduced to address the above issues with IFSs. \"V - variable fractals allow for such randomnessand variability across scales,\" wrote Barnsley referring to the level of variation which occurs in the fractal-like patterns in ferns, plants, and leaves. Interestingly, he speculated that there would be a correspondence between the code trees of a V-variable fractal and the genes of a plant, whenever such a model captures accurately \nthe geometry of the plant." };
	myinfo->AddPage(infoMessage, sizeof(infoMessage) / sizeof(char));
	myinfo->setMessagefromPage(0);

	//Picture window

	//Set root folder for picture window
	char root[] = { "./bitmaps/" };
	picWin.setRoot(root, sizeof(root) / sizeof(char));

	//Add each asset as a separate slide to the picture window. It expects these bmps to be named this way and to be inside the root folder set above.
	char picTitle[] = { "Pictures for Barnsley Fern" }; //Title for the window
	picWin.init(200, 100, 600, 600, picTitle, sizeof(picTitle) / sizeof(char));
	picWin.CalculateLayout();
	//First slide
	char ppath[] = { "shrunk_fern.bmp" }; //name of slide's file
	char pic1_citation[] = { "Sanjay Ach \'Fern plants at Muir Woods, California\'. Found on wikipedia. Note the self-similarity fractal-like pattern of the fern leaves." }; //caption written under picture, in window
	picWin.AddSlide(ppath, sizeof(ppath) / sizeof(char), pic1_citation, sizeof(pic1_citation) / sizeof(char));
	picWin.setPathfromSlide(0);	
	//Second slide
	char pic5_cap[] = "Anatomy of a fern";
	char ppath5[] = { "fern_anatomy.bmp" };
	picWin.AddSlide(ppath5, sizeof(ppath5) / sizeof(char), pic5_cap, sizeof(pic5_cap) / sizeof(char));
	//Third slide
	char ppath6[] = { "applying_IFS.bmp" };
	char pic6_cap[] = { "A Sierpinski triangle, like the Barnsley fern, is a fractal which results from the application of an iterated function system (IFS)." };
	picWin.AddSlide(ppath6, sizeof(ppath6) / sizeof(char), pic6_cap, sizeof(pic6_cap) / sizeof(char));
	//Fourth slide
	char ppath2[] = {"culcita_fern_shrunk.bmp"};
	char pic2_cap[] = { "Culcita fern." };
	picWin.AddSlide(ppath2, sizeof(ppath2) / sizeof(char), pic2_cap, sizeof(pic2_cap) / sizeof(char));
	//Fifth slide
	char pic3_cap[] = "Fern plant exhibiting fractal self-similarlity. Picture found on fractalfoundation.org. \nPhoto credits: Jonathan Wolfe.";
	char ppath3[] = { "fernborg.bmp" };
	picWin.AddSlide(ppath3, sizeof(ppath3) / sizeof(char), pic3_cap, sizeof(pic3_cap) / sizeof(char));
	//Sixth slide
	char pic4_cap[] = "Thelypteridaceae fern. Picture found on inaturalist.org. Photo credits: Homer Edward Price.";
	char ppath4[] = { "Thelypteridaceae_fern.bmp" };
	picWin.AddSlide(ppath4, sizeof(ppath4) / sizeof(char), pic4_cap, sizeof(pic4_cap) / sizeof(char));
	

	sli = new slide(); //initialize slide pointer



}

void BarnsleyFernDemo::button_events()
{
	//process propsheet toolbar buttons
	if (tb->buttons[0].get_btnOn())
	{
		tb->buttons[0].buttonState = 0;
		animate_presets();
	}
}

void BarnsleyFernDemo::animate_presets()
{
	//Called to initialize animation.
	//Resets timers, turns on animation flag, and sets initial values for parameters

	timer_one = 0;
	time_two = 0;
	animation = true;
	cs.f1a = 0;
	cs.f1b = 0;
	cs.f1c = 0;
	cs.f1d = .16;
	cs.f1e = 0;
	cs.f1f = 0;

	cs.f2a = .85;
	cs.f2b = .04;
	cs.f2c = -.04;
	cs.f2d = .85;
	cs.f2e = 0;
	cs.f2f = 1.60;

	cs.f3a = .20;
	cs.f3b = -.26;
	cs.f3c = .23;
	cs.f3d = .23;
	cs.f3e = 0;
	cs.f3f = 1.60;

	cs.f4a = -.15;
	cs.f4b = .28;
	cs.f4c = .26;
	cs.f4d = .24;
	cs.f4e = 0;
	cs.f4f = .44;
}
void BarnsleyFernDemo::updateBP()
{
	//Updates the parameters of the Barnsley Fern demo with values taken from the prop sheet.
	//This function takes each item value from the propsheet and uses that to update the demo struct.
	float v = 0;
	ps_Barnsley.get_item_value(0, &v);
	bp.numIter = v;
	ps_Barnsley.get_item_value(1, &v);
	bp.scale = v;
	ps_Barnsley.get_item_value(2, &v);
	bp.colors_on = v;
	ps_Barnsley.get_item_value(3, &v);
	bp.f2a = v;
	ps_Barnsley.get_item_value(4, &v);
	bp.f2b = v;
	ps_Barnsley.get_item_value(5, &v);
	bp.f2c = v;
	ps_Barnsley.get_item_value(6, &v);
	bp.f2d = v;
	ps_Barnsley.get_item_value(7, &v);
	bp.f2e = v;
	ps_Barnsley.get_item_value(8, &v);
	bp.f2f = v;
	ps_Barnsley.get_item_value(9, &v);
	bp.presets = v;
}
void BarnsleyFernDemo::DrawBarnsleyFern(HDC hdc, HWND hwnd)
{
	//Draw function

	//Draw windows
	for (int i = numWindows - 1; i > -1; i--)
	{
		drawWindow(k[i], hdc, hwnd);
	}
	//Call button events to handle any events that may have been pushed.
	button_events();

	//Don't draw slide's picture if the picWin is closed.
	if (picWin.closed)
	{
		sli->drawPic = false;
	}

	//Checks if the animation flag is on, executes animation if so.
	if (animation)
	{
		//Update timer_one.
		float dt = .03;
		timer_one += dt;

		//Calculate deltas for each parameter per time step
		float delf1a = 0- 0;
		float delf1b = 0 - 0;
		float delf1c = 0 - 0;
		float delf1d = .25 - .16;
		float delf1e = 0 - 0;
		float delf1f = -.04 - 0;

		float delf2a = .95- .85;
		float delf2b = .005 - .04;
		float delf2c = -.005-( - .04);
		float delf2d = .93 - .85;
		float delf2e = -.002 - 0;
		float delf2f = 0.5 - 1.60;

		float delf3a = .035- .20;
		float delf3b = -.2-(- .26);
		float delf3c = .16 - .23;
		float delf3d = .04 - .23;
		float delf3e = -.09 - 0;
		float delf3f = .02 - 1.60;

		float delf4a = -.04-(- .15);
		float delf4b = .2 - .28;
		float delf4c = .16 - .26;
		float delf4d = .04 - .24;
		float delf4e = 0.083 - 0;
		float delf4f = .12 - .44;

		//Calculate current value of each parameter by multiplying (delta/timestep) by (time-step) and adding to current parameter value.
		cs.f1a += delf1a * dt;
		cs.f1b += delf1b * dt;
		cs.f1c += delf1c * dt;
		cs.f1d += delf1d * dt;
		cs.f1e += delf1e * dt;
		cs.f1f += delf1f * dt;
		cs.f2a += delf2a * dt;
		cs.f2b += delf2b * dt;
		cs.f2c += delf2c * dt;
		cs.f2d += delf2d * dt;
		cs.f2e += delf2e * dt;
		cs.f2f += delf2f * dt;
		cs.f3a += delf3a * dt;
		cs.f3b += delf3b * dt;
		cs.f3c += delf3c * dt;
		cs.f3d += delf3d * dt;
		cs.f3e += delf3e * dt;
		cs.f3f += delf3f * dt;
		cs.f4a += delf4a * dt;
		cs.f4b += delf4b * dt;
		cs.f4c += delf4c * dt;
		cs.f4d += delf4d * dt;
		cs.f4e += delf4e * dt;
		cs.f4f += delf4f * dt;
		//After three time units, turn off animation. This will cause the Barnsley Fern state to revert to values taken from updateBP() (the values in the propsheet)
		if (timer_one >= 3)
		{
			animation = false;
		}

	}
	else
	{
		//If not animating, use updateBP() to update the demo's struct.
		updateBP();
		//Notwithstanding, if any presets are enabled, override struct with those values.
		//Preset One: standard Barnsley Fern
		if (bp.presets == 1)
		{
			cs.f1a = 0;
			cs.f1b = 0;
			cs.f1c = 0;
			cs.f1d = .16;
			cs.f1e = 0;
			cs.f1f = 0;

			cs.f2a = .85;
			cs.f2b = .04;
			cs.f2c = -.04;
			cs.f2d = .85;
			cs.f2e = 0;
			cs.f2f = 1.60;

			cs.f3a = .20;
			cs.f3b = -.26;
			cs.f3c = .23;
			cs.f3d = .23;
			cs.f3e = 0;
			cs.f3f = 1.60;

			cs.f4a = -.15;
			cs.f4b = .28;
			cs.f4c = .26;
			cs.f4d = .24;
			cs.f4e = 0;
			cs.f4f = .44;
		}
		//Preset Two: Thelypteridaceae Fern
		else if (bp.presets == 2)
		{
			//Thelypteridaceae Fern
			cs.f1a = 0;
			cs.f1b = 0;
			cs.f1c = 0;
			cs.f1d = .25;
			cs.f1e = 0;
			cs.f1f = -.04;

			cs.f2a = .95;
			cs.f2b = .005;
			cs.f2c = -.005;
			cs.f2d = .93;
			cs.f2e = -.002;
			cs.f2f = 0.5;

			cs.f3a = .035;
			cs.f3b = -.2;
			cs.f3c = .16;
			cs.f3d = .04;
			cs.f3e = -.09;
			cs.f3f = .02;

			cs.f4a = -.04;
			cs.f4b = .2;
			cs.f4c = .16;
			cs.f4d = .04;
			cs.f4e = 0.083;
			cs.f4f = .12;
		}
		//Preset 3: Something else
		else if (bp.presets == 3)
		{
			cs.f1a = 0;
			cs.f1b = 0;
			cs.f1c = 0;
			cs.f1d = .25;
			cs.f1e = 0;
			cs.f1f = -.04;

			cs.f2a = .95;
			cs.f2b = .002;
			cs.f2c = -.002;
			cs.f2d = .93;
			cs.f2e = -.002;
			cs.f2f = 0.5;

			cs.f3a = .035;
			cs.f3b = -.11;
			cs.f3c = .27;
			cs.f3d = .01;
			cs.f3e = -.05;
			cs.f3f = .005;

			cs.f4a = -.04;
			cs.f4b = .11;
			cs.f4c = .27;
			cs.f4d = .01;
			cs.f4e = 0.047;
			cs.f4f = .06;
		}
		else
		{
			//Else, use the demo struct.

			cs.f1a = 0;
			cs.f1b = 0;
			cs.f1c = 0;
			cs.f1d = .16;
			cs.f1e = 0;
			cs.f1f = 0;

			cs.f2a = bp.f2a;
			cs.f2b = bp.f2b;
			cs.f2c = bp.f2c;
			cs.f2d = bp.f2d;
			cs.f2e = bp.f2e;
			cs.f2f = bp.f2f;

			cs.f3a = .20;
			cs.f3b = -.26;
			cs.f3c = .23;
			cs.f3d = .23;
			cs.f3e = 0;
			cs.f3f = 1.60;

			cs.f4a = -.15;
			cs.f4b = .28;
			cs.f4c = .26;
			cs.f4d = .24;
			cs.f4e = 0;
			cs.f4f = .44;
		}
	}


	

	//Handles the main demo logic.

	//Get the client rect
	RECT clirc;
	GetClientRect(hwnd, &clirc);

	//Initialize colors
	COLORREF red = 0x0000dd;
	COLORREF green = 0x00dd00;
	COLORREF blue = 0xdd0000;
	COLORREF colors[3] = { red,green, blue };

	COLORREF green_colors[5] = { COLORREF(0x00ff00), COLORREF(0x00aa00), COLORREF(0x008800), COLORREF(0x00400), COLORREF(0x00a000) };

	//Calculate center of window
	POINT center;
	center.x = (clirc.right - clirc.left) / 2;
	center.y = (clirc.bottom - clirc.top) / 2;

	//Declare and initialize function-paramters to 0.0:
	// x: current x
	// y: current y
	// t: iteration counter
	// xn: new x
	// yn: new y

	//The transform-paramters are also used (i.e. the parameters defined by the prop sheet and bf struct).
	float x, y, t, xn, yn;
	x = y = t = xn = yn = 0.0;
	int colorpick = 0; //color pick is used for color-coding the fern if user enables color
	while (t < bp.numIter)
	{
		//Simulate probability by picking a random number between 1 and 100 and dividing by 100.
		float r = rand() % 100;
		r = r / 100;
		//This should happen about 1% of the time
		if (r < .01)
		{
			//Apply linear transformation to get new x,y from old x, y
			xn = cs.f1a * x + cs.f1b * y + cs.f1e;
			yn = cs.f1c * x + cs.f1d * y + cs.f1f;
			colorpick = 0; 
		}
		//This should happen about 85% of the time
		else if (r < .86)
		{
			//Apply linear transformation to get new x,y from old x, y
			xn = cs.f2a * x + cs.f2b * y + cs.f2e;
			yn = cs.f2c * x + cs.f2d * y + cs.f2f;
			colorpick = 1;
		}
		//This should happen about 17% of the time
		else if (r < .93)
		{
			//Apply linear transformation to get new x,y from old x, y
			xn = cs.f3a * x + cs.f3b * y + cs.f3e;
			yn = cs.f3c * x + cs.f3d * y + cs.f3f;
			colorpick = 0;
		}
		//This should happen about 7% of the time
		else
		{
			//Apply linear transformation to get new x,y from old x, y
			xn = cs.f4a * x + cs.f4b * y + cs.f4e;
			yn = cs.f4c * x + cs.f4d * y + cs.f4f;
			colorpick = 2;
		}
		//Draws the fern by plotting every point found using the above method.
		if (bp.colors_on)
		{
			//Set pixel using xn and yn, as well as bp.scale.
			SetPixel(hdc, center.x + xn * bp.scale, center.y + yn * bp.scale + 200, colors[colorpick]);
		}
		else
		{
			//Set pixel using xn and yn, as well as bp.scale.
			SetPixel(hdc, center.x + xn * bp.scale, center.y + yn * bp.scale + 200, green_colors[(int)t % 5]);
		}

		//Update current x and y to the previous new x and new y, to support the iterative method.
		x = xn;
		y = yn;
		t++; //increment iteration count

	}
}

void BarnsleyFernDemo::drawWindow(int k, HDC hdc, HWND hwnd)
{
	//Implementation-specific method of drawing windows (you must map k to the specific window). My newer framework improves on this.
	if (k == 0)
	{
		ps_Barnsley.draw(hdc, hwnd);
		if (!ps_Barnsley.closed)
		{	
			//toolbar's bounding rectangle (brc) must be continually updated to move with the propsheet.
			tb->brc = ps_Barnsley.getBottomRect();
			tb->calculateLayout();
			tb->Draw(hdc);
		}
	}
	if (k == 1)
	{
		//Draw the info window
		myinfo->draw(hdc, hwnd);
	}
	if (k == 2)
	{
		//Draw the picture window.
		picWin.draw(hdc, hwnd, sli);
	}
}

void BarnsleyFernDemo::open_propsheet()
{
	//This is when the showcase class's open prop sheet button is pressed.
	ps_Barnsley.open();
}
void BarnsleyFernDemo::open_info()
{
	//Open info window
	myinfo->open();
}
void BarnsleyFernDemo::open_pic()
{
	//Open picture window
	picWin.open();
}
void BarnsleyFernDemo::processLclick(POINT cursor)
{
	//Click pipeline from this demo to its windows
	if (ps_Barnsley.processClick(cursor) == 1)
	{
		tb->processClick(cursor);
		ps_Barnsley.selected = 1;
		myinfo->selected = 0;
		picWin.selected = 0;
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
		ps_Barnsley.selected = 0;
		myinfo->selected = 1;
		picWin.selected = 0;
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
		ps_Barnsley.selected = 0;
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
void BarnsleyFernDemo::processDragging(POINT cursor)
{
	//Dragging pipeline
	ps_Barnsley.processDragging(cursor);
	myinfo->processDragging(cursor);
	picWin.processDragging(cursor);
}
void BarnsleyFernDemo::endDrag()
{
	//End dragging pipeline
	ps_Barnsley.endDragging();
	myinfo->endDragging();
	picWin.endDragging();
}
void BarnsleyFernDemo::processScroll(POINT pt, int zdelta, int mult)
{
	//Scrolling pipeline
	ps_Barnsley.processScroll(pt, zdelta, mult);
}

void BarnsleyFernDemo::cleanup()
{	
	//Delete info window pointer
	if (myinfo)
	{
		delete myinfo;
	}
}







int BarnsleyFernDemo::concatenateCharArrays(char* str, char* c1, char* c2, int sz1, int sz2)
{
	//returns the size of the concatenated string
	//the concatenated string is stored in str.

	int size = sz1 + sz2;
	for (int i = 0; i < sz1; i++)
	{
		str[i] = c1[i];
	}
	for (int i = 0; i < sz2; i++)
	{
		str[i + sz1-1] = c2[i];
	}

	return size;
}