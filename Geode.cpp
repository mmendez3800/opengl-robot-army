#include "Geode.h"
#include <GL/freeglut.h>

Geode::Geode()
{
	//
}


Geode::~Geode()
{
	//
}

void Geode::draw(Matrix4 C)
{
	material.apply();

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glMultMatrixf(C.ptr());
	render();
	glPopMatrix();
}

void Geode::drawBoundary(Matrix4 C)
{
	material.apply();

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glMultMatrixf(C.ptr());
	renderBoundary();
	glPopMatrix();
}