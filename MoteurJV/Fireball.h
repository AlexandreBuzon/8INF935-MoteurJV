/*
Projectile utilisé pour la démonstration de la partie 1.

*/

#pragma once
#include "Particle.h"
class Fireball :
    public Particle
{

private:

    //Inutile ici, car soumis à aucune force.
    const double inverseMass = -1;

    const double spawnSpeed = 45;

    std::vector<std::string> appliedForce = {};

public:

    //Constructeurs.
    Fireball();

    /*
    Avec position et vélocité de départ.

    En réalité, seule la direction de la vélocité compte.
    Le vecteur est re-normalisé à spawnVelocity.
    */
    Fireball(double x, double y, double z,
            double vx, double vy, double vz);

};

