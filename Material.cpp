#include "Material.h"

Material::Material() 
{
	diffusion = 0.9;
	reflection = 1 - diffusion;
    isLight = false;
    fongPower = 5;
    fong = 0.5;
    lambert = 0.5;
    id = -1;
}
Material::Material (const Material &material) 
{
	(*this) = material;
}
void Material::operator = (const Material &material) 
{
	color = material.color;
	reflection = material.reflection;
	diffusion = material.diffusion;
    fong = material.fong;
    lambert = material.lambert;
	isLight = material.isLight;
    fongPower = material.fongPower;
    id = material.id;
}

float Material::GetDiffusionValue()	const 
{ 
	return diffusion;
}

float Material::GetReflectionValue() const 
{ 
	return reflection;
}

void Material::SetDiffusionValue(const float value)	
{
	diffusion = value;
}

void Material::SetReflectionValue(const float value)	
{
	reflection = value;
}
