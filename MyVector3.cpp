#include "MyVector3.h"

float3::float3() 
{	
}

float3::float3( float a, float b, float c) 
{
	values[0] = a; values[1] = b; values[2] = c;
}

float3 float3::operator- () const 
{
	return (*this) * (-1);
}


float3 float3::operator- (const float3 &a) const 
{
	float3 b(	-a.values[0] + values[0],
		-a.values[1] + values[1],
		-a.values[2] + values[2]);
	return b;	
}

void float3::operator-= (const float3 &a) 
{
	for (int i = 0; i < 3; i++)
		values[i] -= a.values[i];
}


float3 float3::operator+ (const float3 &a) const 
{
	float3 b(	a.values[0] + values[0],
		a.values[1] + values[1],
		a.values[2] + values[2]);
	return b;
}

void float3::operator+= (const float3 &a) 
{
	for (int i = 0; i < 3; i++)
		values[i] += a.values[i];
}

void float3::operator= (const float3 &a) 
{
	for (int i = 0; i < 3; i++) 
		values[i] = a.values[i];
}


float3 float3::operator* (const float3 &a) const 
{
	float3 res;
	for (int i = 0; i < 3; i++)
		res.values[i] = values[i]*a.values[i];
	return res;
}

float3 float3::operator* (float a) const 
{
	float3 res;
	for (int i = 0; i < 3; i++)
		res.values[i] = values[i] * a;
	return res;
}

void float3::operator*= (float a) 
{
	for (int i = 0; i < 3; i++)
		values[i] *= a;
}

bool float3::operator== (const float3 &a) const
{
    bool result = true;
    for (int i = 0; i < 3; i++) {
        //float b = values[i] - a[i];
        //b = fabs(b);
        if (fabs(values[i]- a[i]) > 0.001)
		{
            result = false;
			break;
		}
    }
	return result;
}

void float3::operator*= (const float3 &a) 
{
	for (int i = 0; i < 3; i++)
		values[i] *= a.values[i];
}

void float3::operator/= (float a) 
{
	for (int i = 0; i < 3; i++)
		values[i] /= a;
}

float3 float3::operator/ (float a) const 
{
	float3 res;
	for (int i = 0; i < 3; i++)
		res.values[i] = values[i] / a;
	return res;
}

float3 float3::operator/ (const float3 &a) const 
{
	float3 result;
	for (int i = 0; i < 3; i++)
		result.values[i] = (*this)[i]/a[i];
	return result;
}

void float3::operator /= (const float3 &a) 
{
	for (int i = 0; i < 3; i++)
		(*this).values[i] = (*this)[i]/a[i];
}

float float3::operator[] (int i) 
{
	return values[i];
}

float float3::operator[] (int i) const 
{
	return values[i];
}

float float3::Length() const
{
	float res = 0;
	for (int i = 0; i < 3; i++)
		res += pow(values[i],2);
	res = sqrtf(res);
	return res;
}

float3 float3::Normalize() {
	float length = Length();
	if (length > 0.001)
		for (int i = 0; i < 3; i++)
			values[i] /= length;
	return *this;
}

float dot(const float3 &a, const float3 &b) 
{
	float res = 0;
	for (int i = 0; i < 3; i++)
		res += a.values[i] * b.values[i];
	return res;
}

float3 cross(const float3 & a, const float3 & b) 
{
	float3 res;
	res.values[0] =  a[1]*b[2] - b[1]*a[2];
	res.values[1] = -a[0]*b[2] + a[2]*b[0];
	res.values[2] =  a[0]*b[1] - a[1]*b[0];
	return res;
}


float GetAngle(float3 a, float3 b, int axis) 
{
	const static float pi = 3.14159265;
	float result = 0;
	a.values[axis] = 0;
	b.values[axis] = 0;
	
	a.Normalize();
	b.Normalize();
	if ( (b == float3(0,0,0)) || (a == float3(0,0,0)))
		return result;
	result = acos(dot(a,b));
	float3 c = cross(a,b);

	if (c[axis] < 0) {
		result = 2*pi - result;
	}
	return result;
}
