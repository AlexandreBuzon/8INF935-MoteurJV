#pragma once
#include "ParticleForceGenerator.h"
class FluidDrag :
    public ParticleForceGenerator
{

    float k1;
    float k2;

    void updateForce(Particle* p_P, double duration);

};

