#ifndef WINDOW_H
#define WINDOW_H

#include "Matrix4.h"
#include "Robot.h"

class Window	  // OpenGL output window related routines
{
    
public:
    
    static int width, height; 	            // window size
	static int flag;
    
    static void initialize(void);
    static void idleCallback(void);
    static void reshapeCallback(int, int);
    static void displayCallback(void);

	static void calculateFPS(void);
	static void moveObject(Matrix4);
	static void scaleObject(Matrix4);

	static void keyboard(unsigned char, int, int);
	static void specialKeyboard(int, int, int);

	static Vector3 trackBallMapping(int, int);
	static void mouseCallback(int, int, int, int);
	static void motionCallback(int, int);
	static void mouseWheelCallback(int, int, int, int);

	static void drawArmies(Matrix4, Matrix4, Robot*, Robot*);
	static bool frustumCheck(Vector3, Robot*);
};

#endif

