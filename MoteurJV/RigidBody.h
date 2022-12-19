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
class RigidBody;

//Pour les collisions.
class Primitive
{

	friend class ContactGenerator;
	friend class RigidBody;

public:
	Primitive() { body = 0; offset = Matrix34(); };
	Primitive(const Primitive& prim) { body.reset(prim.body.get()); offset = prim.offset; };
	~Primitive() {};

protected:
	std::unique_ptr<RigidBody> body;
	Matrix34 offset;

};

class Box : public Primitive
{

	friend class ContactGenerator;

public:
	Vecteur3D halfsize;
	Box(RigidBody *newBody, Matrix34 newOffset, Vecteur3D size) {
		body = std::unique_ptr<RigidBody>(newBody);
		offset = newOffset;
		halfsize = size;
	};
	Box() {
		body = 0;
		offset = Matrix34();
	};
	~Box() {
	
	};
};

class Sphere : public Primitive
{
	friend class ContactGenerator;

public:
	double radius;
	Sphere(RigidBody *newBody, Matrix34 newOffset, double newRad) {
		body = std::unique_ptr<RigidBody>(newBody);
		offset = newOffset;
		radius = newRad;
	};
	Sphere() {
		body = 0;
		offset = Matrix34();
		radius = 0;
	};
	~Sphere() {
		
	};
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
	~RigidBody();
};

