#ifndef ROBOT_H
#define ROBOT_H

#include "MatrixTransform.h"
#include "Cube.h"
#include "Sphere.h"

class Robot
{
public:
	float angle1;
	float angle2;
	bool reverseAngle;

	Group * root;
	Sphere * sphere;
	Cube * cube;

	MatrixTransform * robot;
	MatrixTransform * robotRotate;
	MatrixTransform * torso;
	MatrixTransform * head;

	MatrixTransform * leftArm;
	MatrixTransform * leftArmRotate;
	MatrixTransform * leftArmTranslate;

	MatrixTransform * rightArm;
	MatrixTransform * rightArmRotate;
	MatrixTransform * rightArmTranslate;

	MatrixTransform * leftLeg;
	MatrixTransform * leftLegRotate;
	MatrixTransform * leftLegTranslate;

	MatrixTransform * rightLeg;
	MatrixTransform * rightLegRotate;
	MatrixTransform * rightLegTranslate;

	Robot();
	~Robot();

	virtual void draw(Matrix4);
	virtual void drawBoundary(Matrix4);
	virtual void update(void);

	Vector3 movement(void);

	void moveUp(void);
	void moveDown(void);
	void moveLeft(void);
	void moveRight(void);
};

#endif