#ifndef GEODE_H
#define GEODE_H

#include "Node.h"
#include "Material.h"

class Geode : public Node
{
public:
	Geode();
	~Geode();

	Material material;

	void draw(Matrix4 C);
	void drawBoundary(Matrix4 C);

	virtual void render() = 0;
	virtual void renderBoundary() = 0;
};

#endif