#include "FluidDrag.h"


FluidDrag::FluidDrag() {

	k1 = 0;
	k2 = 0;
	kTorque = 0;
}

FluidDrag::FluidDrag(float k1, float k2, float kTorque) {

	this->k1 = k1;
	this->k2 = k2;
	this->kTorque = kTorque;
}

FluidDrag::~FluidDrag(){}

void FluidDrag::updateForce(Particle* p_P){

	if (p_P->velocity.norm() != 0) {

		//v_unitaire.(k1*v + k2*v^2)/m
		Vecteur3D f = p_P->velocity.normalize()
			*((-k1*p_P->velocity.norm()
			-k2*p_P->velocity.norm()* p_P->velocity.norm()))*p_P->getInverseMass();

		p_P->acceleration = p_P->acceleration + f;

	}

}

void FluidDrag::updateForce(RigidBody* p_B) {

	if (p_B->velocity.norm() != 0) {

		//v_unitaire.(k1*v + k2*v^2)/m
		Vecteur3D f = p_B->velocity.normalize()
			* ((-k1 * p_B->velocity.norm()
				- k2 * p_B->velocity.norm() * p_B->velocity.norm())) * p_B->inverseMass;

		p_B->acceleration = p_B->acceleration + f;

	}

}


void FluidDrag::updateTorque(RigidBody* p_B, const Matrix34& Mb_1,
	Vecteur3D pApplication) {

	if (p_B->angularV.norm() != 0) {

		//Modèle de trainée quadratique. Toujours en base locale.
		Vecteur3D f = p_B->angularV.normalize()
			* ((-kTorque * p_B->angularV.norm() * p_B->angularV.norm()));

		Vecteur3D torque = (Mb_1 * pApplication) ^ f;

		p_B->torqueSum = p_B->torqueSum + torque;

	}


}