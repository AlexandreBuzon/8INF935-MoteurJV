
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

	//Constante d'Archimède (pour flottaison)
	/*
	Pas sûr qu'on s'en serve vraiment puisqu'il faudrait
	définir l'eau en tant que région de l'espace. C'est
	juste à titre conceptuel.
	*/
	float cArchimede;

	//A faire : dictionnaire de forces.

	//METHODES

	//Constructeur
	PhysicsEngine(float G);

	//Destructeur
	~PhysicsEngine();

	/*
	Calcul des trajectoires à l'instant d'après.
	*/
	void calculate(std::vector<Particle>* p_particlePopulation,
		float tick, double time);

private:

	/*
	Calcul des nouveaux vecteurs d'une particule
	à partir des forces.
	*/
	void newParticleState(Particle* p_P, float tick);

	/*
	Ricochet de particule par réflexion par rapport à la limite atteinte.
	L'axe définit la dimension où il y a dépassement.
	Mémo : char => '' au lieu de "".
	*/
	void boundBounce(Particle* p_P, char axis);


};

