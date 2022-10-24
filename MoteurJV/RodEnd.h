#pragma once
#include "Particle.h"
class RodEnd :
    public Particle
{

    RodEnd();
    RodEnd(Vecteur3D p, Vecteur3D v, 
        std::vector<std::string> constraints);
    ~RodEnd();

};

