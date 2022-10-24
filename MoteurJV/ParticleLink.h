#ifndef PARTICLELINK_H
#define PARTICLELINK_H

#include "ParticleConstraintGenerator.h"

class ParticleLink :
	public ParticleConstraintGenerator
{

	virtual void solve(Particle* p_P) = 0;

};
	

#endif
