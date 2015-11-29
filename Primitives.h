#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include "MyVector3.h"
#include "LightRay.h"
#include "Material.h"
#include "Light.h"
#include "Constants.h"

class Primitive 
{
public:
	Primitive() {};
public:
	Material material;
public:
	Material GetMaterial() const { return material;}
	virtual float3	FindMaxBound() const = 0;
	virtual float3	FindMinBound() const = 0;
    virtual bool	FindIntersection(const Ray &ray, float &dist) const = 0;
	virtual float3	GetNormal(const Ray& ray, const float dist) = 0;
public:
	virtual ~Primitive() {};
};

class Sphere : public Primitive 
{
public:
	Sphere() {};
	Sphere(float3 pt, int r);
	Sphere(const Sphere &sphere);
	Sphere(const Light &light);
public:
	float3 pos;
	int radius;
public:
	void operator = (const Sphere &sphere);
	float3 FindMaxBound() const;
	float3 FindMinBound() const;
	float3 GetNormal(const Ray &ray, const float dist);
    bool FindIntersection(const Ray &ray, float & dist) const;
    friend QDataStream & operator<< (QDataStream &out, const Sphere &sphere);
    friend QDataStream & operator>> (QDataStream &in, Sphere &sphere);
};

class Triangle: public Primitive
{
public:
	Triangle() {};
	Triangle(const Triangle& triangle);
public:
	float3 vertex[3];
	float3 normal;
public:
	void operator = (const Triangle &triangle);
	void Init();
	float3 FindMaxBound() const;
	float3 FindMinBound() const;
	float3 GetNormal(const Ray &ray, const float dist);
    bool FindIntersection(const Ray &ray, float & dist) const;
    bool FindPlaneIntersection(const Ray &ray, float & dist)const;
    friend QDataStream & operator<< (QDataStream &out, const Triangle &tr);
    friend QDataStream & operator>> (QDataStream &in, Triangle &tr);
private:
	float f1,f2,f3;		// plane intersection intermediate variables
private:
	float3 FindNormal();
};

float FindF(const float3 * vertex, int num);

#endif
