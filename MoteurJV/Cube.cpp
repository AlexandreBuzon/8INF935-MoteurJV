#include "Cube.h"

Cube::Cube() {

    permanentForces =
    { {"g", Vecteur3D(0,0,0)},
        {"r1", Vecteur3D(0,0,0)},
        {"r2", Vecteur3D(-5,6,2)} };

    constraints = {};

    inverseMass = -1;

    inverseInertia = Matrix33(
        12 * 200 * inverseMass, 0, 0,
        0, 12 * 200 * inverseMass, 0,
        0, 0, 12 * 200 * inverseMass);

    restitution = 0;

    position = Vecteur3D();
    velocity = Vecteur3D();
    acceleration = Vecteur3D();

    orientation = Quaternion();
    angularV = Vecteur3D();
    torqueSum = Vecteur3D();

    transformMatrix.setOrientationAndPosition(
        orientation, position);

    GLvertices = { 0.05f,  0.05f,  0.05f,  1.0f,  0.0f,  0.0f,
                    0.05f,  0.05f,  -0.05f,  1.0f,  1.0f,  0.0f,
                    0.05f,  -0.05f,  -0.05f,  1.0f,  1.0f,  1.0f,
                    0.05f,  -0.05f,  0.05f,  0.0f,  1.0f,  1.0f,
                    -0.05f,  0.05f,  -0.05f,  1.0f,  0.0f,  1.0f,
                    -0.05f,  0.05f,  0.05f,  0.0f,  0.0f,  1.0f,
                    -0.05f,  0.05f,  -0.05f,  0.0f,  1.0f,  0.0f,
                    -0.05f,  -0.05f,  -0.05f,  0.0f,  0.0f,  0.0f, };

    triangles = { 0,1,2,  0,3,2, //triplet ~ une demi-face
                    0,5,6,  0,1,6,
                    0,5,4,  0,3,4,
                    7,5,4,  7,5,6,
                    7,2,1,  7,6,1,
                    7,3,4,  7,3,2 };

}

Cube::Cube(double inverseMass, float restitution,
    Vecteur3D position, Vecteur3D velocity,
    Vecteur3D angularV, Quaternion orientation) {

    permanentForces =
    { //{"g", Vecteur3D(0,0,0)},
        //{"r1", Vecteur3D(0,0,0)}//,
        //{"r2", Vecteur3D(-5,6,2)} 
    };

    constraints = {};

    this->inverseMass = inverseMass;

    this->inverseInertia = Matrix33(
        12 * 200 * inverseMass,0,0,
        0, 12 * 200 * inverseMass, 0,
        0, 0, 12 * 200 * inverseMass);

    this->restitution = restitution;

    this->position = position;
    this->velocity = velocity;
    acceleration = Vecteur3D();

    this->orientation = orientation;
    this->angularV = angularV;
    torqueSum = Vecteur3D();

    transformMatrix.setOrientationAndPosition(
        orientation, position);

    GLvertices = { 0.05f,  0.05f,  0.05f,  1.0f,  0.0f,  0.0f,
                    0.05f,  0.05f,  -0.05f,  1.0f,  1.0f,  0.0f,
                    0.05f,  -0.05f,  -0.05f,  1.0f,  1.0f,  1.0f,
                    0.05f,  -0.05f,  0.05f,  0.0f,  1.0f,  1.0f,
                    -0.05f,  0.05f,  -0.05f,  1.0f,  0.0f,  1.0f,
                    -0.05f,  0.05f,  0.05f,  0.0f,  0.0f,  1.0f, 
                    -0.05f,  0.05f,  -0.05f,  0.0f,  1.0f,  0.0f, 
                    -0.05f,  -0.05f,  -0.05f,  0.0f,  0.0f,  0.0f, };

    triangles = { 0,1,2,  0,3,2, //triplet ~ une demi-face
                    0,5,6,  0,1,6,
                    0,5,4,  0,3,4,
                    7,5,4,  7,5,6,
                    7,2,1,  7,6,1,
                    7,3,4,  7,3,2 };

}

Cube::~Cube(){}