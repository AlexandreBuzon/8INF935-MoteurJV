#pragma once
#include "Particle.h"
#include "ParticuleContact.h"
#include "ConstraintGenerator.h"
#include "ParticleLink.h"

class ParticleRod : public ConstraintGenerator
{
public:
	float length;
	
	Particle* p_anchor;

	ParticleRod();
	ParticleRod(Particle* p_anchor, float length);
	~ParticleRod();

	void solve(Particle* p_P);
	bool checkConflict(Particle* p_P);

};