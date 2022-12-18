/*
Données de collision entre deux corps rigides.

Le système de gestion est tel qu'on a pas besoin
de garder des pointeurs de corps rigides en attributs
de cette classe.
*/

#pragma once

#include "Vecteur3D.h"
#include <vector>

/*
On introduit le contact sous forme d'enregistrement.

PAS SUR QUE CA MARCHE NIVEAU CONSTRUCTION.
*/
struct Contact {

	//Coordonnées globales
	Vecteur3D normal;
	Vecteur3D pointContact;

	double penetration;

};

//PEUT ETRE PAS UTILE DE FAIRE TOUTE UNE CLASSE.
class CollisionData
{

public:
	std::vector<Contact> listeContact;



};

