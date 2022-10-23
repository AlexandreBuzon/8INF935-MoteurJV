#include "BallForces.h"


BallForces::BallForces() {

    spawnSpeed = 150;
    inverseMass = 0.04;
    std::vector<std::string> permanentForces = { "gravity", "Fluid", "ParticuleSpring","ParticuleSpringA","StaticSpring" };

    position.setX(0);
    position.setY(0);
    position.setZ(0);

    velocity.setX(spawnSpeed);
    velocity.setY(0);
    velocity.setZ(0);

    acceleration.setX(0);
    acceleration.setY(0);
    acceleration.setZ(0);

}

BallForces::BallForces(double x, double y, double z,
    double vx, double vy, double vz,std::string permanentForce) {



    spawnSpeed = 150;
    inverseMass = 0.04;
    permanentForces.push_back(permanentForce);

    position.setX(x);
    position.setY(y);
    position.setZ(z);

    velocity.setX(vx);
    velocity.setY(vy);
    velocity.setZ(vz);

    if (velocity.norm() != 0) velocity = velocity * (spawnSpeed / velocity.norm());

    acceleration.setX(0);
    acceleration.setY(0);
    acceleration.setZ(0);

}

BallForces::~BallForces() {}