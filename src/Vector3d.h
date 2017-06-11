#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <math.h>
#include <GL/glut.h>

struct Vector3d
{
	GLdouble x;
	GLdouble y;
	GLdouble z;
};

Vector3d operator+(Vector3d a, Vector3d b);
Vector3d operator+=(Vector3d& left, Vector3d right);
Vector3d operator*(GLdouble scalar, Vector3d vector);
Vector3d coords(GLdouble r, GLdouble theta, GLdouble phi);

#endif
