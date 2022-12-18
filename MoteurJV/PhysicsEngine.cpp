#include "PhysicsEngine.h"

#include <iostream>

PhysicsEngine PhysicsEngine::instance = PhysicsEngine();

//Constructeurs
PhysicsEngine::PhysicsEngine() {
    p_particlePopulation = NULL;
	p_bodyPopulation = NULL;
	p_universalForceRegistry = NULL;
	p_constraints = NULL;

}

PhysicsEngine::PhysicsEngine(std::vector<Particle*>* p_pP,
	std::vector<RigidBody*>* p_bP,
	std::map<std::string, std::unique_ptr<ForceGenerator>>* p_uFR,
	std::map<std::string, std::unique_ptr<ConstraintGenerator>>* p_constraints){
    p_particlePopulation = p_pP;
	p_bodyPopulation = p_bP;
	p_universalForceRegistry = p_uFR;
	this->p_constraints = p_constraints;
}

//Destructeur
PhysicsEngine::~PhysicsEngine(){}


//M�thodes d'inputs.
std::map<std::string, std::unique_ptr<ForceGenerator>>* PhysicsEngine::getForceRegistry() {
	return p_universalForceRegistry;
}

void  PhysicsEngine::setupKeyInputs(GLFWwindow* window) {
	glfwSetKeyCallback(window, PhysicsEngine::callback);
}

void PhysicsEngine::callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	//Input
	PhysicsEngine& engine = PhysicsEngine::GetInstance();
	 
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		std::cout << "FIN" << std::endl;
		glfwSetWindowShouldClose(window, true);
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		std::cout << "Nombre de force :" << std::endl;
		instance.display();
	}

	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
		std::cout << "GRAVITE" << std::endl;
		engine.getForceRegistry()->insert(std::make_pair("g", new LinearFieldGenerator(Vecteur3D(0, -10, 0), false)));
	}
	
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
		engine.getForceRegistry()->insert(std::make_pair(
			"p1", new LinearFieldGenerator(Vecteur3D(1.1, 0, 0), true)));
	}
	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
		engine.getForceRegistry()->insert(std::make_pair(
			"p2", new LinearFieldGenerator(Vecteur3D(0, -1, 0), true)));
	}
	if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS) {
		engine.getForceRegistry()->insert(std::make_pair(
			"p3", new LinearFieldGenerator(Vecteur3D(0, 0, 1.3), true)));
	}
	if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS) {
		engine.getForceRegistry()->insert(std::make_pair(
			"r", new StaticSpring(Vecteur3D(0, 0, 0), 5, 500)));
	}
	if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS) {
		engine.getForceRegistry()->insert(std::make_pair(
			"t", new FluidDrag(0, 0, 25)));
	}
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
		engine.getForceRegistry()->clear();
	}
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
		
	}
	

}
void PhysicsEngine::display() {
	for (size_t j = 0; j < p_universalForceRegistry->size(); j++) {
		std::cout << j << std::endl;
	}
}

PhysicsEngine& PhysicsEngine::GetInstance() {
	return instance;
}


//Acc�l�ration de particule sur une frame.
void PhysicsEngine::accelIntegrate(Particle* p_P, double tick) {

    //Initialisation.
    p_P->acceleration = Vecteur3D(0, 0, 0);

    if (!p_P->permanentForces.empty()) {

		for (std::string force : p_P->permanentForces) {

			p_universalForceRegistry->at(force)->updateForce(p_P);

		}
    }

}

//Acc�l�ration lin�aire du corps rigide.
void PhysicsEngine::accelIntegrate(RigidBody* p_B, double tick) {

	//Initialisation.
	p_B->acceleration = Vecteur3D(0, 0, 0);

	if (!p_B->permanentForces.empty()) {

		for (bodyForce force : p_B->permanentForces) {

			auto index = p_universalForceRegistry->
				find(force.idForce);

			/*
			Aucun risque de comportement impr�visible
			si le g�n�rateur est supprim� de la table.
			*/
			if (index != p_universalForceRegistry->end()) {

				p_universalForceRegistry->at(force.idForce)->
					updateForce(p_B, force.applicationP);
			}
		}
	}

}

//Acc�l�ration angulaire du corps rigide.
void PhysicsEngine::angularAccel(RigidBody* p_B,
	
	double tick) {

	//Initialisation.
	p_B->torqueSum = Vecteur3D(0, 0, 0);

	if (!p_B->permanentForces.empty()) {

		for (bodyForce force : p_B->permanentForces) {

			auto index = p_universalForceRegistry->
				find(force.idForce);

			/*
			Aucun risque de comportement impr�visible
			si le g�n�rateur est supprim� de la table.
			*/
			if (index != p_universalForceRegistry->end()) {

				p_universalForceRegistry->at(force.idForce)
				->updateTorque(p_B, force.applicationP);

			}

		}

	}

}




