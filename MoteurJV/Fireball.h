/*
Projectile utilisé pour la démonstration de la partie 1.
Typiquement Soumis à aucune force universelle.
*/

#pragma once
#include "Particle.h"
class Fireball :
    public Particle
{

private:


    const double inverseMass = -1;

    const double spawnSpeed = 45.0;

public:

    Fireball();

    /*
    Avec position et vélocité de départ.

    En réalité, seule la direction de la vélocité comptent.
    Le vecteur est re-normalisé à spawnVelocity.
    */
    Fireball(double x, double y, double z,
            double vx, double vy, double vz);

};

