//Ressort ancré à un point fixe.

#pragma once
#include "ParticleForceGenerator.h"
class StaticSpring :
    public ParticleForceGenerator
{
public:
    StaticSpring();
    StaticSpring(Vecteur3D anchor, float k, float l0);

    ~StaticSpring();

    void updateForce(Particle* p_P);

private:
    //Autre particule ancre.
    Vecteur3D anchor;

    //Constante du ressort
    float k;

    //Longueur de repos.
    float l0;

};

