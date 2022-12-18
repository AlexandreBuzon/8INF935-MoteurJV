#include "RigidBody.h"
#pragma once
class Box : Primitive
{

	friend class ContactGenerator;

public:
	Vecteur3D halfsize;
};

