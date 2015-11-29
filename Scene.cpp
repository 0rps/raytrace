#include "Scene.h"
#include <math.h>
#include <vector>
#include <time.h>
#include "BVHTree.h"

std::vector<Primitive*> InitSphere() 
{

    std::vector<Primitive*> spheres;
	Sphere sphere;
    /*int d = 160;
    float3 pos(0,0,000);
    sphere.radius = 50;
    for (int k = 0; k <0; k++) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5 ; j++)
        {
            sphere.pos = pos + float3(-k*d,j*d,i*d);
            sphere.pos += float3(random()%100,random()%100, random()%25);
            if (j % 2 == 1)
                sphere.material = constMaterial.metal;
            else
            //sphere.material = constMaterial.plastic;
            sphere.material = constMaterial.metal;

            if ((j+i) % 4  == 0)
                sphere.material.color = float3(255,255,255);
            else if ((j+i) % 4 == 1)
                sphere.material.color = float3(255,0,0);
            else if ((j+i) % 4 == 2)
                sphere.material.color = float3(0,255,0);
            else
                sphere.material.color = float3(0,0,255);
            spheres.push_back(new Sphere(sphere));
        }
    }
    }*/


	return spheres;
}

Triangle Floor(int a1, int a2, int b) 
{
	Triangle tr;
    int d = 100;
    float3 p0(0,0,000);
    tr.material = constMaterial.metal;
	if ((a1+ a2) % 2 == 1) {
		tr.material.color = float3(255,255,255);
	} else {
		tr.material.color = float3(0,0,0);
	}
    p0.values[1] += a2*d;
    p0.values[0] -= a1*d;
	if (b == 0) {
        tr.vertex[2] = p0;
        tr.vertex[1] = p0 + float3(0,d,0);
        tr.vertex[0] = p0 - float3(d,0,0);
	} else {
        tr.vertex[2] = p0 + float3(-d,d,0);
        tr.vertex[1] = p0 + float3(0,d,0);
        tr.vertex[0] = p0 - float3(d,0,0);
    }
	tr.Init();
	return tr;
}
void GenerateBox(std::vector<Primitive *> & objects, const float3 &pt, int dx, int dy, int dz, Material &material)
{
    Triangle tr;
    float3 close_left_d = pt;
    float3 close_right_d =  close_left_d + float3(0,dy,0);
    float3 far_left_d =     close_left_d - float3(dx,0,0);
    float3 far_right_d =    close_right_d - float3(dx,0,0);

    float3 close_left_up =  close_left_d + float3(0,0,dz);
    float3 close_right_up = close_right_d + float3(0,0,dz);
    float3 far_left_up =    far_left_d + float3(0,0,dz);
    float3 far_right_up =   far_right_d + float3(0,0,dz);

    tr.material = material;
    //floor
    tr.vertex[0] = close_left_d;
    tr.vertex[1] = close_right_d;
    tr.vertex[2] = far_left_d;
    tr.Init();
    objects.push_back(new Triangle(tr));

    tr.vertex[0] = far_right_d;
    tr.vertex[1] = close_right_d;
    tr.vertex[2] = far_left_d;
    tr.Init();
    objects.push_back(new Triangle(tr));
    //roof
    tr.vertex[0] = close_left_up;
    tr.vertex[1] = close_right_up;
    tr.vertex[2] = far_left_up;
    tr.Init();
    objects.push_back(new Triangle(tr));

    tr.vertex[0] = far_right_up;
    tr.vertex[1] = close_right_up;
    tr.vertex[2] = far_left_up;
    tr.Init();
    objects.push_back(new Triangle(tr));
    // left side

    tr.vertex[0] = close_left_d;
    tr.vertex[1] = close_left_up;
    tr.vertex[2] = far_left_d;
    tr.Init();
    objects.push_back(new Triangle(tr));

    tr.vertex[0] = far_left_up;
    tr.vertex[1] = close_left_up;
    tr.vertex[2] = far_left_d;
    tr.Init();
    objects.push_back(new Triangle(tr));

    // right side

    tr.vertex[0] = close_right_d;
    tr.vertex[1] = close_right_up;
    tr.vertex[2] = far_right_d;
    tr.Init();
    objects.push_back(new Triangle(tr));

    tr.vertex[0] = far_right_up;
    tr.vertex[1] = close_right_up;
    tr.vertex[2] = far_right_d;
    tr.Init();
    objects.push_back(new Triangle(tr));

    //back side

    tr.vertex[0] = far_left_d;
    tr.vertex[1] = far_left_up;
    tr.vertex[2] = far_right_up;
    tr.Init();
    objects.push_back(new Triangle(tr));

    tr.vertex[0] = far_left_d;
    tr.vertex[1] = far_right_d;
    tr.vertex[2] = far_right_up;
    tr.Init();
    objects.push_back(new Triangle(tr));

    //front side

    tr.vertex[0] = close_left_d;
    tr.vertex[1] = close_left_up;
    tr.vertex[2] = close_right_up;
    tr.Init();
    objects.push_back(new Triangle(tr));

    tr.vertex[0] = close_right_d;
    tr.vertex[1] = close_left_d;
    tr.vertex[2] = close_right_up;
    tr.Init();
    objects.push_back(new Triangle(tr));
}

