#include "Particle.h"
#include "ParticleForceGenerator.h"
#include <vector>

#pragma once
class ParticleForceRegistry
{
private:
	struct ParticleForceEntry
	{
		Particle* p_particle;
		ParticleForceGenerator* p_forceGenerator;
	};

	using Registry = std::vector<ParticleForceEntry>;
	Registry m_registry;

public:


	void updateForce(double tick);

};

