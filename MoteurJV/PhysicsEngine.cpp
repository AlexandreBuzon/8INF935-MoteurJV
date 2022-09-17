#include "PhysicsEngine.h"

PhysicsEngine::PhysicsEngine(float G)
{
	g = G;
	//On se passera de construire la constante d'archimède. Sujet au changement.
	cArchimede = 0;
}

PhysicsEngine::~PhysicsEngine()
{
}

/*
Ricochet de particule par réflexion par rapport à la limite atteinte.
L'axe définit la dimension où il y a dépassement.
Mémo : char => '' au lieu de "".
*/
void PhysicsEngine::boundBounce(Particle* p_P, char axis)
{
	switch(axis){

		//Cas plutôt simple de réflexion.
		//(Serait bien d'avoir une rotation pour le cas général)
		case 'x':
			p_P->x = -p_P->x;

		case 'y':
			p_P->y = -p_P->y;

		case 'z':
			p_P->z = -p_P->z;

		default:
			//Exception ?
	}

}

/*
Calcul des trajectoires à l'instant d'après.
*/
void PhysicsEngine::calculate(vector<Particle>* p_particlePopulation, float tick, double time, Vecteur3D bounds)
{
	for (auto P : p_particlePopulation) {

		//Vérification de collision avec les limites.
		if ((P.x <= 0)||(P.x >= bounds.x)) {

		}

	}
}
