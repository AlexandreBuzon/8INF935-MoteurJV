#include "Particle.h"

Particle::Particle() {
	position = new Vecteur3D();
	velocity = new Vecteur3D();
	acceleration = new Vecteur3D();
	spawnSpeed = 0;
	inverseMass = 0;
}

//Destructeur
Particle::~Particle()
{
	//Nettoyage de la mémoire allouée pour les vecteurs et tableaux.
	//delete position;
	//delete velocity;
	//delete acceleration;
}
