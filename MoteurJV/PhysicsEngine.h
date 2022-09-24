
/*
Classe g�rante de la physique d'un environnement.

Thibault Telitsine
17 septembre 2022
*/

//M�mo : pour optimiser la compilation.
#pragma once

#include "Particle.h"

#include<vector>


class PhysicsEngine
{

	//A FAIRE : friend dans Vector3D.

public:

	//ATTRIBUTS

	//Constante d'acc�l�ration de la pesanteur.
	float g;

	//A faire : dictionnaire de forces.

	//METHODES

	//Constructeurs
	PhysicsEngine();
	PhysicsEngine(float G);

	//Destructeur
	~PhysicsEngine();

	/*
	Calcul des trajectoires � l'instant d'apr�s.
	*/
	void calculate(std::vector<Particle>* p_particlePopulation,
		double tick, double time, Vecteur3D bounds);

private:

	/*
	Calcul des nouveaux vecteurs d'une particule par int�gration.
	*/
	void newParticleState(Particle* p_P, double tick);

	/*
	Ricochet de particule par r�flexion par rapport � la limite atteinte.
	L'axe d�finit la dimension o� il y a d�passement.
	M�mo : char => '' au lieu de "".
	*/
	void boundBounceCheck(Particle* p_P, Vecteur3D bounds);


};

