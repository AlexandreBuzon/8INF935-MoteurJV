#pragma once
#include "Particle.h"
#include<vector>


class ParticuleContact {
public :
	Particle* particule[2];

	float restitution;

	float penetration;

	Vecteur3D contactNormal;

	void resolve(float duration);
	float calculateSeparatingVelocity();

private :
	void resolveVelocity();
	void resolveInterpenetration();


};
