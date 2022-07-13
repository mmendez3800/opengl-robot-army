#include "MatrixTransform.h"
#include <algorithm>

MatrixTransform::MatrixTransform()
{
	M.identity();
}

MatrixTransform::MatrixTransform(Matrix4 set)
{
	this->M = set;
}


MatrixTransform::~MatrixTransform()
{
	//
}

void MatrixTransform::draw(Matrix4 C)
{
	C = C.multiply(M);
	Group::draw(C);
}

void MatrixTransform::drawBoundary(Matrix4 C)
{
	float maxValue = std::max(M.get(0, 0), std::max(M.get(1, 1), M.get(2, 2)));

	Matrix4 newM;
	newM.identity();

	newM.set(0, 0, maxValue);
	newM.set(1, 1, maxValue);
	newM.set(2, 2, maxValue);
	newM.set(3, 0, M.get(3, 0));
	newM.set(3, 1, M.get(3, 1));
	newM.set(3, 2, M.get(3, 2));

	C = C.multiply(newM);
	Group::drawBoundary(C);

}