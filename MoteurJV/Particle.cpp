#include "Particle.h"

Particle::Particle() {
	position =  Vecteur3D();
	velocity =  Vecteur3D();
	acceleration =  Vecteur3D();
	spawnSpeed = 0;
	inverseMass = -1;
	initialX = position.getX();
	initialY = position.getY();
	initialZ = position.getZ();
}

Particle::Particle(Vecteur3D position, Vecteur3D velocity, Vecteur3D acceleration) {

	this->position = position;
	this->velocity = velocity;
	this->acceleration = acceleration;
	spawnSpeed = 0;
	inverseMass = -1;
	initialX = position.getX();
	initialY = position.getY();
	initialZ = position.getZ();
}

Particle::~Particle()
{}

double Particle::getInverseMass() 
{
	return inverseMass;
}

void Particle::setVelocity(Vecteur3D newVelocity) 
{
	velocity = newVelocity;
}

void Particle::setPosition(Vecteur3D newPos)
{
	position = newPos;
}
