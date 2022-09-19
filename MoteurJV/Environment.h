/*
Environnement de jeu

D�finit les particules existantes et les coordonn�es limites.
*/

//Inclut aussi particule et vecteur par transitivit�.
#include "PhysicsEngine.h"

#pragma once
class Environment
{
public:

	//ATTRIBUTS

	//Les limites en un vecteur.
	Vecteur3D bounds;

	//Mesure du temps.
	double time;

	//Le pas de mesure en deux instants.
	float tick;

	//Moteur physique.
	PhysicsEngine engine;

	//METHODES

	//Constructeur
	Environment(float tck, PhysicsEngine e, Vecteur3D b);

	//Destructeur
	~Environment();

	void play();

};

