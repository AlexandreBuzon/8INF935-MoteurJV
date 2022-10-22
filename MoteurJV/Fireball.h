/*
Projectile utilis� pour la d�monstration de la partie 1.

*/

#pragma once
#include "Particle.h"
class Fireball :
    public Particle
{

private:

    //Inutile ici, car soumis � aucune force.
    const double inverseMass = -1;

    const double spawnSpeed = 45.0;

    std::vector<std::string> appliedForce = {};

public:

    Fireball();

    /*
    Avec position et v�locit� de d�part.

    En r�alit�, seule la direction de la v�locit� comptent.
    Le vecteur est re-normalis� � spawnVelocity.
    */
    Fireball(double x, double y, double z,
            double vx, double vy, double vz);

};

