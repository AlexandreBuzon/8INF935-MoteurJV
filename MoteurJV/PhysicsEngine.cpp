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
En ce moment cin�matique, et pas plus. L'ajout des forces
est pour le rendu 2.
*/
void PhysicsEngine::integrate(Particle* p_P, double tick)
{
	//EXCEPTION � construire : masse infinie.

	//Calc accel : dictionnaire forces. Partie 2.

	// 1. Calcul de la position � partir de la v�locit� :
	p_P->position = p_P->position+p_P->velocity*tick;

	// 2. Calcul de la v�locit� � partir de l'acc�l�ration :
	p_P->velocity = p_P->velocity + p_P->acceleration * tick;

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
Calcul des trajectoires � l'instant d'apr�s.

Utilisation d'un pointeur pour la population afin de modifier chaque particule.
*/
void PhysicsEngine::nextPosition(Particle* P, double tick, Vecteur3D bounds)
{
	//Parcours de ce qui est point�.
	//for (auto P : *p_particlePopulation) {

		
		/*
		D'abord le d�placement, puis la collision.
		Les particules construites doivent �tre de toutes fa�ons dans les limites au tout d�part.

		Alterner entre objet et adresse fait un peu maladroit, ceci dit.
		*/
		integrate(P, tick);
		boundBounceCheck(P, bounds);


	//}
}

/*
Synchronisation de la physique et de la r�alit�.

Reprise de l'algorithme de pas semi-variable
pr�sent� par Glenn Fiedler.
*/
void PhysicsEngine::physicsLoop(high_resolution_clock::time_point* p_currentTime,
	double* p_deltaTime, double tick, Vecteur3D bounds) {

	high_resolution_clock::time_point newTime = high_resolution_clock::now();

	/*
	somme du nouveau d�calage avec le d�calage existant.
	*/
	*p_deltaTime = duration_cast<duration<double>>(newTime - *p_currentTime).count() + *p_deltaTime;


	// Si trop en retard (100 secondes ici), pas la peine d'essayer. On r�initialise.
	if (*p_deltaTime > 100) {

		*p_deltaTime = 0;

	}

	*p_currentTime = newTime;

	/*
	It�rateur limite pour �viter un cercle vicieux de
	d�calage.

	Avantage : la simulation s'arr�tera eventuellement
	de ralentir si elle prend de plus en
	plus de retard sur la r�alit�.

	Limite : Soit on ne rattrape pas le retard,
	soit on doit faire face � une acc�l�ration de
	la physique.
	*/
	int i = 0;

	/*
	"Consommation" du delta.

	S'ARRETE si :
	-plus de delta � consommer
	OU
	-l'it�rateur limite a atteint le maximum fix�
	(ici 25, fix� arbitrairement) ET un tick est pass�
	en r�alit�.

	Int�r�t du couplage i et chronometre :
	si trop lent pour suivre, i joue son r�le de
	plafond de ralentissement expliqu� pr�c�demment.

	Si, par hasard, la simulation va bien plus vite,
	alors on lui laisse l'opportunit� d'effectuer quelques
	calculs en plus pour rattraper davantage.
	*/
	while ((*p_deltaTime > 0) && ((i < 25) ||
		(duration_cast<duration<double>>(
			high_resolution_clock::now() - *p_currentTime).count()
			< tick))) {

		/*
		Calculs successifs par tick pour garder une continuit�
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

		//Simple sleep improvis� pour ne pas aller trop vite par rapport � la r�alit�.
	}

}
