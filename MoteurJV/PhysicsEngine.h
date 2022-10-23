
/*
Classe gérante de la physique d'un environnement.
*/

#pragma once

#include "Particle.h"

#include "Fireball.h"
#include "Ball.h"

#include "ParticleForceGenerator.h"

//Mesure de temps pour la boucle de raffraichissement.
#include <chrono>

#include<vector>
#include <map>
#include <memory>

using namespace std::chrono;

class PhysicsEngine
{

public:

	//Constante d'accélération de la pesanteur.
	float g;

	//Les particules à gérer.
	std::vector<Particle*>* p_particlePopulation;

	//Dictionnaire de forces universelles, donc subies dans tous l'espace.
	std::map<std::string,std::unique_ptr<ParticleForceGenerator>>* p_universalForceRegistry;

	//Constructeurs
	PhysicsEngine();
	PhysicsEngine(float G, std::vector<Particle*>* p_pP,
		std::map<std::string, std::unique_ptr<ParticleForceGenerator>>* p_uFR);

	//Destructeur
	~PhysicsEngine();

	/*
	Calcul des trajectoires à l'instant d'après.
	*/
	void nextPosition(Particle* P,
		double tick, Vecteur3D bounds);

	/*
	Synchronisation de la physique et de la réalité.

	Reprise de l'algorithme de pas semi-variable
	présenté par Glenn Fiedler.
	*/
	void physicsLoop(high_resolution_clock::time_point* p_currentTime,
		double* p_deltaTime, double tick, Vecteur3D bounds);

private:

	//Sommation des forces et calcul de l'accélération.
	void accelIntegrate(Particle* p_P, double tick);

	/*
	Calcul des nouveaux vecteurs d'une particule par intégration.
	*/
	void integrate(Particle* p_P, double tick);

	/*
	Ricochet de particule par réflexion par rapport aux limites atteintes.

	Méthode placeholder pour garder la particule en place. Sera probablement
	remplacée ou généralisée lors du travail sur les collisions.
	*/
	void boundBounceCheck(Particle* p_P, Vecteur3D bounds);

};

