#include "Vecteur3D.h"
#include "Quaternion.h"
#include "Matrix34.h"
#include "Matrix33.h"

#include<glad/glad.h>

#pragma once
class RigidBody
{

friend class PhysicsEngine;

private:

	struct bodyForce {
	
		//Clé de la force dans le dictionnaire.
		std::string idForce;

		//Point d'application.
		Vecteur3D applicationP;

		//1 ~ dans base locale, 0 ~ globale
		bool local;
	
	};

	//Le centre de masse par rapport au volume. Même base que dimensions.
	float inverseMass;
	Vecteur3D centerMass;


	//Définis dans la base de l'environnement.
	Vecteur3D position;//L'origine dans la base du corps rigide.
	Vecteur3D velocity;
	Vecteur3D acceleration;

	std::vector<bodyForce> permanentForces;

	std::vector<bodyForce> constraints;

	std::vector<GLfloat> vertices;
	std::vector<GLint> triangles;

	Matrix33 inverseInertia;

	/*
	Le rigid body est un pavé droit.
	On caractérise ses dimensions par un vecteur dans une base locale au corps.
	*/
	Vecteur3D dimensions;

	float restitution;

	Quaternion orientation;

	Vecteur3D angularV;
	Vecteur3D angularA;



public:

	Matrix34 transformMatrix;

};

