#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "MyVector3.h"
#include "LightRay.h"
#include "Material.h"

class Hit 
{
public:	
	Hit();
public:
	void operator = (const Hit& hit) ;
	void FindPosition(const Ray &ray);
public:
    bool	exist;
	float	distance;
	float3	pos;
	float3	normal;
	Material material;
};


#endif
