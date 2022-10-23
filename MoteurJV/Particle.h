/*
Prototype classe Particule.

Entit� g�r�e physiquement de mani�re newtonienne.
D�pourvu de volume.
Connait sa position, vitesse, acc�l�ration,
ainsi que les forces physiques � lui appliquer.

Effectivement, il s'agit d'explorer plusieurs
comportement diff�rents dans un jeu
plut�t que de proposer un mod�le r�aliste.
*/

#pragma once

#include "Vecteur3D.h"
#include "LinearFieldGenerator.h"

#include <string>
#include <vector>

class Particle
{
public:


	Vecteur3D position;
	Vecteur3D velocity;
	Vecteur3D acceleration;
	double mass;
	double rayonCollision;


	//Constructeur
	Particle();
	Particle(Vecteur3D position, Vecteur3D velocity, Vecteur3D acceleration);

	//Destructeur
	~Particle();

	/*
	Les noms des forces que subit en g�n�ral la particule.

	Ainsi, la particule peut ignorer des forces.
	On laisse alors la libert� au d�veloppeur d'associer
	forces � particules comme bon lui semble.

	On utilise des strings pour rattacher � un dictionnaire
	de forces permanentes d�fini par l'utilisateur.
	*/
	std::vector<std::string> permanentForces;

	double getInverseMass();
	void setVelocity(Vecteur3D newVelo);
	void setPosition(Vecteur3D newPos);

//Devra �tre fix� par sous-classe.
protected:

	/*
	Impulsion de d�part ou norme de la vitesse initiale.

	Va servir pour le polymorphisme des diff�rents
	projectiles.
	Typiquement, une particule d�finie
	va avoir une vitesse initiale fix�e par sa nature, 
	plut�t que directement par sa d�claration.
	*/
	double spawnSpeed;

	/*
	Utile pour la gestion des forces auxquelles seront
	soumises la particule.
	*/
	double inverseMass;
};

