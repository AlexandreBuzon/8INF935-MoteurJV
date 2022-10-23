
#pragma once
#include "Particle.h"
class Ball :
    public Particle
{

public:


    Ball();
    Ball(double x, double y, double z,
        double vx, double vy, double vz);


    ~Ball();

};