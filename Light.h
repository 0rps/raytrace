#ifndef LIGHT_H
#define LIGHT_H
#include "MyVector3.h"

class Light {
public:
    Light() {
        color = float3(255,255,255);
    };
public:
	float3 color;
	float3 pos;
    friend QDataStream & operator<< (QDataStream &out, const Light &light) ;
    friend QDataStream & operator>> (QDataStream &out, Light &light) ;
};

#endif
