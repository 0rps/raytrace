#include "VectorActions.h"

std::vector<Primitive*> CopyVectorPrimitive(const std::vector<Primitive*> objects, int beg, int count) 
{
	std::vector<Primitive*> result;
	Sphere* tempSphere;
	Triangle* tempTriangle;
	for (int i = beg; i < (beg+count); i++) 
	{
		tempSphere = dynamic_cast<Sphere *>(objects[i]);
		tempTriangle = dynamic_cast<Triangle *>(objects[i]);
        if (tempSphere != NULL)
			result.push_back(new Sphere(*tempSphere));
		else
			result.push_back(new Triangle(*tempTriangle));
	}
	return result;
}

void ClearPrimitiveVector(std::vector<Primitive*> &objects) 
{
	for (int i = 0; i < objects.size(); i++) 
		delete objects[i];
    objects.clear();
}
