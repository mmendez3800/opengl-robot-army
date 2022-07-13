#ifndef CAMErA_H
#define CAMErA_H

#include "Matrix4.h"
#include "Vector3.h"

class Camera
{
private:
    
protected:
    
    Matrix4 c;   //Camera Matrix
    Matrix4 ci;  //Inverse of Camera Matrix
    
public:
    
    Vector3 e;   //Center of Projection
    Vector3 d;   //Look At
    Vector3 up;  //Up Vector ^
    
	Vector3 leftPlane1;
	Vector3 leftPlane2;
	Vector3 rightPlane1;
	Vector3 rightPlane2;

	Vector3 topPlane1;
	Vector3 topPlane2;
	Vector3 bottomPlane1;
	Vector3 bottomPlane2;

	Vector3 nearPlane1;
	Vector3 nearPlane2;
	Vector3 farPlane1;
	Vector3 farPlane2;

    Camera(void);
    ~Camera(void);
    
    void update(void);
    
    Matrix4& getMatrix(void);
    Matrix4& getInverseMatrix(void);
    
    void set(Vector3&, Vector3&, Vector3&);
    
};

#endif
