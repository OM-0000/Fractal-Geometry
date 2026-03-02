// Copyright (c) 2026 Ossama Mostafa
// MIT License

#include "Vector.h"
#include <cmath>

Vector::Vector(float x, float y, float z)
{
	tuple[0] = x;
	tuple[1] = y;
	tuple[2] = z;
}
Vector::Vector()
{

}
Vector::~Vector() {}

void Vector::RotateVector_mat(Vector* axis, float angle)
{
	//Rotate this vector and the new axis vector about either the z axis until the new axis vector is in the ZX plane.
	//Then, rotate them about the y axis until the new axis vector is parallel with the x axis.
	//Then, perform the rotation of this vector as if it were being rotated about the x axis.
	//Finally, reverse the transformations of both vectors.
	float tanXY = axis->tuple[1] / axis->tuple[0];
	float XYoff_angle = atan(tanXY);
	myMatrix mat;
	mat.init_RotXY_3x3(-XYoff_angle);
	mat.Rotate_XY_3x3(axis, axis);
	mat.Rotate_XY_3x3(this, this);

	float tanXZ = axis->tuple[2] / axis->tuple[0];
	float XZoff_angle = atan(tanXZ);
	mat.init_RotXZ_3x3(-XZoff_angle);
	mat.Rotate_XZ_3x3(axis, axis);
	mat.Rotate_XZ_3x3(this, this);

	//Now, the vectors are in place. Perform the desired transformation.
	mat.init_RotYZ_3x3(angle);
	mat.Rotate_YZ_3x3(this, this);

	//Undue the transformations to return the vectors to their original state, but keeping the transformation of this vector.
	mat.init_RotXZ_3x3(XZoff_angle);
	mat.Rotate_XZ_3x3(axis, axis);
	mat.Rotate_XZ_3x3(this, this);

	mat.init_RotXY_3x3(XYoff_angle);
	mat.Rotate_XY_3x3(axis, axis);
	mat.Rotate_XY_3x3(this, this);
}

Vector Vector::AddVectorToVector(Vector* vec_in)
{
	Vector out;
	out.tuple[0] = tuple[0] + vec_in->tuple[0];
	out.tuple[1] = tuple[1] + vec_in->tuple[1];
	out.tuple[2] = tuple[2] + vec_in->tuple[2];
	return out;
}
Vector Vector::SubtractVectorFromVector(Vector* vec_in)
{
	Vector out;
	out.tuple[0] = tuple[0] - vec_in->tuple[0];
	out.tuple[1] = tuple[1] - vec_in->tuple[1];
	out.tuple[2] = tuple[2] - vec_in->tuple[2];
	return out;
}

Vector Vector::DivideVectorByScalar(float in_scalar)
{
	Vector out;

	out.tuple[0] = tuple[0] / in_scalar;
	out.tuple[1] = tuple[1] / in_scalar;
	out.tuple[2] = tuple[2] / in_scalar;
	return out;
}

Vector Vector::MultiplyVectorByScalar(float in_scalar)
{
	Vector out;

	out.tuple[0] = tuple[0] * in_scalar;
	out.tuple[1] = tuple[1] * in_scalar;
	out.tuple[2] = tuple[2] * in_scalar;
	return out;
}

Vector Vector::CrossProduct(Vector* vec_in)
{
	//note: should use a determinant matrix whenever I've figured that out...
	Vector out;
	out.tuple[0] = (tuple[1] * vec_in->tuple[2]) - (tuple[2] * vec_in->tuple[1]);
	out.tuple[1] = (tuple[2] * vec_in->tuple[0]) - (tuple[0] * vec_in->tuple[2]);
	out.tuple[2] = (tuple[0] * vec_in->tuple[1]) - (tuple[1] * vec_in->tuple[0]);



	return out;
}
float Vector::DotProduct(Vector* vec_in)
{
	float d = 0.0;
	d += tuple[0] * vec_in->tuple[0];
	d += tuple[1] * vec_in->tuple[1];
	d += tuple[2] * vec_in->tuple[2];

	return d;
}

bool Vector::isOpp(Vector* vec_in)
{
	//This will check the signs of each tuple of this vector and the given vector. If there is any opposition, then returns true;
	bool opp = false;
	int c = 0;
	for (int i = 0; i < 3; i++)
	{
		if ((tuple[i] < 0 && vec_in->tuple[i] > 0) || (tuple[i] > 0 && vec_in->tuple[i] < 0))
		{
			c++;
		}
	}
	if (c >= 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

float Vector::get_size()
{
	float size = sqrt(pow(tuple[0], 2) + pow(tuple[1], 2) + pow(tuple[2], 2));
	return size;
}