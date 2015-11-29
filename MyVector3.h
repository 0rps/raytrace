#ifndef MYVECTOR3_H
#define MYVECTOR3_H
#include <math.h>
#include <limits.h>
#include <QWidget>
#include <QDataStream>
//#include "RWObjects.h"

class float3 {
public:
	float3();
	float3(float a, float b,float c);
public:
	float values[3];
public:
	float3	operator-	(const float3 &a) const;
	float3	operator+	(const float3 &a) const;
	float3	operator*	(const float3 &a) const; 
	float3	operator*	(float a) const;
	float3	operator/	(float a) const;
	float3	operator/	(const float3 &a) const;
	void	operator=	(const float3 &a);
    bool    operator==	(const float3 &a) const;
	void	operator-=	(const float3 &a);
	void	operator+=	(const float3 &a);
	void	operator/=	(float a);
	void	operator/=	(const float3 &a);
	void	operator*=	(float a);
	void	operator*=	(const float3 &a);
	float3	operator-	() const;
	float	operator[]	(int);
	float	operator[]	(int) const;

	float Length() const;
	float3 Normalize();
    friend QDataStream & operator<< (QDataStream &out, const float3 &_float3);
    friend QDataStream & operator>> (QDataStream &out, float3 &_float3);
};

float dot(const float3 &a, const float3 &b);
float3 cross(const float3 &a, const float3 &b);
inline float FindDeterminant(const float3 &a, const float3 &b, const float3 &c) {
	return	(a[0] * (b[1]*c[2] - c[1]*b[2]) - 
		a[1]*(b[0]*c[2] - b[2]*c[0]) + 
		a[2]*(b[0]*c[1] - b[1]*c[0]));
}

float GetAngle(float3 a, float3 b, int axis);

#endif
