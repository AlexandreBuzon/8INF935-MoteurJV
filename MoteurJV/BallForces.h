//Particule.
#pragma once
#include "Particle.h"
class BallForces:
    public Particle
{

public:


    BallForces();

    /*
    Avec position et v�locit� de d�part.

    En r�alit�, seule la direction de la v�locit� comptent.
    Le vecteur est re-normalis� � spawnVelocity.
    */
    BallForces(double x, double y, double z,
        double vx, double vy, double vz, std::string permanentForce);


    ~BallForces();

};