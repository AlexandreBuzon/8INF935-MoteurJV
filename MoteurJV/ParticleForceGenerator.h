//Classe abstraite des g�n�rateurs de force.

#include "Particle.h"

#pragma once
class ParticleForceGenerator
{
public:
	virtual void updateForce(Particle* p_P) = 0;
};

