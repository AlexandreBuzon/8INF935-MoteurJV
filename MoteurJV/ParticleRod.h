#pragma once
#include "Particle.h"
#include "ParticuleContact.h"
#include "ParticuleContactGenerator.h"
#include "ParticleLink.h"

class ParticleRod : public ParticleLink 
{
public:
	float length;
	unsigned int addContact(ParticuleContact* contact, unsigned int limit) const;
};