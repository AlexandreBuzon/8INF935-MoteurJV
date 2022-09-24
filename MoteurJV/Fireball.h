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

    const double spawnSpeed = 45;

    std::vector<std::string> appliedForce = {};

public:

    //Constructeurs.
    Fireball();

    /*
    Avec position et v�locit� de d�part.

    En r�alit�, seule la direction de la v�locit� compte.
    Le vecteur est re-normalis� � spawnVelocity.
    */
    Fireball(double x, double y, double z,
            double vx, double vy, double vz);

};

