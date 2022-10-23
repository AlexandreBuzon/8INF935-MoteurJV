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
	p_P->acceleration =
		(p_P->position - anchor).normalize()
		* (-k * ((p_P->position - anchor).norm() - l0))*p_P->getInverseMass();

}