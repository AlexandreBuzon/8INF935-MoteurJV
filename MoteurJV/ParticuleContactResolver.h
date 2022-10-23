#pragma once
#include "Particle.h"
#include "ParticuleContact.h"
#include<vector>

class ParticuleContactResolver 
{
protected:
	unsigned int iteration;
	unsigned int iterationUsed;

public:
	void resolveContacts(ParticuleContact* contactArray, unsigned int numContacts, float duration);
};