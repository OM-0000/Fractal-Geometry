// Copyright (c) 2026 Ossama Mostafa
// MIT License

#include "LSystem.h"

void LSystem::init()
{
	char title[] = "LSYSTEM PROPSHEET";
	propsheet.init(0, 0, 400, 400, title, sizeof(title) / sizeof(char));
	
	char lsp_lbl_itr[] = { "Iterations" };
	PS_Item lsp_psitem_itr(0.0f, 0.0f, 25, 1, 100, 0, COLORREF(0xffffff), COLORREF(0x0a0a0a), lsp_lbl_itr, sizeof(lsp_lbl_itr) / sizeof(char));
	//PS_Item lsp_psitem_itr(lsp_sldr_itr, lsp_lbl_itr, sizeof(lsp_lbl_itr) / sizeof(char));
	lsp_psitem_itr.bgColor = propsheet.cl_col;
	lsp_psitem_itr.textColor = 0xa0ffff;
	propsheet.Add_Item(lsp_psitem_itr);

	
	char lsp_lbl_brsz[] = { "Branchsize" };
	PS_Item lsp_psitem_brsz(50, 0, 100, 1, 100, 0, COLORREF(0xffffff), COLORREF(0x0a0a0a), lsp_lbl_brsz, sizeof(lsp_lbl_brsz) / sizeof(char));
	lsp_psitem_brsz.bgColor = propsheet.cl_col;
	lsp_psitem_brsz.textColor = 0xa0ffff;
	propsheet.Add_Item(lsp_psitem_brsz);

	
	char lsp_lbl_lfsz[] = { "Leafsize" };
	PS_Item lsp_psitem_lfsz(25,0, 100, 1, 100, 0, COLORREF(0xffffff), COLORREF(0x0a0a0a), lsp_lbl_lfsz, sizeof(lsp_lbl_lfsz) / sizeof(char));
	lsp_psitem_lfsz.bgColor = propsheet.cl_col;
	lsp_psitem_lfsz.textColor = 0xa0ffff;
	propsheet.Add_Item(lsp_psitem_lfsz);

	
	char lsp_lbl_dy[] = { "y" };
	PS_Item lsp_psitem_dy(0,-500, 1000, 1, 100, 0, COLORREF(0xffffff), COLORREF(0x0a0a0a), lsp_lbl_dy, sizeof(lsp_lbl_dy) / sizeof(char));
	lsp_psitem_dy.bgColor = propsheet.cl_col;
	lsp_psitem_dy.textColor = 0xa0ffff;
	propsheet.Add_Item(lsp_psitem_dy);

	
	char lsp_lbl_dx[] = { "x" };
	PS_Item lsp_psitem_dx(0,-800, 800, 1, 100, 0, COLORREF(0xffffff), COLORREF(0x0a0a0a), lsp_lbl_dx, sizeof(lsp_lbl_dx) / sizeof(char));
	lsp_psitem_dx.bgColor = propsheet.cl_col;
	lsp_psitem_dx.textColor = 0xa0ffff;
	propsheet.Add_Item(lsp_psitem_dx);

	
	char lsp_lbl_da[] = { "Delta angle" };
	PS_Item lsp_psitem_da(45,-90, 90, 1, 100, 0, COLORREF(0xffffff), COLORREF(0x0a0a0a), lsp_lbl_da, sizeof(lsp_lbl_da) / sizeof(char));
	lsp_psitem_da.bgColor = propsheet.cl_col;
	lsp_psitem_da.textColor = 0xa0ffff;
	propsheet.Add_Item(lsp_psitem_da);

	
	char lsp_lbl_fidx[] = { "Fractal Idx" };
	PS_Item lsp_psitem_fidx(0,0, 1, 1, 100, 0, COLORREF(0xffffff), COLORREF(0x0a0a0a), lsp_lbl_fidx, sizeof(lsp_lbl_fidx) / sizeof(char));
	lsp_psitem_fidx.bgColor = propsheet.cl_col;
	lsp_psitem_fidx.textColor = 0xa0ffff;
	propsheet.Add_Item(lsp_psitem_fidx);

	code_written = false;
	current_code = "";
	fractal_idx = 1;
	last_itr = -1;
	last_fractal = -1;

}
void LSystem::processClick(POINT pt)
{
	propsheet.processClick(pt);
}



void LSystem::processDrag(POINT pt)
{
	propsheet.processDragging(pt);
}
void LSystem::endDrag()
{
	propsheet.endDragging();
}


void LSystem::processScroll(POINT pt, int zdelta, int mult)
{
	propsheet.processScroll(pt, zdelta, mult);
}



void LSystem::updateFV()
{
	float f;
	propsheet.get_item_value(0, &f);
	fv.itr = f;
	propsheet.get_item_value(1, &f);
	fv.branchsize = f;
	propsheet.get_item_value(2, &f);
	fv.leafsize = f;
	propsheet.get_item_value(3, &f);
	fv.dy = f;
	propsheet.get_item_value(4, &f);
	fv.dx = f;
	propsheet.get_item_value(5, &f);
	fv.dtheta = f;
	propsheet.get_item_value(6, &f);
	fv.fidx = f;
}






