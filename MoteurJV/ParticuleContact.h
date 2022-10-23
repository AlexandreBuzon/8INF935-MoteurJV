#pragma once
#include "Particle.h"
#include<vector>


class ParticuleContact {
public :

	//Doublet de particule en collision.
	Particle* particule[2];

	float restitution;

	float penetration;

	Vecteur3D contactNormal;

	void resolve(float duration);
	const float calculateSeparatingVelocity();

private :
	void resolveVelocity(float duration);
	void resolveInterpenetration(float duration);

};