void GeneratePyramide(std::vector<Primitive *> & objects, float3 pt, int height, int d)
{
    Triangle tr;
    pt = pt - float3(0,0,1);
    height += 1;
    float3 close_left = pt;
    float3 close_right = pt + float3(0,d,0);
    float3 far_left = pt - float3(d,0,0);
    float3 far_right = close_right - float3(d,0,0);
    float3 peak = pt + float3(-d/2,d/2,height);

    tr.material = constMaterial.plastic;
    tr.material.color = float3(255,255,0);
    tr.vertex[0] = close_left;
    tr.vertex[1] = far_left;
    tr.vertex[2] = peak;
    tr.Init();
    objects.push_back(new Triangle(tr));

    tr.vertex[0] = far_right;
    tr.vertex[1] = far_left;
    tr.vertex[2] = peak;
    tr.Init();
    objects.push_back(new Triangle(tr));

    tr.vertex[0] = far_right;
    tr.vertex[1] = close_right;
    tr.vertex[2] = peak;
    tr.Init();
    objects.push_back(new Triangle(tr));

    tr.vertex[0] = close_left;
    tr.vertex[1] = close_right;
    tr.vertex[2] = peak;
    tr.Init();
    objects.push_back(new Triangle(tr));
}

void GenerateMirror(std::vector<Primitive *> & objects)
{
    //3500 - -3500,-2500 - 2500, -2500 - 500
    Triangle tr;
    float3 pt = float3(-3480,-900,-2000);
    int leny = 2500;
    int lenz = 2000;
    int d = 100;
    Material mat = constMaterial.plastic;
    mat.color = float3(200,150,100);
    GenerateBox(objects,pt,d,d,lenz + 2*d,mat);
    GenerateBox(objects,pt,d,leny+2*d,d,mat);
    GenerateBox(objects,pt+float3(0,leny + d,0),d,d,lenz + 2*d,mat);
    GenerateBox(objects,pt + float3(0,0,d+lenz),d,leny+2*d,d,mat);

    mat = constMaterial.mirror;
    tr.material = mat;
    pt += float3(0,d,d);

    tr.vertex[0] = pt;
    tr.vertex[1] = pt + float3(0,leny,0);
    tr.vertex[2] = pt + float3(0,0,lenz);
    tr.Init();
    objects.push_back(new Triangle(tr));

    tr.vertex[0] = pt + float3(0,leny,lenz);
    tr.vertex[1] = pt + float3(0,leny,0);
    tr.vertex[2] = pt + float3(0,0,lenz);
    tr.Init();
    objects.push_back(new Triangle(tr));
}

void GenerateOther(std::vector<Primitive *> & objects)
{
    float3 pt = float3(-500,-900,-1300);
    int d = 600;
    int step = 150;
    GeneratePyramide(objects,pt,d,d);
    Sphere sp;
    sp.material = constMaterial.metal;
    sp.material.color = float3(255,0,0);
    sp.radius = d/2;
    pt += float3(0,d+step,0);
    sp.pos = pt + float3(-d/2,d/2,d/2);
    objects.push_back(new Sphere(sp));
    pt += float3(0,d+step,0);
    Material material = constMaterial.metal;
    material.color = float3(255,255,255);
    GenerateBox(objects,pt,d,d,d,material);
    GenerateMirror(objects);
}

void GenerateTable(std::vector<Primitive *> & objects) {
    Material material;
    material = constMaterial.wood;
    material.color = float3(0,255,100);

    int x,y,z,dx,dy,dz;
    x = 0000;
    y = -1000;
    z = -1502;
    GenerateBox(objects, float3(x,y,z),1500,2500,202,material);
    //legs
    GenerateBox(objects, float3(x,          y,-2500),200,200,1000,material);
    GenerateBox(objects, float3(x - 1300,   y,-2500),200,200,1000,material);
    GenerateBox(objects, float3(x - 1300,   y + 2300,-2500),200,200,1000,material);
    GenerateBox(objects, float3(x,          y + 2300,-2500),200,200,1000,material);
    GenerateOther(objects);
}

