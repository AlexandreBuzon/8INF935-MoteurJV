#include "Vecteur3D.h"
#include "Quaternion.h"
#include "Matrix34.h"
#include "Matrix33.h"

#include<glad/glad.h>

struct bodyForce {

	//Cl� de la force dans le dictionnaire.
	std::string idForce;

	//Point d'application.
	Vecteur3D applicationP;

	//1 ~ dans base locale, 0 ~ globale
	bool localF;//Force
	bool localP;//Point d'application

};

#pragma once
class RigidBody
{

friend class PhysicsEngine;

private:

	std::vector<bodyForce> permanentForces;

	std::vector<bodyForce> constraints;

	std::vector<GLfloat> GLvertices;
	std::vector<GLint> triangles;

	Matrix33 inverseInertia;

	/*
	Le rigid body est un pav� droit.
	On caract�rise ses dimensions par un vecteur dans une base locale au corps.
	*/
	Vecteur3D dimensions;

	float restitution;

	Quaternion orientation;


public:

	//D�finis dans la base de l'environnement. Apparent� au centre de masse.
	Vecteur3D position;//L'origine dans la base du corps rigide.

	float inverseMass;

	//En base globale.
	Vecteur3D acceleration;
	Vecteur3D velocity;

	//En base locale.
	Vecteur3D torqueSum;
	Vecteur3D angularV;
	
	

	Matrix34 transformMatrix;

};

