
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

	//Constante d'Archim�de (pour flottaison)
	/*
	Pas s�r qu'on s'en serve vraiment puisqu'il faudrait
	d�finir l'eau en tant que r�gion de l'espace. C'est
	juste � titre conceptuel.
	*/
	float cArchimede;

	//A faire : dictionnaire de forces.

	//METHODES

	//Constructeur
	PhysicsEngine(float G);

	//Destructeur
	~PhysicsEngine();

	/*
	Calcul des trajectoires � l'instant d'apr�s.
	*/
	void calculate(std::vector<Particle>* p_particlePopulation,
		float tick, double time);

private:

	/*
	Calcul des nouveaux vecteurs d'une particule
	� partir des forces.
	*/
	void newParticleState(Particle* p_P, float tick);

	/*
	Ricochet de particule par r�flexion par rapport � la limite atteinte.
	L'axe d�finit la dimension o� il y a d�passement.
	M�mo : char => '' au lieu de "".
	*/
	void boundBounce(Particle* p_P, char axis);


};