void InitTriangle(std::vector<Primitive *> & objects)
{
    Triangle tr;
    /*for (int i = 0; i < 00; i++) {
        for (int j = 0; j < 20; j++)
		{
			tr = Floor(i,j,0);
			objects.push_back(new Triangle(tr));
			tr = Floor(i,j,1);
			objects.push_back(new Triangle(tr));
		}
    }*/
    Material material;
    material = constMaterial.wood;
    material.color = float3(100,100,255);
    GenerateBox(objects,float3(3500,-2500,-2500),7000,5000,3000,material);
    GenerateTable(objects);
}

std::vector<Light> InitLights() {
	std::vector<Light> lights;
	Light light;
    light.pos = float3(-3000,1000, -1000);
	light.color = float3(255,255,255);
    lights.push_back(light);
	
    light.pos = float3(700,400,000);
	light.color = float3(255,255,255);
	lights.push_back(light);

	return lights;
}

void Scene::ClearBvhTree() 
{
	if (bvhTree != NULL) {
		delete bvhTree;
		bvhTree = NULL;
	}
	if (bvhTreeWithLight != NULL) {
		delete bvhTreeWithLight;
		bvhTreeWithLight = NULL;
	}
}

void Scene::ClearObjects() 
{
	if (objects.size() > 0 && objects[0] != NULL)
		ClearPrimitiveVector(objects);
	if (objectsWithLight.size() > 0 && objectsWithLight[0] != NULL)
		ClearPrimitiveVector(objectsWithLight);
}

void InitCamera(Camera &camera) {
	camera.screenDistance = 500;
	camera.screenVector.Normalize();
	camera.Init();
}

void Scene::InitObjects () 
{
	lights = InitLights();
	objects = InitSphere();
	InitTriangle(objects);
    InitObjectsWithLight();
}

void Scene::InitObjectsWithLight()
{
    if (objectsWithLight.size() != 0)
        ClearPrimitiveVector(objectsWithLight);
    objectsWithLight = CopyVectorPrimitive(objects,0,objects.size());
    for (int i = 0; i < lights.size(); i++)
        objectsWithLight.push_back(new Sphere(lights[i]));
}

void Scene::InitBVH() 
{
	AABB box = FindSceneBox(objects);
	bvhTree = GenerateBvhNode(box,objects, 1);
	if (isDrawLight) {
		AABB boxLights = FindSceneBox(objectsWithLight);
		bvhTreeWithLight = GenerateBvhNode(boxLights, objectsWithLight,1);
	}
}

Scene::Scene() {
	bvhTree = NULL;
	bvhTreeWithLight = NULL;
	matrixColor = new float3* [constHeight];
	for (int i = 0; i < constHeight; i++)
		matrixColor[i] = new float3 [constWidth];
	
	InitObjects();
};

float3 Scene::FindColor(Ray &ray)
{
    float3 color;
    if (isUseBvh)
    {
        if (isDrawLight)
            color = RayTrace(ray, constRayTraceDepth, lights, bvhTree, bvhTreeWithLight);
        else
            color = RayTrace(ray, constRayTraceDepth, lights, bvhTree);
    } else {
        if (isDrawLight)
            color = RayTrace(ray, constRayTraceDepth, lights, objects, objectsWithLight);
        else
            color = RayTrace(ray, constRayTraceDepth, lights, objects);
    }
    return color;
}

float3 Scene::FindSmoothColor(const int x, const int y)
{
    int maxPower = 3;
    float delta = (float)1 / (float)maxPower;
    float3 color(0,0,0);
    Ray ray;
    for (int i = 0; i < maxPower; i++)
        for (int j = 0; j < maxPower; j++)
        {
            //float newj = j*delta;
            //float newx = x + newx;
            ray = camera.GetRay(x + (float)j*delta,y + (float)i*delta);
            color += FindColor(ray);

        }
    return (color/(maxPower * maxPower));
}

void Scene::DrawScene() {
	float3 color;
	Ray ray;
	float maxColor = 255;
	InitCamera(camera);

	for (int i = 0; i < camera.screenHeight; i++) {
		for (int j = 0; j < camera.screenWidth; j++) 
		{
            if (isUseSmooth)
                color = FindSmoothColor(j,i);
            else
            {
                ray = camera.GetRay(j,i);
                color = FindColor(ray);
            }
            maxColor = qMax(qMax(qMax(color[0],color[1]), color[2]), maxColor);
			matrixColor[i][j] = color;
		}
	}

	for (int i = 0; i < camera.screenHeight; i++)
		for (int j = 0; j < camera.screenWidth; j++) {
			matrixColor[i][j] *= (255 / maxColor);
		}
}