void LSystem::Draw(HDC hdc, HWND hwnd, POINT origin)
{
	updateFV();
	fractal_idx = fv.fidx;
	int itr;

	if ((fv.fidx < 0 || fv.fidx > 1))
	{
		fv.fidx = 0;
	}
	if ((fv.itr < 0 || fv.itr > 25))
	{
		fv.itr = 0;
	}
	if (last_itr == -1 || last_fractal == -1)
	{
		last_itr = itr = fv.itr;
		last_fractal = fv.fidx;
		code_written = false;
	}
	else if (last_itr != fv.itr || last_fractal != fv.fidx)
	{
		last_itr = itr = fv.itr;
		last_fractal = fv.fidx;
		code_written = false;
	}
	else
	{
		code_written = true;
	}


	if (fractal_idx == 0)
	{
		DynStack lstk;

		string axiom = "0";
		string result = axiom;
		if (code_written == false)
		{
			current_code = result;
			for (int i = 0; i < itr; i++)
			{
				current_code = result = applyLS(result);
			}
		}
		else
		{
			result = current_code;
		}

		HPEN pen = CreatePen(PS_SOLID, 2, COLORREF(0xa00a0a));
		SelectObject(hdc, pen);
		MoveToEx(hdc, origin.x, origin.y, NULL);
		float angle = 0;
		int branchsize = fv.branchsize;
		int leafsize = fv.leafsize;
		int size = leafsize;
		int curr_x = origin.x + fv.dx;
		int curr_y = origin.y + fv.dy;

		for (int i = 0; i < result.size(); i++)
		{
			if (result[i] == '0')
			{
				MoveToEx(hdc, curr_x, curr_y, NULL);
				size = leafsize;
				POINT end = findPoint(curr_x, curr_y, angle, size);
				LineTo(hdc, end.x, end.y);
				curr_x = end.x;
				curr_y = end.y;
			}
			if (result[i] == '1')
			{
				MoveToEx(hdc, curr_x, curr_y, NULL);
				size = branchsize;
				POINT end = findPoint(curr_x, curr_y, angle, size);
				LineTo(hdc, end.x, end.y);
				curr_x = end.x;
				curr_y = end.y;
			}
			if (result[i] == '[')
			{
				drawinfo* pdraw = new drawinfo(curr_x, curr_y, angle);
				lstk.push(pdraw);
				angle -= 3.14159 * fv.dtheta / 180;
			}
			if (result[i] == ']')
			{
				void* temp = nullptr;
				if (lstk.pop(&temp))
				{
					curr_x = static_cast<drawinfo*>(temp)->x;
					curr_y = static_cast<drawinfo*>(temp)->y;
					angle = static_cast<drawinfo*>(temp)->angle;
					angle += 3.14159 * fv.dtheta / 180;
				}
			}
		}
	}
	if (fractal_idx == 1)
	{
		DynStack lstk;

		string axiom = "X";
		string result = axiom;
		if (code_written == false)
		{
			current_code = result;
			for (int i = 0; i < itr; i++)
			{
				current_code = result = applyLS(result);
			}
		}
		else
		{
			result = current_code;
		}
		

		HPEN pen = CreatePen(PS_SOLID, 2, COLORREF(0xa00a0a));
		SelectObject(hdc, pen);
		MoveToEx(hdc, origin.x, origin.y, NULL);
		float angle = 3.14159*fv.dtheta / 180;
		int branchsize = fv.branchsize;
		int leafsize = fv.leafsize;
		int size = leafsize;
		int curr_x = origin.x + fv.dx;
		int curr_y = origin.y + fv.dy;

		for (int i = 0; i < result.size(); i++)
		{
			if (result[i] == 'F')
			{
				MoveToEx(hdc, curr_x, curr_y, NULL);
				size = branchsize;
				POINT end = findPoint(curr_x, curr_y, angle, size);
				LineTo(hdc, end.x, end.y);
				curr_x = end.x;
				curr_y = end.y;
			}
			if (result[i] == '-')
			{
				angle -= (3.14159 * 25 / 180);
			}
			if (result[i] == '+')
			{
				angle += (3.14159 * 25 / 180);
			}
			if (result[i] == '[')
			{
				drawinfo* pdraw = new drawinfo(curr_x, curr_y, angle);
				lstk.push(pdraw);
			}
			if (result[i] == ']')
			{
				void* temp = nullptr;
				if (lstk.pop(&temp))
				{
					curr_x = static_cast<drawinfo*>(temp)->x;
					curr_y = static_cast<drawinfo*>(temp)->y;
					angle = static_cast<drawinfo*>(temp)->angle;
				}
			}
		}
	}


	

}

string LSystem::applyLS(string input)
{
	string output = "";

	if (fractal_idx == 0)
	{
		for (int i = 0; i < input.size(); i++)
		{
			if (input[i] == '0')
			{
				output += "1[0]0";
			}
			if (input[i] == '1')
			{
				output += "11";
			}
			if (input[i] == '[')
			{
				output += "[";
			}
			if (input[i] == ']')
			{
				output += "]";
			}
		}
	}
	if (fractal_idx == 1)
	{
		for (int i = 0; i < input.size(); i++)
		{
			if (input[i] == 'X')
			{
				output += "F+[[X]-X]-F[-FX]+X";
			}
			if (input[i] == 'F')
			{
				output += "FF";
			}
			if (input[i] == '[')
			{
				output += "[";
			}
			if (input[i] == ']')
			{
				output += "]";
			}
			if (input[i] == '+')
			{
				output += "+";
			}
			if (input[i] == '-')
			{
				output += "-";
			}
		}
	}
	return output;
}

POINT LSystem::findPoint(int xs, int ys, float angle, int linesize)
{
	int dx = sin(angle) * linesize;
	int dy = cos(angle) * linesize;

	POINT out;
	out.x = xs + dx;
	out.y = ys - dy;

	return out;
}