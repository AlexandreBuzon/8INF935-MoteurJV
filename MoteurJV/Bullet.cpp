
#include "Bullet.h"

#include "Bullet.h"


Bullet::Bullet() {

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

Bullet::Bullet(double x, double y, double z,
    double vx, double vy, double vz) {

    position.setX(x);
    position.setY(y);
    position.setZ(z);

    velocity.setX(vx);
    velocity.setY(vy);
    velocity.setZ(vz);

    velocity = velocity * (spawnSpeed / velocity.norm());

    acceleration.setX(0);
    acceleration.setY(0);
    acceleration.setZ(0);

}