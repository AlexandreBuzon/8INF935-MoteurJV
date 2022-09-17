#include "Particle.h"

//Crée une erreur sur visual studio.
//Pas sûr que j'ai bien téléchargé.
#include "Vector3D.h"

/*
Pour les tableaux de nature autre que nos vecteurs3D :
Liste de chaînes, triplets RGB, ect.

Les types définis par la std sont plus flexibles et fiables
que les structures C classiques.
*/
#include <vector>
#include <string>
//Destructeur
Particle::~Particle()
{
	//Nettoyage de la mémoire allouée pour les vecteurs et tableaux.
	delete position;
	delete speed;
	delete acceleration;
}
