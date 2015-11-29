#include "Intersection.h"

Hit::Hit() 
{
    exist = false;
}
void Hit::operator = (const Hit& hit) 
{
	normal = hit.normal;
	distance = hit.distance;
	material = hit.material;
	exist = hit.exist;
}

void Hit::FindPosition(const Ray &ray) 
{
	if (exist)
		pos = ray.pos + ray.dir * distance;
}
