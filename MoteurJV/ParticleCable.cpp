#include "Particle.h"
#include "ParticuleContact.h"
#include "ParticuleContactGenerator.h"
#include "ParticleLink.h"
#include "ParticleCable.h"

void ParticleCable::solve(Particle* p_P) {

	Vecteur3D l = p_anchor->position - p_P->position;
	Vecteur3D u = l.normalize();

	//Replace Particule à une position respectant la contrainte.
	p_P->position = p_anchor->position + u * maxLength;


	Vecteur3D projectedVelocity = u * (p_P->velocity * u);

	//Le cable absorbe la composante selon restitution et peut faire effet de rappel.
	p_P->velocity = p_P->velocity - projectedVelocity * (2 - restitution);

}

bool ParticleCable::checkConflict(Particle* p_P) {

	return (p_anchor->position - p_P->position).norm() > maxLength;
}