#include "Primitives.h"

Sphere::Sphere(float3 pt, int r) 
{
	pos = pt;
	radius = r;
}

Sphere::Sphere(const Sphere &sphere) 
{
	(*this) = sphere;
}

Sphere::Sphere(const Light& light) 
{
	pos = light.pos;
	material.color = light.color;
    material.isLight = true;
	radius = constLightRadius; 

}

void Sphere::operator = (const Sphere &sphere) 
{
	pos = sphere.pos;
	radius = sphere.radius;
	material = sphere.material;
}

bool Sphere::FindIntersection(const Ray &ray, float &dist) const
{
	float3 k = ray.pos - pos;
	float b = dot(ray.dir,k) ;
	float c = dot(k,k) - radius * radius;
	float d = b*b - c;
	if (d < 0)
        return false;
	float t1 = -b - sqrtf(d);
	float t2 = -b + sqrtf(d);
	if (t1 < 0 && t2 < 0)
        return false;
	if (t1 >= 0 && t2 >= 0) 
        dist = qMin(t1,t2);
	
	if (t1 >= 0 && t2 < 0)
		dist = t1;
	if (t2 >= 0 && t1 < 0)
		dist = t2;

    return true;
}

float3 Sphere::FindMaxBound() const 
{
	return pos + float3(radius, radius, radius);
}

float3 Sphere::FindMinBound() const 
{
	return pos - float3(radius, radius, radius);
}

float3 Sphere::GetNormal(const Ray &ray, const float dist) 
{
	float3 pt = ray.pos + ray.dir*dist;
	return (pt-pos).Normalize();
}

float FindF(const float3 * vertex, int num) 
{
	float3 a = vertex[0];
	float3 b = vertex[1];
	float3 c = vertex[2];
	float res;
	if (num == 1) 
		res =	(b[1] - a[1]) * (c[2] - a[2]) - 
				(c[1] - a[1]) * (b[2] - a[2]);
	else if (num == 2)
		res =	(b[0] - a[0]) * (c[2] - a[2]) - 
				(c[0] - a[0]) * (b[2] - a[2]);
	else if (num == 3)
		res =	(b[0] - a[0]) * (c[1] - a[1]) - 
				(b[1] - a[1]) * (c[0] - a[0]);
	return res;
}

void Triangle::operator = (const Triangle& triangle) 
{
	for (int i = 0; i < 3; i++)
		vertex[i] = triangle.vertex[i];

	material = triangle.material;
	normal = triangle.normal;
	f1 = triangle.f1;
	f2 = triangle.f2;
	f3 = triangle.f3;
}

Triangle::Triangle(const Triangle& triangle) 
{
	(*this) = triangle;
}

void Triangle::Init() 
{
	f1 = FindF(vertex,1);
	f2 = FindF(vertex,2);
	f3 = FindF(vertex,3);
	FindNormal();
	normal.Normalize();
}

float3 Triangle::FindMaxBound() const 
{
	float3 result;
	for (int i = 0; i < 3; i++)
        result.values[i] = qMax(qMax(vertex[0][i], vertex[1][i]),vertex[2][i]);
	return result;
}

float3 Triangle::FindMinBound() const 
{
	float3 result;
	for (int i = 0; i < 3; i++)
        result.values[i] = qMin(qMin(vertex[0][i], vertex[1][i]),vertex[2][i]);
	return result;
}

bool Triangle::FindPlaneIntersection(const Ray &ray, float & dist) const
{
	float del = f1*ray.dir[0] - f2*ray.dir[1] + f3*ray.dir[2];
	
	if (abs(del) < 0.01)
        return false;
	
	float x,y,z;	
	x = ray.pos[0] - vertex[0][0];
	y = ray.pos[1] - vertex[0][1];
	z = ray.pos[2] - vertex[0][2];
	dist = (y*f2 - x*f1 - z*f3) / del;
	
	if (dist < 0)
        return false;
	
    return true;
}

// method of oriented volume of paralleliped
// built on 2 sides of triangle and its normal
bool Triangle::FindIntersection(const Ray &ray, float &dist) const
{
    bool res = true;
	float3 point;
	if (FindPlaneIntersection(ray,dist)) 
	{
		point = ray.dir * dist + ray.pos;
		float d1 = FindDeterminant(point - vertex[0], vertex[1] - vertex[0], normal);
		float d2 = FindDeterminant(point - vertex[1], vertex[2] - vertex[1], normal);
		float d3 = FindDeterminant(point - vertex[2], vertex[0] - vertex[2], normal);
		if ( !((d1 >=0 && d2 >=0 && d3 >=0) ||
			(d1 <= 0 && d2 <= 0 && d3 <= 0)) )
            res = false;
	} 
	else
        res = false;
	return res;
}

float3 Triangle::GetNormal(const Ray &ray, const float dist) 
{
	if (dot(normal, ray.dir) > 0 ) 
		normal *= -1;
	return normal;
}

float3 Triangle::FindNormal() 
{
	float3 a = vertex[1] - vertex[0];
	float3 b = vertex[2] - vertex[0];
	normal = cross(a,b);

	return normal;
}
