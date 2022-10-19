#include "Particle.h"
#include "ParticuleContact.h"
#include "ParticuleContactGenerator.h"
#include "ParticleLink.h"

float ParticleLink::currentLength() const 
{
	Vecteur3D relativePos = particle[0]->position - particle[1]->position;
	return relativePos.magnitude();
}

unsigned Parti