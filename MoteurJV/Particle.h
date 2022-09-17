/*
Prototype classe Particule.

Entit� g�r�e physiquement de mani�re newtonienne.
D�pourvu de volume.
Connait sa position, vitesse, acc�l�ration,
ainsi que les forces physiques � lui appliquer.

Effectivement, il s'agit d'explorer plusieurs
comportement diff�rents dans un jeu
plut�t que de proposer un mod�le r�aliste.

Thibault Telitsine
17 septembre 2022
*/

/*M�mo : directive pr�processeur pour optimiser
la compilation.
*/
#pragma once

class Particle
{
public:

	//Pour d�terminer la trajectoire.
	Vecteur3D position;
	Vecteur3D speed;
	Vecteur3D acceleration;

//Fix� par sous-classe.
protected:

	/*
	Impulsion de d�part ou norme de la vitesse initiale.

	Va servir pour le polymorphisme des diff�rents
	projectiles.
	Typiquement, une particule d�finie
	va avoir une vitesse initiale fix�e par sa nature, 
	plut�t que directement par sa d�claration.
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
	en �tre compl�tement isol�.

	A FAIRE :
	-programmer dictionnaire des forces dans physicsEngine
	-Exception si �a colle pas
	*/
	std::vector<string> appliedForces;

	/*A FAIRE :
	voir quel objet ImGui
	li� pour pr�sentation graphique
	*/

	//METHODES
	
	//Constructeur dans les sous-classes ?

	//Destructeur
	~Particle();
};

