#ifndef BVHTREE_H
#define BVHTREE_H

#include "Primitives.h"
#include "AABB.h"
#include "VectorActions.h"
#include <vector>
#include <algorithm>

class BvhNode 
{
public:
	BvhNode(); 
	BvhNode(const AABB &_box);
public:
	BvhNode *leftNode;
	BvhNode *rightNode;
	AABB box;
	std::vector<Primitive*> objects;
private:
	BvhNode(const BvhNode& node) {};
	void operator= (const BvhNode& node) {};
public:
    bool IsLeaf() const;
public:
	~BvhNode();
};

class DivideData 
{
public:
	DivideData() {
		isDivided = false;
		divideAxis = -1;
	};
	int divideAxis;
	bool isDivided;
	int leftObjectsNum;
	int rightObjectsNum;
	AABB leftBox;
	AABB rightBox;
};

DivideData SplitObjects(const AABB &box, std::vector< std::vector<Primitive*> > &vectorList);
void TraverseBvhTree(BvhNode* node, const Ray &ray, std::vector<Primitive*> &objects);
BvhNode* GenerateBvhNode(const AABB &aBox, const std::vector<Primitive*> &objects, int depth);

#endif
