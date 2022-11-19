#ifndef ConstraintGenerator_H
#define ConstraintGenerator_H

#pragma once
#include "Particle.h"
#include "RigidBody.h"

class ConstraintGenerator 
{
public:
	virtual void solve(Particle* p_P) = 0;
	virtual bool checkConflict(Particle* p_P) = 0;

	virtual void solve(RigidBody* p_B) = 0;
};

#endif