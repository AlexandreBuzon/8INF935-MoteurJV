/*
Prototype classe Particule.

Entité gérée physiquement de manière newtonienne.
Dépourvu de volume.
Connait sa position, vitesse, accélération,
ainsi que les forces physiques à lui appliquer.

Effectivement, il s'agit d'explorer plusieurs
comportement différents dans un jeu
plutôt que de proposer un modèle réaliste.
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
	Les noms des forces que subit en général la particule.

	Ainsi, la particule peut ignorer des forces.
	On laisse alors la liberté au développeur d'associer
	forces à particules comme bon lui semble.

	On utilise des strings pour rattacher à un dictionnaire
	de forces permanentes défini par l'utilisateur.
	*/
	std::vector<std::string> permanentForces;

	double getInverseMass();
	void setVelocity(Vecteur3D newVelo);
	void setPosition(Vecteur3D newPos);

//Devra être fixé par sous-classe.
protected:

	/*
	Impulsion de départ ou norme de la vitesse initiale.

	Va servir pour le polymorphisme des différents
	projectiles.
	Typiquement, une particule définie
	va avoir une vitesse initiale fixée par sa nature, 
	plutôt que directement par sa déclaration.
	*/
	double spawnSpeed;

	/*
	Utile pour la gestion des forces auxquelles seront
	soumises la particule.
	*/
	double inverseMass;
};

