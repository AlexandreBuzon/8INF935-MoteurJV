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

	ParticuleContact();
	ParticuleContact(float restit, float pene, Vecteur3D contactNormal,
		Particle* p_P1, Particle* p_P2);

	~ParticuleContact();

	void resolve(float duration);
	const float calculateSeparatingVelocity();

private :
	void resolveVelocity(float duration);
	void resolveInterpenetration(float duration);

};
