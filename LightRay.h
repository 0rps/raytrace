#ifndef TRACERAY_H
#define TRACERAY_H
#include "MyVector3.h"

class Ray 
{
public:
	Ray();
	Ray(float3 _pt, float3 _dir);
public:
	float3 pos;
	float3 dir;
public:
	Ray Reflect(float3 pt, float3 normal);
	Ray Reflect(float3 pt, float3 normal) const;
};

inline float3 ReflectVector(const float3 &dir, const float3 normal) 
{
	return (normal * dot(normal, -dir) * 2 + dir);
}

#endif