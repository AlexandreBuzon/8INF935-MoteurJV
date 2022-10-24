#pragma once
#include "ParticleConstraintGenerator.h"

#include "Vecteur3D.h"

class WallContactGenerator :
    public ParticleConstraintGenerator
{

public:

    double restitution;


    /*
    Délimite un mur.
    Les points n'ont pas à être dans le plan.
    */
    std::vector<Vecteur3D> polygonPoints;


    //Caractérise le plan du mur.
    Vecteur3D normal;
    Vecteur3D mainPoint;

    WallContactGenerator();

    WallContactGenerator(double restitution,
        std::vector<Vecteur3D> polygonPoints,
        Vecteur3D normal, Vecteur3D mainPoint);

    ~WallContactGenerator();

    void solve(Particle* p_P);

    bool checkOnWall(Particle* p_P);
    bool checkConflict(Particle* p_P);
    

};

