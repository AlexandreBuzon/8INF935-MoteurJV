/*
Ressort rattaché à une autre particule.

Note : la particule ancre ne subit pas la
force. Il faut deux instances de la classe
pour simuler l'intéraction complète.
*/

#pragma once
#include "ForceGenerator.h"
class ParticleSpring :
    public ForceGenerator
{

public:

    ParticleSpring();
    ParticleSpring(Particle* p_oA, float k, float l0);

    ~ParticleSpring();

    void updateForce(Particle* p_P);

    void updateForce(RigidBody* p_B, Vecteur3D pApplication);
    void updateTorque(RigidBody* p_B,Vecteur3D pApplication);

private:

    //Autre particule ancre.
    Particle* p_otherAnchor;

    //Constante du ressort
    float k;

    //Longueur de repos.
    float l0;

};

