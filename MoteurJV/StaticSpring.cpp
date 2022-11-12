#include "StaticSpring.h"

StaticSpring::StaticSpring() {

	l0 = 0;
	k = 0;
	anchor = Vecteur3D();

}

StaticSpring::StaticSpring(Vecteur3D anchor, float k, float l0) {

	this->l0 = l0;
	this->k = k;
	this->anchor = anchor;

}

StaticSpring::~StaticSpring() {}

void StaticSpring::updateForce(Particle* p_P) {

	//-k(||l||-l0).l_unitaire
	p_P->acceleration = p_P->acceleration +
		(p_P->position - anchor).normalize()
		* (-k * ((p_P->position - anchor).norm() - l0))*p_P->getInverseMass();

}

void StaticSpring::updateForce(RigidBody* p_B) {

	Vecteur3D f = (p_B->position - anchor).normalize()
		* (-k * ((p_B->position - anchor).norm() - l0)) * p_B->inverseMass;

	p_B->acceleration = p_B->acceleration + f;

}

void StaticSpring::updateTorque(RigidBody* p_B,
	const Matrix34& Mb_1,
	Vecteur3D pApplication) {

	Vecteur3D f = (p_B->position - anchor).normalize()
		* (-k * ((p_B->position - anchor).norm() - l0));

	Vecteur3D torque = (Mb_1 * pApplication) ^ f;

	p_B->torqueSum = p_B->torqueSum + torque;

}
