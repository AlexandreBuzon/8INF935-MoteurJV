/*
Environnement de jeu

Définit les particules existantes et les coordonnées limites.
*/

#pragma once
class Environment
{
public:

	//ATTRIBUTS

	//Les limites en un vecteur.
	Vector3D bounds;

	//Mesure du temps.
	double time;

	//Le pas de mesure en deux instants.
	float tick;

	//Moteur physique.
	physicsEngine engine;

	//METHODES

	//Constructeur
	Environment(float tck, physicsEngine e, Vector3D b);

	//Destructeur
	~Environment();

	void play();

};

