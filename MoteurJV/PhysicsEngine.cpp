#include "PhysicsEngine.h"

PhysicsEngine::PhysicsEngine(float G)
{
	g = G;
	//On se passera de construire la constante d'archim�de. Sujet au changement.
	cArchimede = 0;
}

PhysicsEngine::~PhysicsEngine()
{
}

/*
Ricochet de particule par r�flexion par rapport � la limite atteinte.
L'axe d�finit la dimension o� il y a d�passement.
M�mo : char => '' au lieu de "".
*/
void PhysicsEngine::boundBounce(Particle* p_P, char axis)
{
	switch(axis){

		//Cas plut�t simple de r�flexion.
		//(Serait bien d'avoir une rotation pour le cas g�n�ral)
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
Calcul des trajectoires � l'instant d'apr�s.
*/
void PhysicsEngine::calculate(vector<Particle>* p_particlePopulation, float tick, double time, Vecteur3D bounds)
{
	for (auto P : p_particlePopulation) {

		//V�rification de collision avec les limites.
		if ((P.x <= 0)||(P.x >= bounds.x)) {

		}

	}
}
