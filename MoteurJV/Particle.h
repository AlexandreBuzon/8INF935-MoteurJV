/*
Prototype classe Particule.

Entité gérée physiquement de manière newtonienne.
Dépourvu de volume.
Connait sa position, vitesse, accélération,
ainsi que les forces physiques à lui appliquer.

Effectivement, il s'agit d'explorer plusieurs
comportement différents dans un jeu
plutôt que de proposer un modèle réaliste.

Thibault Telitsine
17 septembre 2022
*/

/*Mémo : directive préprocesseur pour optimiser
la compilation.
*/
#pragma once

#include "Vecteur3D.h"

/*
Pour les tableaux de nature autre que nos vecteurs3D :
Liste de chaînes, triplets RGB, ect.

Les types définis par la std sont plus flexibles et fiables
que les structures C classiques.
*/
#include <string>
#include <vector>

class Particle
{
public:

	/*
	Pour déterminer la trajectoire.
	On utilise les pointeurs pour accomoder la commande
	delete dans le destructeur.
	*/
	Vecteur3D* position;
	Vecteur3D* velocity;
	Vecteur3D* acceleration;

	//METHODES

	//Constructeur dans les sous-classes ?

	//Destructeur
	~Particle();

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

	/*
	Les forces que subit la particule.

	Ainsi, la particule peut ignorer des forces, voire
	en être complètement isolé.

	A FAIRE :
	-programmer dictionnaire des forces dans physicsEngine
	-Exception si ça colle pas
	*/
	std::vector<std::string> appliedForces;

	/*A FAIRE :
	voir quel objet ImGui
	lié pour présentation graphique
	*/
};

