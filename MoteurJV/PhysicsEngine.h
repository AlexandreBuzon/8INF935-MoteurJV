
/*
Classe gérante de la physique d'un environnement.

Thibault Telitsine
17 septembre 2022
*/

//Mémo : pour optimiser la compilation.
#pragma once

#include "Particle.h"

#include<vector>


class PhysicsEngine
{

public:

	//ATTRIBUTS

	//Constante d'accélération de la pesanteur.
	float g;

	std::vector<Particle*>* p_particlePopulation;

	//METHODES

	//Constructeurs
	PhysicsEngine();
	PhysicsEngine(float G, std::vector<Particle*>* p_pP);

	//Destructeur
	~PhysicsEngine();

	/*
	Calcul des trajectoires à l'instant d'après.
	*/
	void nextPosition(Particle* P,
		double tick, Vecteur3D bounds);

private:

	/*
	Calcul des nouveaux vecteurs d'une particule par intégration.
	*/
	void integrate(Particle* p_P, double tick);

	/*
	Ricochet de particule par réflexion par rapport aux limites atteintes.
	Mémo : char => '' au lieu de "".

	Méthode placeholder pour garder la particule en place. Sera probablement
	remplacée ou généralisée lors du travail sur les collisions.
	*/
	void boundBounceCheck(Particle* p_P, Vecteur3D bounds);


};

