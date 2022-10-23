#include "Particle.h"

#pragma once
class ParticleForceGenerator
{
public:
	virtual void updateForce(Particle* p_P, double duration) = 0;
};

