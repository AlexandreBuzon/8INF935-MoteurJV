//Trainée fluide.

#pragma once
#include "ParticleForceGenerator.h"
class FluidDrag :
    public ParticleForceGenerator
{


public:

    FluidDrag();
    FluidDrag(float k1, float k2);
    ~FluidDrag();

    void updateForce(Particle* p_P);

private:

    float k1;
    float k2;



};

