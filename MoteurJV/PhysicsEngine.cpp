#include "PhysicsEngine.h"


//Constructeurs
PhysicsEngine::PhysicsEngine() {

	g = 10;

}

PhysicsEngine::PhysicsEngine(float G)
{
	g = G;
}

//Destructeur
PhysicsEngine::~PhysicsEngine()
{

}

/*
Calcul des nouveaux vecteurs d'une particule
En ce moment cin�matique, et pas plus. L'ajout des forces
est pour le rendu 2.
*/
void PhysicsEngine::newParticleState(Particle* p_P, double tick)
{
	//EXCEPTION � construire : masse infinie.

	//Calc accel : dictionnaire forces. Partie 2.

	// 1. Calcul de la position � partir de la v�locit� :
	*p_P->position = *p_P->position+*p_P->velocity*tick;

	// 2. Calcul de la v�locit� � partir de l'acc�l�ration :
	*p_P->velocity = *p_P->velocity + *p_P->acceleration * tick;

}


/*
* M�thode placeholder pour garder la particule dans un cadre ferm�.
* 
Ricochet de particule par r�flexion par rapport � la limite atteinte.
L'axe d�finit la dimension o� il y a d�passement.

M�mo : char => '' au lieu de "".
*/
void PhysicsEngine::boundBounceCheck(Particle* p_P, Vecteur3D bounds)
{
	//V�rification de collision avec les limites.
    //Limites selon Ox.
    if (p_P->position->getX() < 0) {

        p_P->position->setX(0);
        p_P->velocity->setX(-p_P->velocity->getX());
        p_P->acceleration->setX(-p_P->acceleration->getX());
    }
    if (p_P->position->getX() > bounds.getX()) {

        p_P->position->setX(bounds.getX());
        p_P->velocity->setX(-p_P->velocity->getX());
        p_P->acceleration->setX(-p_P->acceleration->getX());
    }
    //Selon Oy.
    if (p_P->position->getY() < 0) {

        p_P->position->setY(0);
        p_P->velocity->setY(-p_P->velocity->getY());
        p_P->acceleration->setY(-p_P->acceleration->getY());
    }
    if (p_P->position->getY() > bounds.getY()) {

        p_P->position->setY(bounds.getY());
        p_P->velocity->setY(-p_P->velocity->getY());
        p_P->acceleration->setY(-p_P->acceleration->getY());

    }
    //Selon Oz.
    if (p_P->position->getZ() < 0) {

        p_P->position->setZ(0);
        p_P->velocity->setZ(-p_P->velocity->getZ());
        p_P->acceleration->setZ(-p_P->acceleration->getZ());
    }
    if (p_P->position->getY() > bounds.getZ()) {

        p_P->position->setZ(bounds.getZ());
        p_P->velocity->setZ(-p_P->velocity->getZ());
        p_P->acceleration->setZ(-p_P->acceleration->getZ());

    }
}

/*
Calcul des trajectoires � l'instant d'apr�s.

Utilisation d'un pointeur pour la population afin de modifier chaque particule.
*/
void PhysicsEngine::calculate(Particle* P, double tick, Vecteur3D bounds)
{
	//Parcours de ce qui est point�.
	//for (auto P : *p_particlePopulation) {

		
		/*
		D'abord le d�placement, puis la collision.
		Les particules construites doivent �tre de toutes fa�ons dans les limites au tout d�part.

		Alterner entre objet et adresse fait un peu maladroit, ceci dit.
		*/
		newParticleState(P, tick);
		boundBounceCheck(P, bounds);


	//}
}

/*
Interpolation des positions.

La boucle de raffraichissement s'execute de telle sorte
qu'il y a souvent un d�calage l�ger entre r�alit� et physique.

l'interpolation
*/
