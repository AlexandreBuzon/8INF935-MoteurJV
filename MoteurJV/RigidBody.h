#include "Vecteur3D.h"
#include "Quaternion.h"
#include "Matrix34.h"
#include "Matrix33.h"

#include <vector>
#include<glad/glad.h>

struct bodyForce {

	//Clé de la force dans le dictionnaire.
	std::string idForce;

	//Point d'application.
	Vecteur3D applicationP;

};

#pragma once
class RigidBody
{

friend class PhysicsEngine;

protected:

	std::vector<bodyForce> permanentForces;

	std::vector<bodyForce> constraints;

	Matrix33 inverseInertia;

	float restitution;



	RigidBody();

	~RigidBody();


public:

	float inverseMass;

	//Définis dans la base de l'environnement. Apparenté au centre de masse.
	Vecteur3D position;//L'origine dans la base du corps rigide.

	//En base globale.
	Vecteur3D acceleration;
	Vecteur3D velocity;

	//En base locale.
	Vecteur3D torqueSum;
	Vecteur3D angularV;
	Quaternion orientation;

	Matrix34 transformMatrix;

	std::vector<GLfloat> GLvertices;
	std::vector<GLuint> triangles;

};

