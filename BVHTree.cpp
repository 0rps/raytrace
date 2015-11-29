#include "BVHTree.h"

BvhNode::BvhNode() 
{
	leftNode = NULL;
	rightNode = NULL;
}

BvhNode::BvhNode(const AABB &_box) 
{
	leftNode = NULL;
	rightNode = NULL;
	box = _box;
}

bool BvhNode::IsLeaf() const {
	return (leftNode == NULL && rightNode == NULL);
}

BvhNode::~BvhNode() 
{
	ClearPrimitiveVector(objects);
	if (leftNode != NULL) {
		delete leftNode;
	}
	if (rightNode != NULL) {
		delete rightNode;
	}
}

bool ComparePrimitivesX(const Primitive *a, const Primitive *b)
{
	return ((a->FindMaxBound())[0] < (b->FindMaxBound())[0]);
}

bool ComparePrimitivesY(const Primitive *a, const Primitive *b)
{
	return ((a->FindMaxBound())[1] < (b->FindMaxBound())[1]);
}

bool ComparePrimitivesZ(const Primitive *a, const Primitive *b)
{
	return ((a->FindMaxBound())[2] < (b->FindMaxBound())[2]);
}

DivideData SplitObjects(const AABB &box, std::vector< std::vector<Primitive*> > &vectorList)
{
	DivideData data;
	int objectsNumber = vectorList[0].size();
	float minSAH = objectsNumber * box.GetSurfaceArea();
	std::sort(vectorList[0].begin(),vectorList[0].end(), ComparePrimitivesX);
	std::sort(vectorList[1].begin(),vectorList[1].end(), ComparePrimitivesY);
	std::sort(vectorList[2].begin(),vectorList[2].end(), ComparePrimitivesZ);

	for (int i = 0; i < 3; i++) 
	{
		AABB tempBox;
		std::vector<AABB> rightBounds;
		for (int j = objectsNumber; j > 0; j--) {
			tempBox.Include(vectorList[i][j-1]);
			rightBounds.push_back(tempBox);
		}
		tempBox.Reset();
		for (int j = 1; j < objectsNumber; j++) 
		{
			tempBox.Include(vectorList[i][j-1]);
			float sah = j * tempBox.GetSurfaceArea() + rightBounds[objectsNumber - j - 1].GetSurfaceArea() * (objectsNumber - j);
			if (sah < minSAH) 
			{
				minSAH = sah;
				data.divideAxis = i;
				data.leftObjectsNum = j;
				data.rightObjectsNum = objectsNumber - j;
				data.rightBox = rightBounds[objectsNumber - j - 1];
				data.leftBox = tempBox;	
			}
		}
		if (data.divideAxis != -1)
			data.isDivided = true;
		return data;
	}
}

BvhNode* GenerateBvhNode(const AABB &box, const std::vector<Primitive*> &objects, int depth) 
{
	BvhNode *node = new BvhNode(box);
    std::vector< std::vector<Primitive*> > vectorList;
	if (objects.size() < 2) 
	{
		node->objects = CopyVectorPrimitive(objects, 0, objects.size());
		return node;
	}
	for (int i = 0; i < 3; i++)
		vectorList.push_back(CopyVectorPrimitive(objects, 0, objects.size()));
	DivideData data = SplitObjects(box, vectorList);
	if (data.isDivided) 
	{
		std::vector<Primitive*> leftObjects = CopyVectorPrimitive(vectorList[data.divideAxis], 0, data.leftObjectsNum);
		node->leftNode = GenerateBvhNode(data.leftBox, leftObjects, depth++);
		std::vector<Primitive*> rightObjects = CopyVectorPrimitive(vectorList[data.divideAxis], data.leftObjectsNum, data.rightObjectsNum);
		node->rightNode = GenerateBvhNode(data.rightBox, rightObjects, depth++);
		ClearPrimitiveVector(rightObjects);
		ClearPrimitiveVector(leftObjects);
	} else 
	{
		node->objects = CopyVectorPrimitive(objects, 0, objects.size());
	}
	for (int i = 0; i < 3; i++)
		ClearPrimitiveVector(vectorList[i]);
	return node;
}

void AddVector(std::vector<Primitive*> &a, std::vector<Primitive*> &b)
{
	for (int i = 0; i < b.size(); i++)
		a.push_back(b[i]);
}

void TraverseBvhTree(BvhNode* node, const Ray &ray, std::vector<Primitive*> &objects) 
{
	if (node->box.IsIntersect(ray)) 
	{
		if (node->IsLeaf()) 
		{
			AddVector(objects, node->objects);
		} else {
			TraverseBvhTree(node->leftNode, ray, objects);
			TraverseBvhTree(node->rightNode, ray, objects);
		}
	}
}
