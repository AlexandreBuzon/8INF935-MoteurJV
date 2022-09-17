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

class Particle
{
public:

	//Pour déterminer la trajectoire.
	Vecteur3D position;
	Vecteur3D speed;
	Vecteur3D acceleration;

//Fixé par sous-classe.
protected:

	/*
	Impulsion de départ ou norme de la vitesse initiale.

	Va servir pour le polymorphisme des différents
	projectiles.
	Typiquement, une particule définie
	va avoir une vitesse initiale fixée par sa nature, 
	plutôt que directement par sa déclaration.
	*/
	double spawnVelocity;

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
	std::vector<string> appliedForces;

	/*A FAIRE :
	voir quel objet ImGui
	lié pour présentation graphique
	*/

	//METHODES
	
	//Constructeur dans les sous-classes ?

	//Destructeur
	~Particle();
};

