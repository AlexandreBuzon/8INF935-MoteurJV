#include "ParticleSpring.h"

ParticleSpring::ParticleSpring() {

	l0 = 0;
	k = 0;
	p_otherAnchor = NULL;

}

ParticleSpring::ParticleSpring(Particle* p_oA, float k, float l0) {

	this->l0 = l0;
	this->k = k;
	p_otherAnchor = p_oA;

}

ParticleSpring::~ParticleSpring(){}

void ParticleSpring::updateForce(Particle* p_P) {

	//Garde fou, ne devrait pas arriver du fait des collisions.
	if ((p_P->position - p_otherAnchor->position).norm() == 0)return;

	//-k(||l||-l0).l_unitaire
	p_P->acceleration = p_P->acceleration +
		(p_P->position - p_otherAnchor->position).normalize()
		* (-k * ((p_P->position - p_otherAnchor->position).norm()-l0)) * p_P->getInverseMass();

}

void ParticleSpring::updateForce(RigidBody* p_B, Vecteur3D pApplication) {

	//Point d'application en global.
	Vecteur3D P = p_B->transformMatrix * pApplication;

	//Garde fou, ne devrait pas arriver du fait des collisions.
	if ((P - p_otherAnchor->position).norm() == 0)return;

	p_B->acceleration = p_B->acceleration +
		(P - p_otherAnchor->position).normalize()
		* (-k * ((P - p_otherAnchor->position).norm() - l0)) * p_B->inverseMass;

}

void ParticleSpring::updateTorque(RigidBody* p_B, Vecteur3D pApplication) {

	//Point d'application en global.
	Vecteur3D P = p_B->transformMatrix*pApplication;

	//Garde fou, ne devrait pas arriver du fait des collisions.
	if ((P - p_otherAnchor->position).norm() == 0)return;

	Vecteur3D f = (P - p_otherAnchor->position).normalize()
		* (-k * ((P - p_otherAnchor->position).norm() - l0));

	Vecteur3D torque = p_B->transformMatrix.TransformDirection(pApplication) ^ f;

	p_B->torqueSum = p_B->torqueSum + torque;

}