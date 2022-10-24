
/*
Classe g�rante de la physique d'un environnement.
*/

#pragma once

#include "Particle.h"

#include "Fireball.h"
#include "Ball.h"

#include "ParticleForceGenerator.h"
#include "ParticleConstraintGenerator.h"
#include "ParticuleContact.h"

//Mesure de temps pour la boucle de raffraichissement.
#include <chrono>

#include<vector>
#include <map>
#include <memory>

using namespace std::chrono;

class PhysicsEngine
{

public:

	//Les particules � g�rer.
	std::vector<Particle*>* p_particlePopulation;

	//Dictionnaire de forces universelles, donc subies dans tous l'espace.
	std::map<std::string,std::unique_ptr<ParticleForceGenerator>>* p_universalForceRegistry;

	//Dictionnaire de contraintes d�finies.
	std::map<std::string, std::unique_ptr<ParticleConstraintGenerator>>* p_constraints;

	//Constructeurs
	PhysicsEngine();
	PhysicsEngine(std::vector<Particle*>* p_pP,
		std::map<std::string, std::unique_ptr<ParticleForceGenerator>>* p_uFR,
		std::map<std::string, std::unique_ptr<ParticleConstraintGenerator>>* p_constraints);

	//Destructeur
	~PhysicsEngine();

	/*
	Calcul des trajectoires � l'instant d'apr�s.
	*/
	void nextPosition(Particle* P,
		double tick, Vecteur3D bounds);

	//M�thode de recherche de collision entre particules.
	std::vector<ParticuleContact> particleCollisionSearch();

	/*
	Synchronisation de la physique et de la r�alit�.

	Reprise de l'algorithme de pas semi-variable
	pr�sent� par Glenn Fiedler.
	*/
	void physicsLoop(high_resolution_clock::time_point* p_currentTime,
		double* p_deltaTime, double tick, Vecteur3D bounds);

private:

	//Sommation des forces et calcul de l'acc�l�ration.
	void accelIntegrate(Particle* p_P, double tick);

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

