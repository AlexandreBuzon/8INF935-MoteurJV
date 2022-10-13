#include "Particle.h"

Particle::Particle() {
	position =  Vecteur3D();
	velocity =  Vecteur3D();
	acceleration =  Vecteur3D();
	spawnSpeed = 0;
	inverseMass = 0;
}

Particle::~Particle()
{}
