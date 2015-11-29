#include "LightRay.h"

Ray::Ray() {
	
}

Ray::Ray(float3 _pos, float3 _dir) {
	pos = _pos;
	dir = _dir;
}

Ray Ray::Reflect(float3 pt, float3 normal) {
	Ray ray;
	ray.dir = normal * dot(normal,-dir) * 2 + dir;
	ray.dir.Normalize();
	ray.pos = pt + ray.dir * 0.01;
	return ray;
}

Ray Ray::Reflect(float3 pt, float3 normal) const {
	Ray ray;
	ray.dir = normal * dot(normal,-dir) * 2 + dir;
	ray.dir.Normalize();
	ray.pos = pt + ray.dir * 0.01;
	return ray;
}
