#ifndef PARTICLELINK_H
#define PARTICLELINK_H

#include "ConstraintGenerator.h"

class ParticleLink :
	public ConstraintGenerator
{

	virtual void solve(Particle* p_P) = 0;

};
	

#endif
