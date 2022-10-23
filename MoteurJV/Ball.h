//Particule soumise à la gravité.

#pragma once
#include "Particle.h"
class Ball :
    public Particle
{

public:


    Ball();

    /*
    Avec position et vélocité de départ.

    En réalité, seule la direction de la vélocité comptent.
    Le vecteur est re-normalisé à spawnVelocity.
    */
    Ball(double x, double y, double z,
        double vx, double vy, double vz);


    ~Ball();

};