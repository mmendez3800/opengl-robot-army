#include <iostream>

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include "math.h"

#include "Window.h"
#include "House.h"
#include "Cube.h"
#include "OBJObject.h"
#include "Matrix4.h"
#include "Globals.h"

int Window::width  = 512;   //Set window width in pixels here
int Window::height = 512;   //Set window height in pixels here

float spinDirection = 1;    //Changes the direction of the cube
int Window::flag = 0;               //Indicates when to switch from cube to house
int rendering = 1;          //Indicates which rendering engine to use

int frame = 0, gtime = 0, timebase = 0, showFPS = 1;   //Used in calculating frame rate
float fps = 0;							  //Used in calculating frame rate

bool Rotate = false, Move = false;
Vector3 lastPoint;

bool boundary = false;
bool culling = false;
int count = 0;

void Window::initialize(void)
{
    //Setup the light
    Vector4 lightPos(0.0, 10.0, 15.0, 0.0);
    Globals::light.position = lightPos;
    Globals::light.quadraticAttenuation = 0.02;

	Globals::camera.set(Vector3(40, 20, 120), Vector3(40, 0, 40), Vector3(0, 1, 0));
    
    //Initialize cube matrix:
    //Globals::cube.toWorld.identity();
	//Globals::sphere.toWorld.identity();
    
    //Setup the cube's material properties
    //Color color(0x23ff27ff);
    //Globals::cube.material.color = color;
	//Globals::sphere.material.color = color;
	Globals::robot1 = new Robot();
	Globals::robot2 = new Robot();
}

