#include "Vecteur3D.h"
#include "Quaternion.h"
#include "Matrix34.h"

#pragma once
class RigidBody
{

friend class PhysicsEngine;

private:


	//Définis dans la base de l'environnement.
	Vecteur3D position;//L'origine dans la base du corps rigide.
	Vecteur3D velocity;
	Vecteur3D acceleration;


	/*
	Le rigid body est un pavé droit.
	On caractérise ses dimensions par un vecteur dans une base locale au corps.
	*/
	Vecteur3D dimensions;

	//Le centre de masse par rapport au volume. Même base que dimensions.
	float inverseMass;
	Vecteur3D centerMass;

	float restitution;

	Quaternion orientation;

	Vecteur3D angularV;
	Vecteur3D angularA;



public:

	Matrix34 transformMatrix;

};

