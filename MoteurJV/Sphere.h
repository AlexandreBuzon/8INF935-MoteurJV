/*
Primitive sph�rique.
*/

#include "RigidBody.h"

#pragma once
class Sphere : Primitive
{
	friend class ContactGenerator;

public:
	double radius;

};

