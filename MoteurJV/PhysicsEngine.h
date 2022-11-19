
/*
Classe g�rante de la physique d'un environnement.
*/

#pragma once

#include "Particle.h"

#include "RigidBody.h"

#include "Fireball.h"
#include "Ball.h"

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include "ForceGenerator.h"
#include "LinearFieldGenerator.h"
#include "StaticSPring.h"

#include "ConstraintGenerator.h"
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

	//N�cessaire aux inputs de la d�monstration.
	static PhysicsEngine& GetInstance();

	//Les particules � g�rer.
	std::vector<Particle*>* p_particlePopulation;

	//Les corps rigides � g�rer.
	std::vector<RigidBody*>* p_bodyPopulation;

	//Dictionnaire de forces universelles, donc subies dans tous l'espace.
	std::map<std::string,std::unique_ptr<ForceGenerator>>* p_universalForceRegistry;

	//Dictionnaire de contraintes d�finies.
	std::map<std::string, std::unique_ptr<ConstraintGenerator>>* p_constraints;

	//Constructeurs
	PhysicsEngine();
	PhysicsEngine(std::vector<Particle*>* p_pP,
		std::vector<RigidBody*>* p_bP,
		std::map<std::string, std::unique_ptr<ForceGenerator>>* p_uFR,
		std::map<std::string, std::unique_ptr<ConstraintGenerator>>* p_constraints);

	//Destructeur
	~PhysicsEngine();

	//M�thodes utilis�es en input.
	void display();

	std::map<std::string, std::unique_ptr<ForceGenerator>>* getForceRegistry();

	static void setupKeyInputs(GLFWwindow* window);

	static void callback(
		GLFWwindow* window, int key, int scancode, int action, int mods);

	/*
	Calcul des trajectoires � l'instant d'apr�s.
	*/
	void nextPosition(Particle* P,
		double tick, Vecteur3D bounds);
	void nextPosition(RigidBody* p_B,
		double tick,
		Vecteur3D bounds);

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

	//Nous facilite la vie pour les inputs.
	static PhysicsEngine instance;

	//Sommation des forces et calcul de l'acc�l�ration.
	void accelIntegrate(Particle* p_P, double tick);

	void angularAccel(RigidBody* p_B,
		
		double tick);

	void accelIntegrate(RigidBody* p_B, double tick);

	/*
	Calcul des nouveaux vecteurs d'une particule par int�gration.
	*/
	void integrate(Particle* p_P, double tick);

	void integrate(RigidBody* p_B, double tick);

	/*
	Ricochet de particule par r�flexion par rapport aux limites atteintes.

	M�thode placeholder pour garder la particule en place. Sera probablement
	remplac�e ou g�n�ralis�e lors du travail sur les collisions.
	*/
	void boundBounceCheck(Particle* p_P, Vecteur3D bounds);

	//Equivalent corps rigide.
	void boundBounceCheck(RigidBody* p_B, Vecteur3D bounds);

};

