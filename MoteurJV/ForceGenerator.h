//Classe abstraite des générateurs de force.

#ifndef FORCEGENERATOR_H
#define FORCEGENERATOR_H

#include "Particle.h"
#include "RigidBody.h"

#pragma once
class ForceGenerator
{
public:
	virtual void updateForce(Particle* p_P) = 0;
	virtual void updateForce(RigidBody* p_B) = 0;

	virtual void updateTorque(RigidBody* p_B,
		const Matrix34& Mb_1,
		Vecteur3D pApplication) = 0;
};

#endif