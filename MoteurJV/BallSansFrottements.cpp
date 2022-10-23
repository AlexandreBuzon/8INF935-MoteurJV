
#include "BallSansFrottements.h"


BallSansFrottements::BallSansFrottements() {

    spawnSpeed = 150;
    inverseMass = 0.04;
    std::vector<std::string> permanentForces = { "gravity"};

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

BallSansFrottements::BallSansFrottements(double x, double y, double z,
    double vx, double vy, double vz) {



    spawnSpeed = 150;
    inverseMass = 0.04;
    permanentForces = { "gravity"};

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

BallSansFrottements::~BallSansFrottements() {}