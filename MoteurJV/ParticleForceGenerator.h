#include "Particle.h"

#pragma once
class ParticleForceGenerator
{
public:
	virtual void updateForce(Particle* p_particle, float duration) = 0;
};

