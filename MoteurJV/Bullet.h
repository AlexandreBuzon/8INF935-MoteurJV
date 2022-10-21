
#pragma once
#include "Particle.h"
class Bullet :
    public Particle
{
private:

    const double spawnSpeed = 150;

    const double inverseMass = 40;

public:

    //Constructeur
    Bullet();
    Bullet(double x, double y, double z,
        double vx, double vy, double vz);

    //Destructeur
    ~Bullet();

};