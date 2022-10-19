#pragma once
#include "Particle.h"
#include "ParticuleContact.h"

class ParticuleContactGenerator 
{
public:
	virtual unsigned int addContact(ParticuleContact* contact, unsigned int limit) const = 0;
};