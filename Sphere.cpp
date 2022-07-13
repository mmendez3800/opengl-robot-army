#include "Sphere.h"

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

Sphere::Sphere()
{
	this->radiuss = 1.0;
	this->slices = 50;
	this->stacks = 50;
}

Sphere::Sphere(double radius, int slices, int stacks)
{
    this->radiuss = radius;
    this->slices = slices;
    this->stacks = stacks;
}

void Sphere::update()
{
    //
}

void Sphere::render()
{
	glutSolidSphere(radiuss, slices, stacks);
}

void Sphere::renderBoundary()
{
	radius = 1.0;
	glColor3f(0.0, 1.0, 0.0);
	glutWireSphere(radius, 25, 25);
}


