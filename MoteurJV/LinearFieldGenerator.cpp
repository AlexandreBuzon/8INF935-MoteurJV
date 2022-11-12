#include "LinearFieldGenerator.h"

LinearFieldGenerator::LinearFieldGenerator() {

	force = Vecteur3D();

}

LinearFieldGenerator::LinearFieldGenerator(Vecteur3D f) {

	force = f;

}

LinearFieldGenerator::~LinearFieldGenerator() {}

void LinearFieldGenerator::updateForce(Particle* p_P) {

	p_P->acceleration = p_P->acceleration + force*p_P->getInverseMass();

}

void LinearFieldGenerator::updateForce(RigidBody* p_B) {

	p_B->acceleration = p_B->acceleration + force*p_B->inverseMass;

}

void LinearFieldGenerator::updateTorque(RigidBody* p_B,
	const Matrix34& Mb_1,
	Vecteur3D pApplication) {



	Vecteur3D torque;

	if (local)torque = Mb_1 * (pApplication ^ force);
	else torque =  (Mb_1 *pApplication) ^ force;

	p_B->torqueSum = p_B->torqueSum + torque;

}