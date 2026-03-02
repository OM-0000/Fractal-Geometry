// Copyright (c) 2026 Ossama Mostafa
// MIT License

#pragma once
#include "myMatrix.h"

class Vector
{
public:
	Vector(float x, float y, float z);
	Vector();
	~Vector();
	float tuple[3]; //(x, y, z)

	float loc[3]; //(x, y, z) of the vector's tail

	void RotateVector_mat(Vector* axis, float angle);


	Vector AddVectorToVector(Vector* vec_in);
	Vector SubtractVectorFromVector(Vector* vec_in);
	Vector DivideVectorByScalar(float in_scalar);
	Vector MultiplyVectorByScalar(float in_scalar);
	Vector CrossProduct(Vector* vec_in);
	float DotProduct(Vector* vec_in);
	float get_size();
	bool isOpp(Vector* vec_in);

	void operator += (Vector const& obj) {

		for (int i = 0; i < 3; i++)
		{
			tuple[i] += obj.tuple[i];
		}
	}

	void operator -= (Vector const& obj) {

		for (int i = 0; i < 3; i++)
		{
			tuple[i] -= obj.tuple[i];
		}
	}

};