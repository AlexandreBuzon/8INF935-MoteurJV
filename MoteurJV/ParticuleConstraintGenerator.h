#ifndef PARTICLECONSTRAINTGENERATOR_H
#define PARTICLECONSTRAINTGENERATOR_H

#pragma once
#include "Particle.h"

class ParticleConstraintGenerator 
{
public:
	virtual void solve(Particle* p_P) = 0;
};

#endif