//Calcul des nouveaux vecteurs d'une particule
void PhysicsEngine::integrate(Particle* p_P, double tick)
{
	// 1. L'acc�l�ration.
	accelIntegrate(p_P,tick);

	// 2. Calcul de la v�locit� � partir de l'acc�l�ration :
	p_P->velocity = p_P->velocity + p_P->acceleration * tick;

	// 3. Calcul de la position � partir de la v�locit� :
	p_P->position = p_P->position+p_P->velocity*tick;
}

//Equivalent pour corps rigide.
void PhysicsEngine::integrate(RigidBody* p_B, double tick) {

	Matrix34 Mb_1 = p_B->transformMatrix.Inverse();

	//1.1. L'acc�l�ration
	accelIntegrate(p_B, tick);

	//1.2. V�locit�
	p_B->velocity = p_B->velocity + p_B->acceleration * tick;

	//1.3. Position
	p_B->position = p_B->position + p_B->velocity * tick;

	//2.1 Acc�l�ration angulaire.
	angularAccel(p_B, tick);

	Matrix33* p_R = new Matrix33();
	Matrix33* p_Ig_1 = new Matrix33();

	*p_R = p_B->transformMatrix.getM33();

	

	//Inverse matrice d'inertie en base globale.
	*p_Ig_1 = *p_R * p_B->inverseInertia * p_R->Inverse();

	delete p_R;
	p_R = 0;

	//2.2. Vitesse angulaire
	p_B->angularV = p_B->angularV + (*p_Ig_1 * p_B->torqueSum) * tick;

	delete p_Ig_1;
	p_Ig_1 = 0;

	//2.3 Orientation
	p_B->orientation = 
		p_B->orientation.UpdateByAngularVelocity(
			p_B->angularV,tick);

	p_B->orientation.Normalise();

	//3. Transformation affine
	p_B->transformMatrix.setOrientationAndPosition(
	p_B->orientation,p_B->position);

}


/*
* M�thode pour garder la particule dans un cadre ferm�.
* 
Ricochet de particule par r�flexion par rapport � la limite atteinte.
L'axe d�finit la dimension o� il y a d�passement.
*/
void PhysicsEngine::boundBounceCheck(Particle* p_P, Vecteur3D bounds)
{
	//V�rification de collision avec les limites.
    //Limites selon Ox.
    if (p_P->position.getX() < -1000) {

        p_P->position.setX(-1000);
        p_P->velocity.setX(-p_P->velocity.getX());
        p_P->acceleration.setX(-p_P->acceleration.getX());
    }
    if (p_P->position.getX() > bounds.getX()) {

        p_P->position.setX(bounds.getX());
        p_P->velocity.setX(-p_P->velocity.getX());
        p_P->acceleration.setX(-p_P->acceleration.getX());
    }
    //Selon Oy.
    if (p_P->position.getY() < -1000) {

        p_P->position.setY(-1000);
        p_P->velocity.setY(-p_P->velocity.getY());
        p_P->acceleration.setY(-p_P->acceleration.getY());
    }
    if (p_P->position.getY() > bounds.getY()) {

        p_P->position.setY(bounds.getY());
        p_P->velocity.setY(-p_P->velocity.getY());
        p_P->acceleration.setY(-p_P->acceleration.getY());

    }

    //Selon Oz.
    if (p_P->position.getZ() < -1000) {

        p_P->position.setZ(-1000);
        p_P->velocity.setZ(-p_P->velocity.getZ());
        p_P->acceleration.setZ(-p_P->acceleration.getZ());
    }
    if (p_P->position.getZ() > bounds.getZ()) {

        p_P->position.setZ(bounds.getZ());
        p_P->velocity.setZ(-p_P->velocity.getZ());
        p_P->acceleration.setZ(-p_P->acceleration.getZ());

    }
}

