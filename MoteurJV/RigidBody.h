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
//Pour les collisions.
class Primitive
{

	friend class ContactGenerator;
	friend class RigidBody;

public:
	Primitive() { body = 0; offset = Matrix34(); };
	~Primitive() {};

protected:
	RigidBody* body;
	Matrix34 offset;

};

class Box : public Primitive
{

	friend class ContactGenerator;

public:
	Vecteur3D halfsize;
	Box(RigidBody* rig, Matrix34 off, Vecteur3D size) {
		halfsize = size;
		body = rig;
		offset = off;
	};
};

class Sphere : public Primitive
{
	friend class ContactGenerator;

public:
	double radius;

};

#pragma once
class RigidBody
{

friend class PhysicsEngine;
friend class ContactGenerator;
friend class TreeNode;

protected:

	std::vector<bodyForce> permanentForces;

	std::vector<bodyForce> constraints;

	Matrix33 inverseInertia;

	float restitution;

	//Volume englobant en phase large.
	double broadRadius;

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

	//Graphique.
	std::vector<GLfloat> GLvertices;
	std::vector<GLuint> triangles;

	//Primitives
	std::vector<Primitive> primitiveList;
};

