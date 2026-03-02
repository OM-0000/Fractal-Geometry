// Copyright (c) 2026 Ossama Mostafa
// MIT License

#pragma once
#include "Vector.h"
#include <cmath>
class myPoint
{
public:
	myPoint(float x, float y, float z);
	myPoint();
	~myPoint();


	float tuple[3]; //(x, y, z)

	bool on = false;
	void toggle();
	bool get_on();

	myPoint AddVectorToPoint(Vector* vec_in);
	myPoint SubtractVectorFromPoint(Vector* vec_in);
	Vector SubtractPointFromPoint(myPoint* pt_in);

};