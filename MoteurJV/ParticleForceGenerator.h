//Classe abstraite des générateurs de force.

#ifndef PARTICLEFORCEGENERATOR_H
#define PARTICLEFORCEGENERATOR_H

#include "Particle.h"

#pragma once
class ParticleForceGenerator
{
public:
	virtual void updateForce(Particle* p_P) = 0;
};

#endif