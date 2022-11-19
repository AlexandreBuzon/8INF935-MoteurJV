//Ressort ancré à un point fixe.

#pragma once
#include "ForceGenerator.h"
class StaticSpring :
    public ForceGenerator
{
public:
    StaticSpring();
    StaticSpring(Vecteur3D anchor, float k, float l0);

    ~StaticSpring();

    void updateForce(Particle* p_P);

    void updateForce(RigidBody* p_B, Vecteur3D pApplication);

    void updateTorque(RigidBody* p_B, 
        Vecteur3D pApplication);

private:

    //Autre particule ancre.
    Vecteur3D anchor;

    //Constante du ressort
    float k;

    //Longueur de repos.
    float l0;

};

