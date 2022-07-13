#define _USE_MATH_DEFINES

#include "Camera.h"
#include "Window.h"
#include "math.h"

Camera::Camera()
{
    c.identity();
    e.set(0.0, 0.0, 20.0);
    d.set(0.0, 0.0, 0.0);
    up.set(0.0, 1.0, 0.0);
    
    //Pre-define a camera matrix (and its inverse) that are shifted 'e' from the origin
    c.set(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, e[0], e[1], e[2], 1);
    ci.set(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, -e[0], -e[1], -e[2], 1);
}

Camera::~Camera()
{
    //Delete and dynamically allocated memory/objects here
}

Matrix4& Camera::getMatrix()
{
    return c;
}

Matrix4& Camera::getInverseMatrix()
{
    return ci;
}

void Camera::update()
{
	Vector3 x, y, z;

	z = e - d;
	z = z.normalize();
	x = up.cross(z);
	x = x.normalize();
	y = z.cross(x);

	c.set(x[0], x[1], x[2], 0,
		  y[0], y[1], y[2], 0,
		  z[0], z[1], z[2], 0,
		  e[0], e[1], e[2], 1);

	Matrix4 r_inverse, t_inverse;

	r_inverse.set(x[0], x[1], x[2], 0,
		          y[0], y[1], y[2], 0,
		          z[0], z[1], z[2], 0,
		          0, 0, 0, 1);
	r_inverse = r_inverse.transpose();
	t_inverse.set(1, 0, 0, 0,
		          0, 1, 0, 0,
		          0, 0, 1, 0,
		          -e[0], -e[1], -e[2], 1);
	ci = r_inverse * t_inverse;

	float frustumHeight = 1000 * tan(M_PI / 6);
	float frustumWidth = frustumHeight * Window::width / Window::height;

	nearPlane2 = e + z;
	nearPlane1 = z;
	farPlane2 = e + z * 1000;
	farPlane1 = z;

	leftPlane2 = farPlane2 + (y * frustumHeight) - (x * frustumWidth);
	leftPlane1 = (y.cross(leftPlane2 - e)).normalize();
	rightPlane2 = farPlane2 - (y * frustumHeight) + (x * frustumWidth);
	rightPlane1 = ((rightPlane2 - e).cross(y)).normalize();
	
	topPlane2 = farPlane2 + (y * frustumHeight) - (x * frustumWidth);
	topPlane1 = (x.cross(topPlane2 - e)).normalize();
	bottomPlane2 = farPlane2 - (y * frustumHeight) + (x * frustumWidth);
	bottomPlane1 = ((bottomPlane2 - e).cross(x)).normalize();
}

void Camera::set(Vector3& e, Vector3& d, Vector3& up)
{
    this->e = e;
    this->d = d;
    this->up = up;
    update();
}
