#ifndef GLOBALS_H
#define GLOBALS_H

#include "Camera.h"
#include "House.h"
#include "Cube.h"
#include "Sphere.h"
#include "OBJObject.h"
#include "Light.h"
#include "DrawData.h"
#include "UpdateData.h"
#include "Window.h"
#include "Robot.h"

class Globals
{
    
public:
    
    static Camera camera;

	static House house;

    //static Cube cube;

	static Sphere sphere;

	static OBJObject bunny, dragon, bear;

    static Light light;

    static DrawData drawData;
    static UpdateData updateData;
    //Feel free to add more member variables as needed

	static Robot * robot1;
	static Robot * robot2;
};

#endif
