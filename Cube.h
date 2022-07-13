#ifndef CUBE_H
#define CUBE_H

#include "Vector3.h"
#include "Geode.h"
#include <iostream>
#include <vector>
#include <string>

class Cube : public Geode
{
    
public:
    
    float size;
    
	Cube(void);
    Cube(float);
    virtual ~Cube(void);
    
    virtual void update(void);
	virtual void render(void);
	virtual void renderBoundary(void);
    
    /*void spin(float);

	std::vector<Vector3> * getVertices(void);
	std::vector<int> * getIndices(void);
	std::vector<Vector3> * getNormals(void);
	std::vector<int> * getNormIndices(void);*/
};

#endif

