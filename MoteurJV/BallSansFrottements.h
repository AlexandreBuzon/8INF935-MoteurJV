//Particule soumise à la gravité, mais pas de frottements.

#pragma once
#include "Particle.h"
class BallSansFrottements :
    public Particle
{

public:


    BallSansFrottements();

    /*
    Avec position et vélocité de départ.

    En réalité, seule la direction de la vélocité comptent.
    Le vecteur est re-normalisé à spawnVelocity.
    */
    BallSansFrottements(double x, double y, double z,
        double vx, double vy, double vz);


    ~BallSansFrottements();

};