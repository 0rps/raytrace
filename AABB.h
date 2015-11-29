#ifndef AABB_H
#define AABB_H

#include "MyVector3.h"
#include "Primitives.h"
#include <vector>

class AABB 
{
public:
	AABB ();
	AABB(const AABB &_box); 
public:
	void operator= (const AABB &box);
	void Reset(); 
	float GetSurfaceArea() const;
	void Include(const Primitive *a); 
    bool IsIntersect(const Ray &ray);

public:
	float3 minBound;
	float3 maxBound;
};

AABB FindSceneBox(const std::vector<Primitive*> &objects);
#endif
