
/*
Classe gérante de la physique d'un environnement.
*/

#pragma once

#include "Particle.h"

#include "RigidBody.h"

#include "Fireball.h"
#include "Ball.h"

#include "ForceGenerator.h"
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

	//Les particules à gérer.
	std::vector<Particle*>* p_particlePopulation;

	//Les corps rigides à gérer.
	std::vector<RigidBody*>* p_bodyPopulation;

	//Dictionnaire de forces universelles, donc subies dans tous l'espace.
	std::map<std::string,std::unique_ptr<ForceGenerator>>* p_universalForceRegistry;

	//Dictionnaire de contraintes définies.
	std::map<std::string, std::unique_ptr<ParticleConstraintGenerator>>* p_constraints;

	//Constructeurs
	PhysicsEngine();
	PhysicsEngine(std::vector<Particle*>* p_pP,
		std::vector<RigidBody*>* p_bP,
		std::map<std::string, std::unique_ptr<ForceGenerator>>* p_uFR,
		std::map<std::string, std::unique_ptr<ParticleConstraintGenerator>>* p_constraints);

	//Destructeur
	~PhysicsEngine();

	/*
	Calcul des trajectoires à l'instant d'après.
	*/
	void nextPosition(Particle* P,
		double tick, Vecteur3D bounds);
	void nextPosition(RigidBody* p_B,
		double tick,
		Vecteur3D bounds);

	//Méthode de recherche de collision entre particules.
	std::vector<ParticuleContact> particleCollisionSearch();
	

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

	void angularAccel(RigidBody* p_B,
		const Matrix34& Mb_1,
		double tick);

	void accelIntegrate(RigidBody* p_B,
		const Matrix34& Mb_1,
		double tick);

	/*
	Calcul des nouveaux vecteurs d'une particule par intégration.
	*/
	void integrate(Particle* p_P, double tick);

	void integrate(RigidBody* p_B, double tick);

	/*
	Ricochet de particule par réflexion par rapport aux limites atteintes.

	Méthode placeholder pour garder la particule en place. Sera probablement
	remplacée ou généralisée lors du travail sur les collisions.
	*/
	void boundBounceCheck(Particle* p_P, Vecteur3D bounds);

	//Equivalent corps rigide.
	void boundBounceCheck(RigidBody* p_B, Vecteur3D bounds);

};

