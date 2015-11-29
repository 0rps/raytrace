#include "RWObjects.h"


QDataStream & operator<< (QDataStream &out, const Sphere &sphere)
{
    out << sphere.material;
    out << sphere.pos;
    out << sphere.radius;
    return out;
}

QDataStream & operator>> (QDataStream &in,Sphere &sphere)
{
    in >> sphere.material;
    in >> sphere.pos;
    in >> sphere.radius;
    return in;
}

QDataStream & operator<< (QDataStream &out, const Triangle &tr)
{
    out << tr.f1;
    out << tr.f2;
    out << tr.f3;
    out << tr.material;
    out << tr.normal;
    for (int i = 0; i< 3 ; i++)
        out << tr.vertex[i];
    return out;
}

QDataStream & operator>> (QDataStream &in, Triangle &tr)
{
    in >> tr.f1;
    in >> tr.f2;
    in >> tr.f3;
    in >> tr.material;
    in >> tr.normal;
    for (int i = 0; i< 3 ; i++)
        in >> tr.vertex[i];
    return in;
}


QDataStream & operator<< (QDataStream &out, const float3 &a)
{
    for (int i = 0; i < 3; i++)
        out << a[i];
    return out;
}

QDataStream & operator>> (QDataStream &in, float3 &a)
{
    for (int i = 0; i < 3; i++)
        in >> a.values[i];
    return in;
}

QDataStream & operator<< (QDataStream &out, const Material &material)
{
    out <<material.color;
    out << material.diffusion;
    out << material.reflection;
    out << material.fong;
    out << material.fongPower;
    out << material.lambert;
    out << material.isLight;
    out << material.id;
    return out;
}

QDataStream & operator>> (QDataStream &in, Material &material)
{
    in >> material.color;
    in >> material.diffusion;
    in >> material.reflection;
    in >> material.fong;
    in >> material.fongPower;
    in >> material.lambert;
    in >> material.isLight;
    in >> material.id;
    return in;
}

QDataStream & operator<< (QDataStream &out, const Light &light)
{
    out << light.color;
    out << light.pos;
    return out;
}

QDataStream & operator>> (QDataStream &in, Light &light)
{
    in >> light.color;
    in >> light.pos;
    return in;
}


