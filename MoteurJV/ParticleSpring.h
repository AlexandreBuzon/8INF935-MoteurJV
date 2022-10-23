/*
Ressort rattach� � une autre particule.

Note : la particule ancre ne subit pas la
force. Il faut deux instances de la classe
pour simuler l'int�raction compl�te.
*/

#pragma once
#include "ParticleForceGenerator.h"
class ParticleSpring :
    public ParticleForceGenerator
{

public:

    ParticleSpring();
    ParticleSpring(Particle* p_oA, float k, float l0);

    ~ParticleSpring();

    void updateForce(Particle* p_P);

private:

    //Autre particule ancre.
    Particle* p_otherAnchor;

    //Constante du ressort
    float k;

    //Longueur de repos.
    float l0;

};

