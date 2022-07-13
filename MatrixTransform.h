#ifndef MATRIXTRANSFORM_H
#define MATRIXTRANSFORM_H

#include "Group.h"

class MatrixTransform : public Group
{
public:
	Matrix4 M;

	MatrixTransform(void);
	MatrixTransform(Matrix4);
	~MatrixTransform();

	virtual void draw(Matrix4);
	virtual void drawBoundary(Matrix4);
};

#endif