#include "Particle.h"

Particle::Particle() {
	position =  Vecteur3D();
	velocity =  Vecteur3D();
	acceleration =  Vecteur3D();
	spawnSpeed = 0;
	inverseMass = -1;
}

Particle::Particle(Vecteur3D position, Vecteur3D velocity, Vecteur3D acceleration) {

	this->position = position;
	this->velocity = velocity;
	this->acceleration = acceleration;
	spawnSpeed = 0;
	inverseMass = -1;
}

Particle::~Particle()
{}
