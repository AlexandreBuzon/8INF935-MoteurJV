#include "Particle.h"

//Cr�e une erreur sur visual studio.
//Pas s�r que j'ai bien t�l�charg�.
#include "Vector3D.h"

/*
Pour les tableaux de nature autre que nos vecteurs3D :
Liste de cha�nes, triplets RGB, ect.

Les types d�finis par la std sont plus flexibles et fiables
que les structures C classiques.
*/
#include <vector>
#include <string>
//Destructeur
Particle::~Particle()
{
	//Nettoyage de la m�moire allou�e pour les vecteurs et tableaux.
	delete position;
	delete speed;
	delete acceleration;
}
