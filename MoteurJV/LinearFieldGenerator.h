// Forces avec direction fixe du type poids, vent, ect.

#pragma once

#include "ForceGenerator.h"

class LinearFieldGenerator :
    public ForceGenerator
{
public:

    LinearFieldGenerator();
    LinearFieldGenerator(Vecteur3D f, bool localBase);
    ~LinearFieldGenerator();

    void updateForce(Particle* p_P);

    virtual void updateForce(RigidBody* p_B, Vecteur3D pApplication);

    void updateTorque(RigidBody* p_B, Vecteur3D pApplication);


private:

    Vecteur3D force;

    //Pour corps rigides seulement.
    bool localBase;

};