void PhysicsEngine::boundBounceCheck(RigidBody* p_B, Vecteur3D bounds) {

	Vecteur3D* p_p = &p_B->position;

	//Selon Ox.
	if ((p_p->x < -bounds.x)||(p_p->x > bounds.x)) {

		if (p_p->x < 0)p_p->x = -bounds.x;
		else p_p->x = bounds.x;
		p_B->velocity.x = -p_B->velocity.x;
		p_B->acceleration.x = -p_B->acceleration.x;

	}
	//Selon Oy.
	if ((p_p->y < -bounds.y) || (p_p->y > bounds.y)) {

		if (p_p->y < 0)p_p->y = -bounds.y;
		else p_p->y = bounds.y;
		p_B->velocity.y = -p_B->velocity.y;
		p_B->acceleration.y = -p_B->acceleration.y;

	}
	//Selon Oz.
	if ((p_p->z < -bounds.z) || (p_p->z > bounds.z)) {

		if (p_p->z < 0)p_p->z = -bounds.z;
		else p_p->z = bounds.z;
		p_B->velocity.z = -p_B->velocity.z;
		p_B->acceleration.z = -p_B->acceleration.z;

	}
}

/*
Calcul des trajectoires � l'instant d'apr�s.
D'abord int�gration, puis gestion de collisions.
*/
void PhysicsEngine::nextPosition(Particle* p_P, double tick, Vecteur3D bounds)
{

		
		/*
		D'abord le d�placement, puis la collision.
		Les particules construites doivent �tre de toutes fa�ons dans les limites au tout d�part.
		*/
		integrate(p_P, tick);

		if (!p_P->constraints.empty()) {

			for (std::string c : p_P->constraints) {

				if (p_constraints->at(c)->checkConflict(p_P))
					p_constraints->at(c)->solve(p_P);

			}

		}

		boundBounceCheck(p_P, bounds);

}

void PhysicsEngine::nextPosition(RigidBody* p_B, double tick, Vecteur3D bounds)
{

	integrate(p_B, tick);

	//BROAD PHASE

	//NARROW PHASE
	/*
	for (noeud p�re de feuille){
	
		RigidBody& B1 = noeud gauche;
		RigidBody& B2 = noeud droit;

		narrowPhase(B1,B2);
	
	}
	
	*/

	boundBounceCheck(p_B, bounds);

}




std::vector<ParticuleContact> PhysicsEngine::particleCollisionSearch() {

	std::vector<ParticuleContact> conflictList = {};

	for (size_t i = 0; i < p_particlePopulation->size(); i++) {

		for (size_t j = i+1; j < p_particlePopulation->size(); j++) {

			double distance =
				(p_particlePopulation->at(i)->position 
					- p_particlePopulation->at(j)->position).norm();

			double d1 = p_particlePopulation->at(i)->rayonCollision;
			double d2 = p_particlePopulation->at(j)->rayonCollision;

			if (distance < d1 + d2) {

				conflictList.push_back(ParticuleContact(1, d1 + d2 - distance,
					(p_particlePopulation->at(i)->position
						- p_particlePopulation->at(j)->position).normalize(),
					p_particlePopulation->at(i),
					p_particlePopulation->at(j)));

			}

		}

	}

	return conflictList;

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


			if (!p_particlePopulation->empty()) {

				for (size_t j = 0; j < p_particlePopulation->size(); j++) {
					nextPosition(p_particlePopulation->at(j), tick, bounds);
				}

			}

			if (!p_bodyPopulation->empty()) {

				for (size_t j = 0; j < p_bodyPopulation->size(); j++) {
					nextPosition(p_bodyPopulation->at(j), tick, bounds);
				}
			}

			std::vector<ParticuleContact> conflicts = particleCollisionSearch();

			while (!conflicts.empty()) {

				conflicts.back().resolve(tick);
				conflicts.pop_back();
			}


			*p_deltaTime -= tick;
			i++;

		}

		//Consommation du reste si le compteur i le permet.
		else {

			if (!p_particlePopulation->empty()) {

				for (size_t j = 0; j < p_particlePopulation->size(); j++) {
					nextPosition(p_particlePopulation->at(j), tick, bounds);
				}

			}

			if (!p_bodyPopulation->empty()) {

				for (size_t j = 0; j < p_bodyPopulation->size(); j++) {
					nextPosition(p_bodyPopulation->at(j), tick, bounds);
				}
			}

			*p_deltaTime = 0;

			std::vector<ParticuleContact> conflicts = particleCollisionSearch();

			while (!conflicts.empty()) {

				conflicts.back().resolve(tick);
				conflicts.pop_back();
			}

		}

	}

	while (
		duration_cast<duration<double>>(high_resolution_clock::now() - *p_currentTime).count()
		< tick) {

		//Simple sleep improvis� pour ne pas aller trop vite par rapport � la r�alit�.
	}

}
