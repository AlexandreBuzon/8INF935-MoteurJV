#include "Particle.h"
#include "ParticuleContact.h"
#include "ParticuleContactGenerator.h"
#include "ParticleLink.h"
#include "ParticleRod.h"

unsigned ParticleRod::addContact(ParticuleContact* contact, unsigned limit)const 
{
	float currentLen = currentLength();
	
	if (currentLen == length) 
	{
		return 0;
	}

	contact->particule[0] = particle[0];
	contact->particule[1] = particle[1];

	Vecteur3D normal = particle[1]->position - particle[0]->position;
	normal.normalize();

	if(currentLen > length)
	{
		contact->contactNormal = normal;
		contact->penetration = currentLen - length;
	}
	else
	{
		contact->contactNormal = normal * -1;
		contact->penetration = length - currentLen;
	}

	contact->restitution = 0;
	return 1;
}