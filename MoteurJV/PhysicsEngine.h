
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

	//A FAIRE : friend dans Vector3D.

public:

	//ATTRIBUTS

	//Constante d'accélération de la pesanteur.
	float g;

	//A faire : dictionnaire de forces.

	//METHODES

	//Constructeurs
	PhysicsEngine();
	PhysicsEngine(float G);

	//Destructeur
	~PhysicsEngine();

	/*
	Calcul des trajectoires à l'instant d'après.
	*/
	void calculate(std::vector<Particle>* p_particlePopulation,
		double tick, double time, Vecteur3D bounds);

private:

	/*
	Calcul des nouveaux vecteurs d'une particule par intégration.
	*/
	void newParticleState(Particle* p_P, double tick);

	/*
	Ricochet de particule par réflexion par rapport à la limite atteinte.
	L'axe définit la dimension où il y a dépassement.
	Mémo : char => '' au lieu de "".
	*/
	void boundBounceCheck(Particle* p_P, Vecteur3D bounds);


};

