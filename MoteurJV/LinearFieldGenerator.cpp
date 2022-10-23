#include "LinearFieldGenerator.h"

LinearFieldGenerator::LinearFieldGenerator() {

	force = Vecteur3D();

}

LinearFieldGenerator::LinearFieldGenerator(Vecteur3D f) {

	force = f;

}

LinearFieldGenerator::~LinearFieldGenerator() {}

void LinearFieldGenerator::updateForce(Particle* p_P) {

	p_P->acceleration = p_P->acceleration + force;

}