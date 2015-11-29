#include "AABB.h"

AABB::AABB ()
{

	maxBound = float3(INT_MIN, INT_MIN, INT_MIN);
	minBound = float3(INT_MAX, INT_MAX, INT_MAX);
}

AABB::AABB(const AABB &_box) 
{
	(*this) = _box;
}

void AABB::operator= (const AABB &box) 
{
	maxBound = box.maxBound;
	minBound = box.minBound;
}

void AABB::Reset() 
{
	maxBound = float3(INT_MIN, INT_MIN, INT_MIN);
	minBound = float3(INT_MAX, INT_MAX, INT_MAX);
}

void AABB::Include(const Primitive *a) 
{
	float3 tempMax = a->FindMaxBound();
	float3 tempMin = a->FindMinBound();
	for (int i = 0; i <3 ; i++) 
	{
        minBound.values[i] = qMin(minBound[i], tempMin[i]);
        maxBound.values[i] = qMax(maxBound[i], tempMax[i]);
	}
}

float AABB::GetSurfaceArea() const
{
	float xLen = maxBound[0] - minBound[0];
	float yLen = maxBound[1] - minBound[1];
	float zLen = maxBound[2] - minBound[2];
	float square = 2 * (xLen * yLen + xLen*zLen + zLen*yLen);

	return square;
}

bool AABB::IsIntersect(const Ray &ray)
{
	float minArg, maxArg;
	float minTemp, maxTemp;
	for (int i = 0; i < 3; i++) 
	{
		if (ray.dir[i] == 0)
			if (ray.pos[i] < minBound[i] || ray.pos[i] > maxBound[i])
                return false;
	}
	minTemp = (minBound[0] - ray.pos[0]) / ray.dir[0];
	maxTemp = (maxBound[0] - ray.pos[0]) / ray.dir[0];
    minArg = qMin(minTemp, maxTemp);
    maxArg = qMax(minTemp, maxTemp);

	minTemp = (minBound[1] - ray.pos[1]) / ray.dir[1];
	maxTemp = (maxBound[1] - ray.pos[1]) / ray.dir[1];
    minArg = qMax(minArg,qMin(minTemp, maxTemp));
    maxArg = qMin(maxArg,qMax(minTemp, maxTemp));

	minTemp = (minBound[2] - ray.pos[2]) / ray.dir[2];
	maxTemp = (maxBound[2] - ray.pos[2]) / ray.dir[2];
    minArg = qMax(minArg,qMin(minTemp, maxTemp));
    maxArg = qMin(maxArg,qMax(minTemp, maxTemp));

	return (maxArg >= 0 && maxArg >= minArg);
}

AABB FindSceneBox(const std::vector<Primitive*> &objects) 
{
	AABB result;
	for (int i = 0; i < objects.size(); i++)
		result.Include(objects[i]);
	return result;
}
