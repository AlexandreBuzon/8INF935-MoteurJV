#include "Particle.h"

//Destructeur
Particle::~Particle()
{
	//Nettoyage de la m�moire allou�e pour les vecteurs et tableaux.
	delete position;
	delete velocity;
	delete acceleration;
}
