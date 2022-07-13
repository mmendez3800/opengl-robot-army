#include "Cube.h"

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#include "Window.h"
#include "math.h"
#include <sstream>
#include <fstream>
#include <cstring>

std::vector<Vector3> vertices;
std::vector<int> indices;

std::vector<Vector3> normals;
std::vector<int> normIndices;

Cube::Cube()
{
	this->size = 1.0;
}

Cube::Cube(float size)
{
    this->size = size;
	/*float halfSize = size / 2.0;

	vertices.push_back(Vector3(-halfSize, halfSize, halfSize));
	vertices.push_back(Vector3(halfSize, halfSize, halfSize));
	vertices.push_back(Vector3(halfSize, -halfSize, halfSize));
	vertices.push_back(Vector3(-halfSize, -halfSize, halfSize));
	vertices.push_back(Vector3(-halfSize, halfSize, -halfSize));
	vertices.push_back(Vector3(-halfSize, -halfSize, -halfSize));
	vertices.push_back(Vector3(halfSize, halfSize, -halfSize));
	vertices.push_back(Vector3(halfSize, -halfSize, -halfSize));

	normals.push_back(Vector3(0.0, 0.0, 1.0));
	normals.push_back(Vector3(-1.0, 0.0, 0.0));
	normals.push_back(Vector3(1.0, 0.0, 0.0));
	normals.push_back(Vector3(0.0, 0.0, -1.0));
	normals.push_back(Vector3(0.0, 1.0, 0.0));
	normals.push_back(Vector3(0.0, -1.0, 0.0));

	//Front face
	indices.push_back(0);
	indices.push_back(2);
	indices.push_back(1);
	indices.push_back(0);
	indices.push_back(2);
	indices.push_back(3);

	normIndices.push_back(0);
	normIndices.push_back(0);
	normIndices.push_back(0);
	normIndices.push_back(0);
	normIndices.push_back(0);
	normIndices.push_back(0);

	//Left side
	indices.push_back(0);
	indices.push_back(5);
	indices.push_back(4);
	indices.push_back(0);
	indices.push_back(5);
	indices.push_back(3);

	normIndices.push_back(1);
	normIndices.push_back(1);
	normIndices.push_back(1);
	normIndices.push_back(1);
	normIndices.push_back(1);
	normIndices.push_back(1);

	//Right side
	indices.push_back(1);
	indices.push_back(7);
	indices.push_back(6);
	indices.push_back(1);
	indices.push_back(7);
	indices.push_back(2);

	normIndices.push_back(2);
	normIndices.push_back(2);
	normIndices.push_back(2);
	normIndices.push_back(2);
	normIndices.push_back(2);
	normIndices.push_back(2);

	//Back face
	indices.push_back(4);
	indices.push_back(7);
	indices.push_back(6);
	indices.push_back(4);
	indices.push_back(7);
	indices.push_back(5);

	normIndices.push_back(3);
	normIndices.push_back(3);
	normIndices.push_back(3);
	normIndices.push_back(3);
	normIndices.push_back(3);
	normIndices.push_back(3);

	//Top side
	indices.push_back(0);
	indices.push_back(6);
	indices.push_back(1);
	indices.push_back(0);
	indices.push_back(6);
	indices.push_back(4);

	normIndices.push_back(4);
	normIndices.push_back(4);
	normIndices.push_back(4);
	normIndices.push_back(4);
	normIndices.push_back(4);
	normIndices.push_back(4);

	//Bottom side
	indices.push_back(5);
	indices.push_back(2);
	indices.push_back(7);
	indices.push_back(5);
	indices.push_back(2);
	indices.push_back(3);

	normIndices.push_back(5);
	normIndices.push_back(5);
	normIndices.push_back(5);
	normIndices.push_back(5);
	normIndices.push_back(5);
	normIndices.push_back(5);*/
}

Cube::~Cube()
{
    //Delete any dynamically allocated memory/objects here
}

void Cube::update(void)
{
    //
}

void Cube::render()
{
	glutSolidCube(size);
}

void Cube::renderBoundary()
{
	radius = sqrt(2) / 2;
	glColor3f(0.0, 1.0, 0.0);
	glutWireSphere(radius, 25, 25);
}

/*void Cube::spin(float radians)
{
    Matrix4 rotation;
    rotation.makeRotateY(radians);
    
    toWorld = toWorld * rotation;
}

std::vector<Vector3>* Cube::getVertices()
{
	return &vertices;
}

std::vector<int>* Cube::getIndices()
{
	return &indices;
}

std::vector<Vector3>* Cube::getNormals()
{
	return &normals;
}

std::vector<int>* Cube::getNormIndices()
{
	return &normIndices;
} */