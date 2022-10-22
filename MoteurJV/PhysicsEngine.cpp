#include "PhysicsEngine.h"


//Constructeurs
PhysicsEngine::PhysicsEngine() {

	g = 10;
    p_particlePopulation = NULL;
}

PhysicsEngine::PhysicsEngine(float G, std::vector<Particle*>* p_pP)
{
	g = G;
    p_particlePopulation = p_pP;
}

//Destructeur
PhysicsEngine::~PhysicsEngine()
{

}


void accelIntegrate(Particle* p_P, double tick) {

    //Initialisation.
    p_P->acceleration = Vecteur3D(0, 0, 0);

    if (!p_P->permanentForces.empty()) {



        /*
        for(std::string force : p_P->permanentForces) {

            //(dico forces perm -> updateforce)

        }*/

    }

}



/*
Calcul des nouveaux vecteurs d'une particule
En ce moment cinématique, et pas plus. L'ajout des forces
est pour le rendu 2.
*/
void PhysicsEngine::integrate(Particle* p_P, double tick)
{
	//EXCEPTION à construire : masse infinie.

	//Calc accel : dictionnaire forces. Partie 2.

	// 1. Calcul de la position à partir de la vélocité :
	p_P->position = p_P->position+p_P->velocity*tick;

	// 2. Calcul de la vélocité à partir de l'accélération :
	p_P->velocity = p_P->velocity + p_P->acceleration * tick;

}


/*
* Méthode placeholder pour garder la particule dans un cadre fermé.
* 
Ricochet de particule par réflexion par rapport à la limite atteinte.
L'axe définit la dimension où il y a dépassement.

Mémo : char => '' au lieu de "".
*/
void PhysicsEngine::boundBounceCheck(Particle* p_P, Vecteur3D bounds)
{
	//Vérification de collision avec les limites.
    //Limites selon Ox.
    if (p_P->position.getX() < 0) {

        p_P->position.setX(0);
        p_P->velocity.setX(-p_P->velocity.getX());
        p_P->acceleration.setX(-p_P->acceleration.getX());
    }
    if (p_P->position.getX() > bounds.getX()) {

        p_P->position.setX(bounds.getX());
        p_P->velocity.setX(-p_P->velocity.getX());
        p_P->acceleration.setX(-p_P->acceleration.getX());
    }
    //Selon Oy.
    if (p_P->position.getY() < 0) {

        p_P->position.setY(0);
        p_P->velocity.setY(-p_P->velocity.getY());
        p_P->acceleration.setY(-p_P->acceleration.getY());
    }
    if (p_P->position.getY() > bounds.getY()) {

        p_P->position.setY(bounds.getY());
        p_P->velocity.setY(-p_P->velocity.getY());
        p_P->acceleration.setY(-p_P->acceleration.getY());

    }

    //Selon Oz.
    if (p_P->position.getZ() < 0) {

        p_P->position.setZ(0);
        p_P->velocity.setZ(-p_P->velocity.getZ());
        p_P->acceleration.setZ(-p_P->acceleration.getZ());
    }
    if (p_P->position.getZ() > bounds.getZ()) {

        p_P->position.setZ(bounds.getZ());
        p_P->velocity.setZ(-p_P->velocity.getZ());
        p_P->acceleration.setZ(-p_P->acceleration.getZ());

    }
}

/*
Calcul des trajectoires à l'instant d'après.

Utilisation d'un pointeur pour la population afin de modifier chaque particule.
*/
void PhysicsEngine::nextPosition(Particle* P, double tick, Vecteur3D bounds)
{
	//Parcours de ce qui est pointé.
	//for (auto P : *p_particlePopulation) {

		
		/*
		D'abord le déplacement, puis la collision.
		Les particules construites doivent être de toutes façons dans les limites au tout départ.

		Alterner entre objet et adresse fait un peu maladroit, ceci dit.
		*/
		integrate(P, tick);
		boundBounceCheck(P, bounds);


	//}
}

/*
Synchronisation de la physique et de la réalité.

Reprise de l'algorithme de pas semi-variable
présenté par Glenn Fiedler.
*/
void PhysicsEngine::physicsLoop(high_resolution_clock::time_point* p_currentTime,
	double* p_deltaTime, double tick, Vecteur3D bounds) {

	high_resolution_clock::time_point newTime = high_resolution_clock::now();

	/*
	somme du nouveau décalage avec le décalage existant.
	*/
	*p_deltaTime = duration_cast<duration<double>>(newTime - *p_currentTime).count() + *p_deltaTime;


	// Si trop en retard (100 secondes ici), pas la peine d'essayer. On réinitialise.
	if (*p_deltaTime > 100) {

		*p_deltaTime = 0;

	}

	*p_currentTime = newTime;

	/*
	Itérateur limite pour éviter un cercle vicieux de
	décalage.

	Avantage : la simulation s'arrêtera eventuellement
	de ralentir si elle prend de plus en
	plus de retard sur la réalité.

	Limite : Soit on ne rattrape pas le retard,
	soit on doit faire face à une accélération de
	la physique.
	*/
	int i = 0;

	/*
	"Consommation" du delta.

	S'ARRETE si :
	-plus de delta à consommer
	OU
	-l'itérateur limite a atteint le maximum fixé
	(ici 25, fixé arbitrairement) ET un tick est passé
	en réalité.

	Intérêt du couplage i et chronometre :
	si trop lent pour suivre, i joue son rôle de
	plafond de ralentissement expliqué précédemment.

	Si, par hasard, la simulation va bien plus vite,
	alors on lui laisse l'opportunité d'effectuer quelques
	calculs en plus pour rattraper davantage.
	*/
	while ((*p_deltaTime > 0) && ((i < 25) ||
		(duration_cast<duration<double>>(
			high_resolution_clock::now() - *p_currentTime).count()
			< tick))) {

		/*
		Calculs successifs par tick pour garder une continuité
		dans la progression physique.
		*/
		if (*p_deltaTime > tick) {

			for (size_t j = 0; j < p_particlePopulation->size(); j++) {
				nextPosition(p_particlePopulation->at(j), tick, bounds);
			}

			*p_deltaTime -= tick;
			i++;

		}

		//Consommation du reste si le compteur i le permet.
		else {

			for (size_t j = 0; j < p_particlePopulation->size(); j++) {
				nextPosition(p_particlePopulation->at(j), *p_deltaTime, bounds);
			}

			*p_deltaTime = 0;

		}

	}

	while (
		duration_cast<duration<double>>(high_resolution_clock::now() - *p_currentTime).count()
		< tick) {

		//Simple sleep improvisé pour ne pas aller trop vite par rapport à la réalité.
	}

}
