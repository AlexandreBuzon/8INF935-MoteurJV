//Particule soumise � la gravit�, mais pas de frottements.

#pragma once
#include "Particle.h"
class BallSansFrottements :
    public Particle
{

public:


    BallSansFrottements();

    /*
    Avec position et v�locit� de d�part.

    En r�alit�, seule la direction de la v�locit� comptent.
    Le vecteur est re-normalis� � spawnVelocity.
    */
    BallSansFrottements(double x, double y, double z,
        double vx, double vy, double vz);


    ~BallSansFrottements();

};