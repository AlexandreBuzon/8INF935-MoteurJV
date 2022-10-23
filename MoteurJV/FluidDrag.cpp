#include "FluidDrag.h"


FluidDrag::FluidDrag() {

	k1 = 0;
	k2 = 0;

}

FluidDrag::FluidDrag(float k1, float k2) {

	this->k1 = k1;
	this->k2 = k2;

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