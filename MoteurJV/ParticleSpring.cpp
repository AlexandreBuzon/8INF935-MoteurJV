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
	p_P->acceleration =
		(p_P->position - p_otherAnchor->position).normalize()
		* (-k * ((p_P->position - p_otherAnchor->position).norm()-l0)) * p_P->getInverseMass();

}