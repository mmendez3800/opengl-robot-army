#ifndef SPHERE_H
#define SPHERE_H

#include <iostream>
#include "Drawable.h"
#include "Geode.h"

class Sphere : public Geode
{
    
public:
    
    double radiuss;
    int slices, stacks;
    
	Sphere(void);
    Sphere(double, int, int);
 
    virtual void update(void);
	virtual void render(void);
	virtual void renderBoundary(void);
};

#endif
