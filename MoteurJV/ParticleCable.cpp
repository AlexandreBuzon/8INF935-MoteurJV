#include "Particle.h"
#include "ParticuleContact.h"
#include "ParticuleContactGenerator.h"
#include "ParticleLink.h"
#include "ParticleCable.h"

unsigned ParticleCable::addContact(ParticuleContact* contact, unsigned limit) const 
{
	float length = currentLength();

	if (length < maxLength) 
	{
		return 0;
	}

	contact->particule[0] = particle[0];
	contact->particule[1] = particle[1];

	Vecteur3D normal = particle[1]->position - particle[0]->position;
	normal.normalize();
	contact->contactNormal = normal;
	contact->penetration = length - maxLength;
	contact->restitution = restitution;
	return 1;
}