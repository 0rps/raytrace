#ifndef MATRIX_OPERATIONS_H
#define MATRIX_OPERATIONS_H

#include "MyVector3.h"

struct MATRIX {
	float m[3][3];
};

void MulPoint(float3 &a, const MATRIX m);
void RotateY(float3 &a,const double angle);
void RotateZ(float3 &a,const double angle);
void RotateX(float3 &a,const double angle);
void Rotate(float3 &a, float* angle);
#endif