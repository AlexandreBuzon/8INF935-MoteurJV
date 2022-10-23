//Particule.
#pragma once
#include "Particle.h"
class BallForces:
    public Particle
{

public:


    BallForces();

    /*
    Avec position et vélocité de départ.

    En réalité, seule la direction de la vélocité comptent.
    Le vecteur est re-normalisé à spawnVelocity.
    */
    BallForces(double x, double y, double z,
        double vx, double vy, double vz, std::string permanentForce);


    ~BallForces();

};