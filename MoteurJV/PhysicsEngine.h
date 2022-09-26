
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

public:

	//ATTRIBUTS

	//Constante d'acc�l�ration de la pesanteur.
	float g;

	//A faire : dictionnaire de forces pour partie 2 ?

	//METHODES

	//Constructeurs
	PhysicsEngine();
	PhysicsEngine(float G);

	//Destructeur
	~PhysicsEngine();

	/*
	Calcul des trajectoires � l'instant d'apr�s.
	*/
	void calculate(Particle* P,
		double tick, Vecteur3D bounds);

private:

	/*
	Calcul des nouveaux vecteurs d'une particule par int�gration.
	*/
	void newParticleState(Particle* p_P, double tick);

	/*
	Ricochet de particule par r�flexion par rapport aux limites atteintes.
	M�mo : char => '' au lieu de "".

	M�thode placeholder pour garder la particule en place. Sera probablement
	remplac�e ou g�n�ralis�e lors du travail sur les collisions.
	*/
	void boundBounceCheck(Particle* p_P, Vecteur3D bounds);


};

