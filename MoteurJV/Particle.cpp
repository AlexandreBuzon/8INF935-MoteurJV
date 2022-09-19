#include "Particle.h"

//Destructeur
Particle::~Particle()
{
	//Nettoyage de la mémoire allouée pour les vecteurs et tableaux.
	delete position;
	delete speed;
	delete acceleration;
}
