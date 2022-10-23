//Particule soumise � la gravit�.

#pragma once
#include "Particle.h"
class Ball :
    public Particle
{

public:


    Ball();

    /*
    Avec position et v�locit� de d�part.

    En r�alit�, seule la direction de la v�locit� comptent.
    Le vecteur est re-normalis� � spawnVelocity.
    */
    Ball(double x, double y, double z,
        double vx, double vy, double vz);


    ~Ball();

};