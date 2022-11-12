//Trainée fluide.

#pragma once
#include "ForceGenerator.h"
class FluidDrag :
    public ForceGenerator
{


public:

    FluidDrag();
    FluidDrag(float k1, float k2,float kTorque);
    ~FluidDrag();

    void updateForce(Particle* p_P);

    void updateForce(RigidBody* p_B);

    void updateTorque(RigidBody* p_B,
        const Matrix34& Mb_1,
        Vecteur3D pApplication);

private:

    float k1;
    float k2;

    float kTorque;

};

