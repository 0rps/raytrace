#ifndef VECTOR_ACTIONS_H
#define VECTOR_ACTIONS_H

#include "Primitives.h"
#include <vector>
std::vector<Primitive*> CopyVectorPrimitive(const std::vector<Primitive*> objects, int beg, int count); 
void ClearPrimitiveVector(std::vector<Primitive*> &objects); 

#endif