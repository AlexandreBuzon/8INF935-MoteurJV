/*
Primitive sph�rique.
*/

#include "Primitive.h"

#pragma once
class Sphere : Primitive
{
	friend class ContactGenerator;

public:
	double radius;

};