//----------------------------------------------------------------------------
// Callback method called when system is idle.
// This is called at the start of every new "frame" (qualitatively)
void Window::idleCallback()
{
	//Calculates the frame rate of an object
	if (showFPS == -1) {
		calculateFPS();
	}

    //Set up a static time delta for update calls
    Globals::updateData.dt = 1.0/60.0;// 60 fps
    
    //Rotate cube; if it spins too fast try smaller values and vice versa
    //Globals::cube.spin(spinDirection * 0.0005);
    
    //Call the update function on cube
    //Globals::cube.update(Globals::updateData);
	//Globals::sphere.update(Globals::updateData);

	Globals::robot1->update();
	Globals::robot2->update();
    
    //Call the display routine to draw the cube
	
	displayCallback();
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when graphics window is resized by the user
void Window::reshapeCallback(int w, int h)
{
    width = w;                                                       //Set the window width
    height = h;                                                      //Set the window height
    glViewport(0, 0, w, h);                                          //Set new viewport size
    glMatrixMode(GL_PROJECTION);                                     //Set the OpenGL matrix mode to Projection
    glLoadIdentity();                                                //Clear the projection matrix by loading the identity
    gluPerspective(60.0, double(width)/(double)height, 1.0, 1000.0); //Set perspective projection viewing frustum
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when window readraw is necessary or when glutPostRedisplay() was called.
void Window::displayCallback()
{
	Globals::camera.update();

    //Clear color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //Set the OpenGL matrix mode to ModelView
    glMatrixMode(GL_MODELVIEW);
    
    //Push a matrix save point
    //This will save a copy of the current matrix so that we can
    //make changes to it and 'pop' those changes off later.
    glPushMatrix();
    
    //Replace the current top of the matrix stack with the inverse camera matrix
    //This will convert all world coordiantes into camera coordiantes
    glLoadMatrixf(Globals::camera.getInverseMatrix().ptr());
    
    //Bind the light to slot 0.  We do this after the camera matrix is loaded so that
    //the light position will be treated as world coordiantes
    //(if we didn't the light would move with the camera, why is that?)
    Globals::light.bind(0);
	Matrix4 army1;
	army1.makeTranslate(-50, 0, -2);
	Matrix4 army2;
	army2.makeTranslate(50, 0, 2);
    
    //Draw cube or house
	switch (flag) {
	case 0:
		/*Globals::sphere.material.ambientColor = Color(0.0, 0.5, 0.0);
		Globals::sphere.material.diffuseColor = Color(0.8, 0.8, 0.8);
		Globals::sphere.material.specularColor = Color(0.25, 0.25, 0.25);
		Globals::sphere.material.shininess = 90.0;

		Globals::sphere.draw(Globals::drawData);*/
		if (Move) {
			count++;

			if ((count / 100) % 4 == 0)
				Globals::robot1->moveRight();
			else if ((count / 100) % 4 == 1)
				Globals::robot1->moveDown();
			else if ((count / 100) % 4 == 2)
				Globals::robot1->moveLeft();
			else if ((count / 100) % 4 == 3)
				Globals::robot1->moveUp();

			if ((count / 100) % 4 == 0)
				Globals::robot2->moveLeft();
			else if ((count / 100) % 4 == 1)
				Globals::robot2->moveDown();
			else if ((count / 100) % 4 == 2)
				Globals::robot2->moveRight();
			else if ((count / 100) % 4 == 3)
				Globals::robot2->moveUp();
		}

		drawArmies(army1, army2, Globals::robot1, Globals::robot2);
		break;

	/*case 1:
		Globals::house.draw(Globals::drawData);
		break;

	case 2:
		Globals::bunny.material.ambientColor = Color(1.0, 0.2039216, 0.701960);
		Globals::bunny.material.diffuseColor = Color(0.34615, 0.3143, 0.0903);
		Globals::bunny.material.specularColor = Color(0.797357, 0.723991, 0.73);
		Globals::bunny.material.shininess = 255.0;

		Globals::bunny.draw(Globals::drawData);
		break;

	case 3:
		Globals::dragon.material.ambientColor = Color(0.0, 0.0, 0.5);
		Globals::dragon.material.diffuseColor = Color(1.0, 1.0, 1.0);
		Globals::dragon.material.specularColor = Color(0.0, 0.0, 0.0);
		Globals::dragon.material.shininess = 0.0;

		Globals::dragon.draw(Globals::drawData);
		break;

	case 4:
		Globals::bear.material.ambientColor = Color(0.5, 0.0, 0.0);
		Globals::bear.material.diffuseColor = Color(0.61424, 0.04136, 0.04136);
		Globals::bear.material.specularColor = Color(0.727811, 0.626959, 0.626959);
		Globals::bear.material.shininess = 150.0;

		Globals::bear.draw(Globals::drawData);
		break;*/
	}

	/*Matrix4 army;
	army.identity();
	drawArmy(army, Globals::robot);*/
    
    //Pop off the changes we made to the matrix stack this frame
    glPopMatrix();
    
    //Tell OpenGL to clear any outstanding commands in its command buffer
    //This will make sure that all of our commands are fully executed before
    //we swap buffers and show the user the freshly drawn frame
    glFlush();
    
    //Swap the off-screen buffer (the one we just drew to) with the on-screen buffer
    glutSwapBuffers();
}

//Calculates frame rate of object in Window
void Window::calculateFPS()
{
	//  Increase frame count
	frame++;

	//  Get the number of milliseconds since glutInit called
	//  (or first call to glutGet(GLUT ELAPSED TIME)).
	gtime = glutGet(GLUT_ELAPSED_TIME);

	//  Calculate time passed
	int timeInterval = gtime - timebase;

	if (timeInterval > 1000)
	{
		//  calculate the number of frames per second
		fps = frame / (timeInterval / 1000.0f);

		//  Set time
		timebase = gtime;

		//  Reset frame count
		frame = 0;

		std::cout << "FPS: " << fps << std::endl;
	}
}

//TODO: Keyboard callbacks!
void Window::keyboard(unsigned char key, int x, int y) {
	Matrix4 trans;
	Vector3 move;

	switch (key) {
	/*case 'c':
		//if (flag == 0)
			//spinDirection = -spinDirection;

		break;*/

	case 'x':
		move.set(-1, 0, 0);
		Globals::camera.set(Globals::camera.e + move, Globals::camera.d, Globals::camera.up);
		//moveObject(trans);
		break;

	case 'X':
		move.set(1, 0, 0);
		Globals::camera.set(Globals::camera.e + move, Globals::camera.d, Globals::camera.up);
		//moveObject(trans);
		break;

	case 'y':
		move.set(0, -1, 0);
		Globals::camera.set(Globals::camera.e + move, Globals::camera.d, Globals::camera.up);
		//moveObject(trans);
		break;

	case 'Y':
		move.set(0, 1, 0);
		Globals::camera.set(Globals::camera.e + move, Globals::camera.d, Globals::camera.up);
		//moveObject(trans);
		break;

	case 'z':
		move.set(0, 0, -1);
		Globals::camera.set(Globals::camera.e + move, Globals::camera.d, Globals::camera.up);
		//moveObject(trans);
		break;

	case 'Z':
		move.set(0, 0, 1);
		Globals::camera.set(Globals::camera.e + move, Globals::camera.d, Globals::camera.up);
		//moveObject(trans);
		break;

	case 'b':
		boundary = !boundary;
		break;

	case 'c':
		culling = !culling;
		break;

	case 'm':
		Move = !Move;
		break;

	/*case 'r':
		times = 0;

		switch (flag) {
		case 0:
			Globals::sphere.toWorld.identity();
			//spinDirection = 1;
			break;

		case 2:
			while (times < 20) {
				Globals::bunny.centerObject();
				times++;
			}
			//Globals::bunny.toWorld.identity();
			break;

		case 3:
			while (times < 20) {
				Globals::dragon.centerObject();
				times++;
			}
			//Globals::dragon.toWorld.identity();
			break;

		case 4:
			while (times < 20) {
				Globals::bear.centerObject();
				times++;
			}
			//Globals::bear.toWorld.identity();
			break;
		}

		break;

	case 'o':
		trans.makeRotateZ(10 * M_PI / 180);
		moveObject(trans);
		break;

	case 'O':
		trans.makeRotateZ(-10 * M_PI / 180);
		moveObject(trans);
		break;

	case 's':
		trans.makeScale(.9);
		scaleObject(trans);
		break;

	case 'S':
		trans.makeScale(1.1);
		scaleObject(trans);
		break;

	case 'e':
		rendering = -rendering;
		break;

	case '+':
		if (rendering == -1 && Globals::rasterizer.part < 3)
			Globals::rasterizer.part++;

		break;

	case '-':
		if (rendering == -1 && Globals::rasterizer.part > 0)
			Globals::rasterizer.part--;
		
		break;

	case 'd':
		if (rendering == -1 && Globals::rasterizer.part != 0)
			Globals::rasterizer.box = -Globals::rasterizer.box;

		break;*/

	case 'f':
		showFPS = -showFPS;
		break;
	}

	/*if (flag == 0) {
		Vector3 position(Globals::cube.toWorld.get(3, 0), Globals::cube.toWorld.get(3, 1),
			Globals::cube.toWorld.get(3, 2));

		position.print("Position of Cube");
	}*/
}

//Moves the object in Window depeding on which key is pressed
void Window::moveObject(Matrix4 translate) {
	/*switch (flag) {
	case 0:
		Globals::sphere.toWorld = translate * Globals::sphere.toWorld;
		break;

	case 2:
		Globals::bunny.toWorld = translate * Globals::bunny.toWorld;
		break;

	case 3:
		Globals::dragon.toWorld = translate * Globals::dragon.toWorld;
		break;

	case 4:
		Globals::bear.toWorld = translate * Globals::bear.toWorld;
		break;
	}*/
}

//Scales the object in Window
void Window::scaleObject(Matrix4 scale) {
	/*switch (flag) {
	case 0:
		Globals::sphere.toWorld = Globals::sphere.toWorld * scale;
		break;

	case 2:
		Globals::bunny.toWorld = Globals::bunny.toWorld * scale;
		break;

	case 3:
		Globals::dragon.toWorld = Globals::dragon.toWorld * scale;
		break;

	case 4:
		Globals::bear.toWorld = Globals::bear.toWorld * scale;
		break;
	}*/
}

//TODO: Function Key callbacks!
void Window::specialKeyboard(int key, int x, int y) {
	Vector3 e, d, up;

	switch (key) {
	/*case GLUT_KEY_F1:
		e.set(0.0, 0.0, 20.0);
		d.set(0.0, 0.0, 0.0);
		up.set(0.0, 1.0, 0.0);
		Globals::camera.set(e, d, up);
		flag = 0;
		//Globals::rasterizer.toDrawOBJ = &Globals::cube;
		break;

	case GLUT_KEY_F2:
		e.set(0.0, 24.14, 24.14);
		d.set(0.0, 0.0, 0.0);
		up.set(0.0, 1.0, 0.0);
		Globals::camera.set(e, d, up);
		flag = 1;
		Globals::rasterizer.toDrawOBJ = &Globals::house;
		break;

	case GLUT_KEY_F3:
		e.set(-28.33, 11.66, 23.33);
		d.set(-5.0, 0.0, 0.0);
		up.set(0.0, 1.0, 0.5);
		Globals::camera.set(e, d, up);
		flag = 1;
		Globals::rasterizer.toDrawOBJ = &Globals::house;
		break;

	case GLUT_KEY_F2:
		flag = 2;
		e.set(0.0, 0.0, 20.0);
		d.set(0.0, 0.0, 0.0);
		up.set(0.0, 1.0, 0.0);
		Globals::camera.set(e, d, up);
		//Globals::rasterizer.toDrawOBJ = &Globals::bunny;
		break;

	case GLUT_KEY_F3:
		flag = 3;
		e.set(0.0, 0.0, 20.0);
		d.set(0.0, 0.0, 0.0);
		up.set(0.0, 1.0, 0.0);
		Globals::camera.set(e, d, up);
		//Globals::rasterizer.toDrawOBJ = &Globals::dragon;
		break;

	case GLUT_KEY_F4:
		flag = 4;
		e.set(0.0, 0.0, 20.0);
		d.set(0.0, 0.0, 0.0);
		up.set(0.0, 1.0, 0.0);
		Globals::camera.set(e, d, up);
		//Globals::rasterizer.toDrawOBJ = &Globals::bear;
		break;*/
	}
}

Vector3 Window::trackBallMapping(int x, int y)
{
	// Vector v is the synthesized 3D position of the mouse location on the trackball
	Vector3 v;

	// this is the depth of the mouse location: the delta between the plane through the center of the trackball and the z position of the mouse
	float d;
	
	// this calculates the mouse X position in trackball coordinates, which range from -1 to +1
	v[0] = (2.0 * x - float(width)) / float(width);
	
	// this does the equivalent to the above for the mouse Y position
	v[1] = (float(height) - 2.0 * y) / float(height);
	
	// initially the mouse z position is set to zero, but this will change below
	v[2] = 0.0;
	
	// this is the distance from the trackball's origin to the mouse location, without considering depth (=in the plane of the trackball's origin)
	d = v.magnitude();
	
	// this limits d to values of 1.0 or less to avoid square roots of negative values in the following line
	d = (d < 1.0) ? d : 1.0;
	
	// this calculates the Z coordinate of the mouse position on the trackball, based on Pythagoras: v.z*v.z + d*d = 1*1
	v[2] = sqrtf(1.001 - d * d);
	
	// Still need to normalize, since we only capped d, not v.
	v = v.normalize();
	
	// return the mouse location on the surface of the trackball
	return v;
}

//TODO: Mouse callbacks!
void Window::mouseCallback(int button, int state, int x, int y)
{
	/*if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		Rotate = true;
		Move = false;
		lastPoint = trackBallMapping(x, y);
	}

	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		Rotate = false;
		Move = true;
		lastPoint = trackBallMapping(x, y);
	}

	else {
		Rotate = false;
		Move = false;
	}*/
}

//TODO: Mouse Motion callbacks!
void Window::motionCallback(int x, int y)
{
	/*Vector3 curPoint;
	Matrix4 trans;

	if (Rotate) {
		curPoint = trackBallMapping(x, y);

		Vector3 rotAxis = lastPoint.cross(curPoint);
		float rot_angle = lastPoint.angle(curPoint);

		trans.makeRotateArbitrary(rotAxis, rot_angle);
		moveObject(trans);

		lastPoint = curPoint;
	}

	else if (Move) {
		curPoint = trackBallMapping(x, y);

		Vector3 curPoint2(curPoint[0], curPoint[1], 0.0);
		Vector3 lastPoint2(lastPoint[0], lastPoint[1], 0.0);

		Vector3 translate;
		translate = (curPoint2 - lastPoint2) * 10;

		trans.makeTranslate(translate);
		moveObject(trans);

		lastPoint = curPoint;
		
	}*/
}

void Window::mouseWheelCallback(int wheel, int direction, int x, int y)
{
	/*Matrix4 trans;

	if (direction > 0)
		trans.makeScale(1.1);

	else
		trans.makeScale(0.9);

	scaleObject(trans);*/
}

void Window::drawArmies(Matrix4 platoon1, Matrix4 platoon2, Robot *rob1, Robot *rob2)
{
	Matrix4 group1 = platoon1;
	Matrix4 group2 = platoon2;
	float spacing = 10;

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			Vector3 a = rob1->movement() + Vector3(platoon1.get(3, 0), platoon1.get(3, 1), platoon1.get(3, 2)) + Vector3(i * spacing, 0, j * spacing);
			if ((culling && frustumCheck(a, rob1)) || !culling) {
				rob1->draw(platoon1 * group1.makeTranslate(i * spacing, 0, j * spacing));

				if (boundary)
					rob1->drawBoundary(platoon1 * group1.makeTranslate(i * spacing, 0, j * spacing));

				group1 = platoon1;
			}
		}
	}

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			Vector3 b = rob2->movement() + Vector3(platoon2.get(3, 0), platoon2.get(3, 1), platoon2.get(3, 2)) + Vector3(i * spacing, 0, j * spacing);
			if ((culling && frustumCheck(b, rob2)) || !culling) {
				rob2->draw(platoon2 * group2.makeTranslate(i * spacing, 0, j * spacing));

				if (boundary)
					rob2->drawBoundary(platoon2 * group2.makeTranslate(i * spacing, 0, j * spacing));

				group2 = platoon2;
			}
		}
	}
}

bool Window::frustumCheck(Vector3 c, Robot *robot)
{
	return !((c - Globals::camera.leftPlane2).dot(Globals::camera.leftPlane1) > robot->root->radius ||
			 (c - Globals::camera.rightPlane2).dot(Globals::camera.rightPlane1) > robot->root->radius ||
			 (c - Globals::camera.topPlane2).dot(Globals::camera.topPlane1) > robot->root->radius ||
			 (c - Globals::camera.bottomPlane2).dot(Globals::camera.bottomPlane1) > robot->root->radius ||
			 (c - Globals::camera.farPlane2).dot(Globals::camera.farPlane1) > robot->root->radius ||
			 (c - Globals::camera.nearPlane2).dot(Globals::camera.nearPlane1) > robot->root->radius);
}