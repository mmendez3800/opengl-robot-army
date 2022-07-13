#define _USE_MATH_DEFINES

#include "Robot.h"
#include "math.h"

#ifdef __APPLE__
	#include <GLUT/glut.h>
#else
	#include <GL/glut.h>
#endif

Robot::Robot()
{
	angle1 = 0.0;
	angle2 = 0.0;
	reverseAngle = true;

	sphere = new Sphere();
	cube = new Cube();
	root = new Group();

	robot = new MatrixTransform();
	robotRotate = new MatrixTransform();

	torso = new MatrixTransform();
	head = new MatrixTransform();

	leftArm = new MatrixTransform();
	leftArmRotate = new MatrixTransform();
	leftArmTranslate = new MatrixTransform();

	rightArm = new MatrixTransform();
	rightArmRotate = new MatrixTransform();
	rightArmTranslate = new MatrixTransform();

	leftLeg = new MatrixTransform();
	leftLegRotate = new MatrixTransform();
	leftLegTranslate = new MatrixTransform();

	rightLeg = new MatrixTransform();
	rightLegRotate = new MatrixTransform();
	rightLegTranslate = new MatrixTransform();

	robot->M.identity();

	torso->M = torso->M.makeScale(2.5, 3.5, 2);
	torso->center = Vector3(0, 0, 0);
	torso->radius = sqrt(2.5 * 2.5 + 3.5 * 3.5 + 2 * 2) / 2;
	torso->addChild(cube);
	robotRotate->addChild(torso);

	head->M = head->M.makeTranslate(0, 3, 0);
	head->center = Vector3(0, 3, 0);
	head->radius = 1.0;
	head->addChild(sphere);
	robotRotate->addChild(head);

	leftArm->M = leftArm->M.makeTranslate(0, 1.5, 0);
	leftArmRotate->M = leftArmRotate->M.makeRotateX(0);
	leftArmTranslate->M = leftArmTranslate->M.makeScale(1, 2.5, 1);
	leftArmTranslate->M = leftArmTranslate->M.makeTranslate(-1.5, -1.25, 0) * leftArmTranslate->M;
	leftArm->center = Vector3(-1.5, 0.25, 0);
	leftArm->radius = sqrt(1 + 2.5 * 2.5 + 1) / 2;
	leftArmTranslate->addChild(cube);
	leftArmRotate->addChild(leftArmTranslate);
	leftArm->addChild(leftArmRotate);
	robotRotate->addChild(leftArm);

	rightArm->M = rightArm->M.makeTranslate(0, 1.5, 0);
	rightArmRotate->M = rightArmRotate->M.makeRotateX(0);
	rightArmTranslate->M = rightArmTranslate->M.makeScale(1, 2.5, 1);
	rightArmTranslate->M = rightArmTranslate->M.makeTranslate(1.5, -1.25, 0) * rightArmTranslate->M;
	rightArm->center = Vector3(1.5, 0.25, 0);
	rightArm->radius = sqrt(1 + 2.5 * 2.5 + 1) / 2;
	rightArmTranslate->addChild(cube);
	rightArmRotate->addChild(rightArmTranslate);
	rightArm->addChild(rightArmRotate);
	robotRotate->addChild(rightArm);

	leftLeg->M = leftLeg->M.makeTranslate(-1, -1.45, 0);
	leftLegRotate->M = leftLegRotate->M.makeRotateX(0);
	leftLegTranslate->M = leftLegTranslate->M.makeScale(1, 3, 1);
	leftLegTranslate->M = leftLegTranslate->M.makeTranslate(0, -1.55, 0) * leftLegTranslate->M;
	leftLeg->center = Vector3(-1, -3, 0);
	leftLeg->radius = sqrt(1 + 9 + 1) / 2;
	leftLegTranslate->addChild(cube);
	leftLegRotate->addChild(leftLegTranslate);
	leftLeg->addChild(leftLegRotate);
	robotRotate->addChild(leftLeg);

	rightLeg->M = rightLeg->M.makeTranslate(1, -1.45, 0);
	rightLegRotate->M = rightLegRotate->M.makeRotateX(0);
	rightLegTranslate->M = rightLegTranslate->M.makeScale(1, 3, 1);
	rightLegTranslate->M = rightLegTranslate->M.makeTranslate(0, -1.55, 0) * rightLegTranslate->M;
	leftLeg->center = Vector3(1, -3, 0);
	leftLeg->radius = sqrt(1 + 9 + 1) / 2;
	rightLegTranslate->addChild(cube);
	rightLegRotate->addChild(rightLegTranslate);
	rightLeg->addChild(rightLegRotate);
	robotRotate->addChild(rightLeg);

	robot->addChild(robotRotate);
	root->addChild(robot);
}


Robot::~Robot()
{
}

void Robot::draw(Matrix4 C)
{
	root->center = Vector3(C.get(3, 0), C.get(3, 1), C.get(3, 2));
	root->radius = 4.5;
	root->draw(C);
}

void Robot::drawBoundary(Matrix4 C)
{
	root->drawBoundary(C);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glMultMatrixf((C * robot->M).ptr());
	glColor3f(0.0, 1.0, 0.0);
	glutWireSphere(4.5, 25, 25);
	glPopMatrix();
}

void Robot::update()
{
	if (angle1 >= 1.0 || angle2 >= 1.0)
		reverseAngle = !reverseAngle;

	if (reverseAngle == true)
		angle1 = angle1 - 0.5;

	else
		angle1 = angle1 + 0.5;

	angle2 = -angle1;

	leftArmRotate->M = leftArmRotate->M.makeRotateX(angle1);
	rightArmRotate->M = rightArmRotate->M.makeRotateX(angle2);
	leftLegRotate->M = leftLegRotate->M.makeRotateX(angle2);
	rightLegRotate->M = rightLegRotate->M.makeRotateX(angle1);
}

Vector3 Robot::movement()
{
	Vector3 distance = Vector3(robot->M.get(3, 0), robot->M.get(3, 1), robot->M.get(3, 2));
	return distance;
}

void Robot::moveUp()
{
	robotRotate->M.makeRotateY(M_PI);
	robot->M = robot->M.makeTranslate(0, 0, 1) * robot->M;
	root->center[2] = root->center[2] + robot->M.get(3, 0);
}

void Robot::moveDown()
{
	robotRotate->M.makeRotateY(M_PI);
	robot->M = robot->M.makeTranslate(0, 0, -1) * robot->M;
	root->center[2] = root->center[2] + robot->M.get(3, 0);
}

void Robot::moveLeft()
{
	robotRotate->M.makeRotateY(M_PI_2);
	robot->M = robot->M.makeTranslate(-1, 0, 0) * robot->M;
	root->center[0] = root->center[0] + robot->M.get(3, 0);
}

void Robot::moveRight()
{
	robotRotate->M.makeRotateY(M_PI_2);
	robot->M = robot->M.makeTranslate(1, 0, 0) * robot->M;
	root->center[0] = root->center[0] + robot->M.get(3, 0);
}