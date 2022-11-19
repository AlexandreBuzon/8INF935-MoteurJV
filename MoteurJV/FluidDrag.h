//Trainée fluide.

#pragma once
#include "ForceGenerator.h"
class FluidDrag :
    public ForceGenerator
{


public:

    FluidDrag();
    FluidDrag(double k1, double k2,double kTorque);
    ~FluidDrag();

    void updateForce(Particle* p_P);

    void updateForce(RigidBody* p_B, Vecteur3D pApplication);

    void updateTorque(RigidBody* p_B, Vecteur3D pApplication);

private:

    float k1;
    float k2;

    float kTorque;

};

