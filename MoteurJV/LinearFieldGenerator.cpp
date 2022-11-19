#include "LinearFieldGenerator.h"

LinearFieldGenerator::LinearFieldGenerator() {

	force = Vecteur3D();
	localBase = false;
}

LinearFieldGenerator::LinearFieldGenerator(Vecteur3D f,
	bool localBase) {

	force = f;
	this->localBase = localBase;
}

LinearFieldGenerator::~LinearFieldGenerator() {}

void LinearFieldGenerator::updateForce(Particle* p_P) {

	p_P->acceleration = p_P->acceleration + force*p_P->getInverseMass();

}

void LinearFieldGenerator::updateForce(RigidBody* p_B, Vecteur3D pApplication) {

	Vecteur3D f;
	if(localBase)f = p_B->transformMatrix.TransformDirection(force);
	else f = force;

	p_B->acceleration = p_B->acceleration + f*p_B->inverseMass;

}

void LinearFieldGenerator::updateTorque(RigidBody* p_B, Vecteur3D pApplication) {

	Vecteur3D torque;

	if (localBase) {

		//Changement seulement de direction, car translation relative à l'objet.
		Vecteur3D P = p_B->transformMatrix.TransformDirection(pApplication);
		Vecteur3D f = p_B->transformMatrix.TransformDirection(force);

		torque = P ^ f;

	}
	else torque =  p_B->transformMatrix.TransformDirection(pApplication) ^ force;

	p_B->torqueSum = p_B->torqueSum + torque;

}