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

#include "Vecteur3D.h"

/*
Pour les tableaux de nature autre que nos vecteurs3D :
Liste de cha�nes, triplets RGB, ect.

Les types d�finis par la std sont plus flexibles et fiables
que les structures C classiques.
*/
#include <string>
#include <vector>

class Particle
{
public:

	/*
	Pour d�terminer la trajectoire.
	On utilise les pointeurs pour accomoder la commande
	delete du destructeur.
	*/
	Vecteur3D* position;
	Vecteur3D* velocity;
	Vecteur3D* acceleration;

	//METHODE

	//Destructeur
	~Particle();

	//Ajout/retrait de forces en partie 2.

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

	/*
	Les noms des forces que subit la particule.

	Ainsi, la particule peut ignorer des forces, voire
	en �tre compl�tement isol�.
	On laisse alors la libert� au d�veloppeur d'associer
	forces � particules comme bon lui semble.

	A FAIRE :
	-programmer dictionnaire des forces dans physicsEngine
	-Exception si �a colle pas.
	*/
	std::vector<std::string> appliedForces;
};

