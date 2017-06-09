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



Vector3d operator+(Vector3d a, Vector3d b)
{
	return
	{
		.x = a.x + b.x,
		.y = a.y + b.y,
		.z = a.z + b.z,
	};
}



Vector3d operator+=(Vector3d& left, Vector3d right)
{
	return left = left + right;
}



Vector3d operator*(GLdouble scalar, Vector3d vector)
{
	return
	{
		.x = scalar * vector.x,
		.y = scalar * vector.y,
		.z = scalar * vector.z,
	};
}



Vector3d coords(GLdouble r, GLdouble theta, GLdouble phi)
{
	return
	{
		.x = r*sin(phi)*cos(theta),
		.y = r*sin(phi)*sin(theta),
		.z = r*cos(phi),
	};
}


#endif
