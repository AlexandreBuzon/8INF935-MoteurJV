// Forces avec direction fixe du type poids, vent, ect.

#pragma once


#include "ParticleForceGenerator.h"

class LinearFieldGenerator :
    public ParticleForceGenerator
{
public:

    LinearFieldGenerator();
    LinearFieldGenerator(Vecteur3D f);
    ~LinearFieldGenerator();

    void updateForce(Particle* p_P, double duration);


private:
    Vecteur3D force;

};

