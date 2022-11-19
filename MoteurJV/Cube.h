//Classe de corps rigide utilisée dans la démonstration.

#pragma once
#include "RigidBody.h"
class Cube :
    public RigidBody
{

public:

    Cube();

    Cube(double inverseMass, float restitution,
        Vecteur3D position, Vecteur3D velocity,
        Vecteur3D angularV, Quaternion orientation);

    ~Cube();

};

