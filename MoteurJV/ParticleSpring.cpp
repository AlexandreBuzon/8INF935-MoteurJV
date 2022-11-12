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

	//-k(||l||-l0).l_unitaire
	p_P->acceleration = p_P->acceleration +
		(p_P->position - p_otherAnchor->position).normalize()
		* (-k * ((p_P->position - p_otherAnchor->position).norm()-l0)) * p_P->getInverseMass();

}

void ParticleSpring::updateForce(RigidBody* p_B) {

	p_B->acceleration = p_B->acceleration +
		(p_B->position - p_otherAnchor->position).normalize()
		* (-k * ((p_B->position - p_otherAnchor->position).norm() - l0)) * p_B->inverseMass;

}

void ParticleSpring::updateTorque(RigidBody* p_B,
	const Matrix34& Mb_1,
	Vecteur3D pApplication) {

	Vecteur3D f = (p_B->position - p_otherAnchor->position).normalize()
		* (-k * ((p_B->position - p_otherAnchor->position).norm() - l0));

	Vecteur3D torque = (Mb_1 * pApplication) ^ f;

	p_B->torqueSum = p_B->torqueSum + torque;

}