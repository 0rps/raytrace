#ifndef MATERIAL_H
#define MATERIAL_H

#include "MyVector3.h"

class Material 
{
public:
	Material() ;
	Material(const Material &material);
public:
	float3 color;
    bool isLight;
    float fong;
    int fongPower;
    float lambert;
    int id;
	float diffusion;
	float reflection;
public:
	void operator = (const Material &material);
public:
	float GetDiffusionValue()	const;
	float GetReflectionValue()	const;
    void SetDiffusionValue(const float value);
	void SetReflectionValue(const float value);	
    friend QDataStream & operator>> (QDataStream &out, Material &m) ;
};

#endif
