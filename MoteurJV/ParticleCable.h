#pragma once
#include "Particle.h"
#include "ParticuleContact.h"
#include "ParticuleContactGenerator.h"
#include "ParticleLink.h"

class ParticleCable : public ParticleLink 
{
public:
	float maxLength;
	float restitution;
	unsigned int addContact(ParticuleContact* contact, unsigned int limit) const;
};