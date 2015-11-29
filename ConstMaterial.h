#ifndef CONST_MATERIAL_H
#define CONST_MATERIAL_H
#include "Material.h"

class ConstMaterial
{
public:
    ConstMaterial()
    {
        InitWood();
        InitPlastic();
        InitMetal();
        InitMirror();
    }
private:
    void InitMirror()
    {
        mirror.SetDiffusionValue(0);
        mirror.SetReflectionValue(1);
        mirror.id = 3;
    }
    void InitWood()
    {
        wood.SetDiffusionValue(1);
        wood.fong = 0;
        wood.lambert = 1;
        wood.SetReflectionValue(0);
        wood.id = 2;
    }
    void InitPlastic()
    {
        plastic.SetDiffusionValue(1);
        plastic.SetReflectionValue(0);
        plastic.fongPower = 7;
        plastic.lambert = 0.6;
        plastic.fong = 0.4;
        plastic.id = 1;
    }
    void InitMetal()
    {
        // good
        // dif = 0.6
        // refl = 0.4
        // fong 0.5
        // lamb = 0.5
        // fongpow = 6
        metal.SetDiffusionValue(0.6);
        metal.SetReflectionValue(0.35);
        metal.fong = 0.8;
        metal.fongPower = 6;
        metal.lambert = 0.4;
        metal.id = 0;
    }
public:
    Material mirror;
    Material metal;
    Material wood;
    Material plastic;
};

static const ConstMaterial constMaterial;

#endif
