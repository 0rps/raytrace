#include "MatrixOperations.h"

void MulPoint(float3 &a, const MATRIX m) {
	float3 temp = a;
	for (int i = 0; i < 3; i++) {
		a.values[i] = 0;
		for (int j = 0; j < 3; j++) 
		{
			a.values[i] += m.m[i][j] * temp[j];
		}
	}
}

void RotateX(float3 &a,const double angle) {
	MATRIX m = {{
		{1,0,0},
		{0,cos(angle), -sin(angle)},
		{0,sin(angle), cos(angle)}
	}};
	MulPoint(a,m);
}

void RotateY(float3 &a,const double angle) {
	MATRIX m = {{
		{cos(angle), 0, sin(angle)},
		{0, 1, 0},
		{-sin(angle), 0, cos(angle)}
	}};
	MulPoint(a,m);
}

void RotateZ(float3 &a,const double angle) {
	MATRIX m = {{
		{cos(angle), -sin(angle),0},
		{sin(angle), cos(angle),0},
		{0, 0, 1}
	}};
	MulPoint(a,m);

}

void Rotate(float3 &a, float* angle) 
{
	if (angle[1] != 0)
		RotateY(a,angle[1]);
	if (angle[0] != 0)
		RotateX(a, angle[0]);
	if (angle[2] != 0)
		RotateZ(a,angle[2]);

}
