#pragma once
#include "Particle.h"
#include "ParticuleContact.h"
#include "ParticuleContactGenerator.h"

class ParticleLink : public ParticuleContactGenerator 
{
public:
	Particle* particle[2];

	float currentLength() const;

	unsigned int addContact(ParticuleContact* contact, unsigned int limit) const = 0;
};
