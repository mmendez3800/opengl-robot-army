#ifndef NODE_H
#define NODE_H

#include <iostream>
#include "Matrix4.h"
#include "Vector3.h"

class Node
{
public:
	Vector3 center;
	float radius;

	Node();
	~Node();

	virtual void draw(Matrix4 C) = 0;
	virtual void drawBoundary(Matrix4 C) = 0;
	virtual void update() = 0;
};

#endif
