#ifndef SCENE_H
#define SCENE_H
#include "Camera.h"
#include <vector>
#include "BVHTree.h"
#include "Intersection.h"
#include "Constants.h"
#include "ConstMaterial.h"
class Scene 
{
public:
	Scene();
public:
	std::vector<Primitive *> objects;
	std::vector<Primitive *> objectsWithLight;
	std::vector<Light>	lights;
	Camera camera;
	float3** matrixColor;
	BvhNode *bvhTree;
	BvhNode *bvhTreeWithLight;
    bool isDrawLight;
    bool isUseBvh;
    bool isUseSmooth;
public:
	void DrawScene() ;
    float3 FindColor(Ray &ray);
    float3 FindSmoothColor(const int x, const int y);
	void InitObjects();
    void InitObjectsWithLight();
	void InitBVH();
	void ClearObjects();
	void ClearBvhTree();
public:
	~Scene() 
	{
		if (objects.size() > 0 && objects[0] != NULL)
			ClearPrimitiveVector(objects);
		if (objectsWithLight.size() > 0 && objectsWithLight[0] != NULL)
			ClearPrimitiveVector(objectsWithLight);
		if (bvhTree != NULL)
			delete bvhTree;
		if (bvhTreeWithLight != NULL)
			delete bvhTreeWithLight;
		for (int i = 0; i < constHeight; i++)
			delete [] matrixColor[i];
		delete [] matrixColor;
	}
};

template<typename T>
float3 RayTrace(Ray &ray, int depth, std::vector<Light> &lights, T &objects, T &objWithLight);

template<typename T>
float3 RayTrace(Ray &ray, int depth, std::vector<Light> &lights, T &objects);

#endif
