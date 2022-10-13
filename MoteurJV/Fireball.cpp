#include "Fireball.h"

Fireball::Fireball() {

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

/*
Avec position et vélocité de départ.

En réalité, seule la direction de la vélocité compte.
Le vecteur est re-normalisé à spawnVelocity.
*/
Fireball::Fireball(double x, double y, double z,
    double vx, double vy, double vz) {

    position.setX(x);
    position.setY(y);
    position.setZ(z);

    velocity.setX(vx);
    velocity.setY(vy);
    velocity.setZ(vz);

    velocity = velocity * (spawnSpeed/velocity.norm());

    acceleration.setX(0);
    acceleration.setY(0);
    acceleration.setZ(0);

}