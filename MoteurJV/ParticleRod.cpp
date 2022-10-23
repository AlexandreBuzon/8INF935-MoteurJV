#include "Particle.h"
#include "ParticuleContact.h"
#include "ParticuleContactGenerator.h"
#include "ParticleLink.h"
#include "ParticleRod.h"

ParticleRod::ParticleRod() {

	p_anchor = NULL;
	length = 0;

}

ParticleRod::ParticleRod(Particle* p_anchor, float length) {

	this->p_anchor = p_anchor;
	this->length = length;

}

ParticleRod::~ParticleRod() {}

void ParticleRod::solve(Particle* p_P) {

	Vecteur3D l = p_anchor->position - p_P->position;
	Vecteur3D u = l.normalize();

	//Replace Particule à une position respectant la contrainte.
	p_P->position = p_anchor->position + u * length;


	Vecteur3D projectedVelocity = u * (p_P->velocity * u);

	//La tige absorbe la composante de la vitesse entrant en choc.
	p_P->velocity = p_P->velocity - projectedVelocity;
}

bool ParticleRod::checkConflict(Particle* p_P) {

	return (p_P->position - p_anchor->position).norm() == length;

}