Hit FindIntersection(const Ray &ray, std::vector<Primitive*> & objects) 
{
	Hit hit;
	float distance;
	hit.distance = INT_MAX;
	
	for (int i = 0; i < objects.size(); i++) 
	{
		if (objects[i]->FindIntersection(ray, distance)) 
			if (hit.distance > distance && hit.distance > errorRange) 
			{
                hit.exist = true;
				hit.distance = distance;
				hit.normal = objects[i]->GetNormal(ray, distance); 
                hit.material = objects[i]->GetMaterial();
			}
	}
	hit.FindPosition(ray);
	return hit;
}

Hit FindIntersection(const Ray &ray, BvhNode* tree) 
{
	Hit hit;
	float distance;
	hit.distance = INT_MAX;

	std::vector<Primitive *> objects;
	TraverseBvhTree(tree, ray, objects);

	for (int i = 0; i < objects.size(); i++) 
	{
		if (objects[i]->FindIntersection(ray, distance)) 
			if (hit.distance > distance && hit.distance > errorRange) 
			{
                hit.exist = true;
				hit.distance = distance;
				hit.normal = objects[i]->GetNormal(ray, distance); 
				hit.material = objects[i]->GetMaterial();
			}
	}
	hit.FindPosition(ray);
	return hit;
}

template<typename T>
bool Visible(const float3 &pt, const float3 &n,const Ray &viewRay, const Light &light, T &objects) {
    bool result = true;
	
	Ray ray;
	float distance;

	ray.pos = light.pos;
	ray.dir = pt - light.pos ;
	distance = ray.dir.Length();
	ray.dir.Normalize();
	if ((dot(n,viewRay.dir) * dot(ray.dir, n)) < 0)
        result = true;
	else 
	{
		Hit hit = FindIntersection(ray, objects);
		if (hit.exist && hit.distance < (distance - errorRange))
            result = false;
	}
	return result;
}

float LamberLight(const Hit &hit, const Light &light) {
	float coeff = dot((light.pos - hit.pos).Normalize(), hit.normal);
    return qMax(coeff,(float)0);
}

float FongLight(const Hit &hit, const float3 &dir, const Light &light) 
{
	float3 lightDir = (light.pos - hit.pos).Normalize();
	float3 reflectDir = ReflectVector(dir,hit.normal);
	// mb kill reflect dir and use -dir;
    return (pow(qMax ((float)0, dot(lightDir, reflectDir)), hit.material.fongPower));
}

float3 DiffusionColor(const Hit &hit, const Ray &ray, const Light &light) 
{
    //static const float constFong = 0.4;
    //static const float constLambert = 1 - constFong;
	static const float maxIntensity = 255;

	float3 color = blackColor;

	if (hit.material.GetDiffusionValue() > 0) 
	{
		float3 tempColor = hit.material.color;
		tempColor *= light.color / maxIntensity;
        color += tempColor * hit.material.fong * FongLight(hit, ray.dir, light);
        color += tempColor * hit.material.lambert * LamberLight(hit, light);
		color *= hit.material.GetDiffusionValue();
	}

	return color;
}

template<typename T>
float3 ReflectionColor(const Ray& ray, const Hit &hit, std::vector<Light> &lights, T &objects, int depth) 
{
	
	float3 color = blackColor;
	if (hit.material.GetReflectionValue() > 0) 
	{
		Ray reflectRay = ray.Reflect(hit.pos, hit.normal);
		float3 reflectColor = RayTrace(reflectRay, depth-1, lights, objects);
        color += reflectColor*hit.material.GetReflectionValue();
	}
	return color;
}

template<typename T>
float3 RayTrace(Ray &ray, int depth, std::vector<Light> &lights, T &objects) 
{	
		float3 color = blackColor;
		if (depth == 0) 
			return color;
		Hit hit = FindIntersection(ray, objects);
		if (hit.exist) {
			for (int i = 0; i < lights.size(); i++) 
			{
				if (Visible(hit.pos,hit.normal, ray, lights[i], objects)) 
				{	
					color += DiffusionColor(hit, ray, lights[i]);
				}
			}
			color += ReflectionColor(ray, hit, lights, objects, depth);
			
		}
		return color;
}

template<typename T>
float3 RayTrace(Ray &ray, int depth, std::vector<Light> &lights, T &objects, T &objWithLights) 
{
	static const float3 BlackColor(0,0,0);

	float3 color = BlackColor;
	if (depth == 0) 
		return color;
	Hit hit = FindIntersection(ray, objWithLights);
	if (hit.material.isLight) {
		return hit.material.color;
	} 
	if (hit.exist) {
		for (int i = 0; i < lights.size(); i++) {
		
			if (Visible(hit.pos,hit.normal, ray, lights[i], objects)) 
			{	
				color += DiffusionColor(hit, ray, lights[i]);
			}
		}
		color += ReflectionColor(ray, hit, lights, objects, depth);
	}
	return color;
}
