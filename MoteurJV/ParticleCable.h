#pragma once
#include "Particle.h"
#include "ParticuleContact.h"
#include "ParticuleContactGenerator.h"
#include "ParticleLink.h"

class ParticleCable : public ParticleLink 
{
public:
	float maxLength;
	double restitution;

	Particle* p_anchor;

	void solve(Particle* p_P);
	bool checkConflict(Particle* p_P);
};