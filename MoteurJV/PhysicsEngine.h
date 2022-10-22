
/*
Classe g�rante de la physique d'un environnement.

Thibault Telitsine
17 septembre 2022
*/

//M�mo : pour optimiser la compilation.
#pragma once

#include "Particle.h"

//Mesure de temps pour la boucle de raffraichissement.
#include <chrono>

#include<vector>
#include <map>

using namespace std::chrono;

class PhysicsEngine
{

public:

	//Constante d'acc�l�ration de la pesanteur.
	float g;

	//Les particules � g�rer.
	std::vector<Particle*>* p_particlePopulation;

	//Les forces d�localis�es.


	//Constructeurs
	PhysicsEngine();
	PhysicsEngine(float G, std::vector<Particle*>* p_pP);

	//Destructeur
	~PhysicsEngine();

	/*
	Calcul des trajectoires � l'instant d'apr�s.
	*/
	void nextPosition(Particle* P,
		double tick, Vecteur3D bounds);

	/*
	Synchronisation de la physique et de la r�alit�.

	Reprise de l'algorithme de pas semi-variable
	pr�sent� par Glenn Fiedler.
	*/
	void physicsLoop(high_resolution_clock::time_point* p_currentTime,
		double* p_deltaTime, double tick, Vecteur3D bounds);

private:

	/*
	Calcul des nouveaux vecteurs d'une particule par int�gration.
	*/
	void integrate(Particle* p_P, double tick);

	/*
	Ricochet de particule par r�flexion par rapport aux limites atteintes.

	M�thode placeholder pour garder la particule en place. Sera probablement
	remplac�e ou g�n�ralis�e lors du travail sur les collisions.
	*/
	void boundBounceCheck(Particle* p_P, Vecteur3D bounds);

};

