#include "RodEnd.h"

RodEnd::RodEnd(){

    position = Vecteur3D();
    velocity = Vecteur3D();
    acceleration = Vecteur3D();

    permanentForces = {};

    constraints = {};

}


RodEnd::RodEnd(Vecteur3D p, Vecteur3D v,
    std::vector<std::string> constraints){

    position = p;
    velocity = v;

    permanentForces = { "poids" };

    this->constraints = constraints;

}


RodEnd::~RodEnd(){}