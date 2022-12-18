
/*
Classe g�rante de la physique d'un environnement.
*/

#pragma once

#include "Particle.h"

#include "TreeNode.h"
#include "ContactGenerator.h"

#include "Fireball.h"
#include "Ball.h"
#include "FluidDrag.h"
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include "ForceGenerator.h"
#include "LinearFieldGenerator.h"
#include "StaticSPring.h"
#include "Cube.h"
#include "ConstraintGenerator.h"
#include "ParticuleContact.h"

//Mesure de temps pour la boucle de raffraichissement.
#include <chrono>

#include<vector>
#include <map>
#include <memory>

using namespace std::chrono;

class PhysicsEngine
{

public:

	//N�cessaire aux inputs de la d�monstration.
	static PhysicsEngine& GetInstance();

	//Les particules � g�rer.
	std::vector<Particle*>* p_particlePopulation;

	//Les corps rigides � g�rer.
	std::vector<RigidBody*>* p_bodyPopulation;

	//Dictionnaire de forces universelles, donc subies dans tous l'espace.
	std::map<std::string,std::unique_ptr<ForceGenerator>>* p_universalForceRegistry;

	//Dictionnaire de contraintes d�finies.
	std::map<std::string, std::unique_ptr<ConstraintGenerator>>* p_constraints;

	//Constructeurs
	PhysicsEngine();
	PhysicsEngine(std::vector<Particle*>* p_pP,
		std::vector<RigidBody*>* p_bP,
		std::map<std::string, std::unique_ptr<ForceGenerator>>* p_uFR,
		std::map<std::string, std::unique_ptr<ConstraintGenerator>>* p_constraints);

	//Destructeur
	~PhysicsEngine();

	//M�thodes utilis�es en input.
	void display();

	std::map<std::string, std::unique_ptr<ForceGenerator>>* getForceRegistry();

	static void setupKeyInputs(GLFWwindow* window);

	static void callback(
		GLFWwindow* window, int key, int scancode, int action, int mods);

	/*
	Calcul des trajectoires � l'instant d'apr�s.
	*/
	void nextPosition(Particle* P,
		double tick, Vecteur3D bounds);
	void nextPosition(RigidBody* p_B,
		double tick,
		Vecteur3D bounds);

	//M�thode de recherche de collision entre particules.
	std::vector<ParticuleContact> particleCollisionSearch();
	
	//Construction top-down d'un arbre de volumes englobants (inspir� par Ericson).
	void topDownBVTree(TreeNode** tree, std::vector<RigidBody*> elements) {

		TreeNode* p_Node = new TreeNode();

		*tree = p_Node;

		//A FAIRE. VOIR ERICSON OU JSP SUR COMMENT FAIRE UN VOLUME SPHERIQUE ENGLOBANT.
		//*p_Node->buildBV(elements);

		if (elements.size() <= 1) {
		
			p_Node->nodeType = LEAF;
			p_Node->VolumeElements = elements;

		
		}
		else {
			p_Node->nodeType = NODE;

			std::vector<std::vector<RigidBody*>> subsets = partition(elements, p_Node->BVposition.normalize());

			topDownBVTree(&p_Node->left, subsets.at(0));
			topDownBVTree(&p_Node->right, subsets.at(1));

		}

	}


	//A REVOIR
	void search(TreeNode** tree) {

		ContactGenerator cG = ContactGenerator();

		if ((*tree)->left != 0 && (*tree)->right != 0) {

			if ((*tree)->left->nodeType == LEAF && (*tree)->right->nodeType == LEAF) {

				TreeNode*& l = (*tree)->left;
				TreeNode*& r = (*tree)->right;

				double radiusSum = l->BVradius + r->BVradius;

				double distance = (l->BVposition - r->BVposition).norm();

				if (radiusSum >= distance) {

					for (RigidBody* p_rbL : l->VolumeElements) {

						for (RigidBody* p_rbR : r->VolumeElements) {

							cG.narrowPhase(*p_rbL, *p_rbR);

						}

					}

				}

			}
			else {

				search(&(*tree)->left);
				search(&(*tree)->right);
			}


		}
	
	};

	//Algorithme de partitionnement.
	std::vector<std::vector<RigidBody*>> partition(std::vector<RigidBody*> elements, Vecteur3D axis) {
	
		std::vector<std::vector<RigidBody*>> subsets = { {},{} };
		
		double mean = 0;

		//Calcul de la moyenne.
		for (RigidBody* p_rb : elements) {

			mean += p_rb->position * axis;

		}

		mean = mean / elements.size();

		//Tri selon la moyenne.
		for (RigidBody* p_rb : elements) {

			if (p_rb->position * axis <= mean)subsets.at(0).push_back(p_rb);
			else subsets.at(1).push_back(p_rb);

		}

		return subsets;

	};

	/*
	Synchronisation de la physique et de la r�alit�.

	Reprise de l'algorithme de pas semi-variable
	pr�sent� par Glenn Fiedler.
	*/
	void physicsLoop(high_resolution_clock::time_point* p_currentTime,
		double* p_deltaTime, double tick, Vecteur3D bounds);

private:

	//Nous facilite la vie pour les inputs.
	static PhysicsEngine instance;

	//Sommation des forces et calcul de l'acc�l�ration.
	void accelIntegrate(Particle* p_P, double tick);

	void angularAccel(RigidBody* p_B,
		
		double tick);

	void accelIntegrate(RigidBody* p_B, double tick);

	/*
	Calcul des nouveaux vecteurs d'une particule par int�gration.
	*/
	void integrate(Particle* p_P, double tick);

	void integrate(RigidBody* p_B, double tick);

	/*
	Ricochet de particule par r�flexion par rapport aux limites atteintes.

	M�thode placeholder pour garder la particule en place. Sera probablement
	remplac�e ou g�n�ralis�e lors du travail sur les collisions.
	*/
	void boundBounceCheck(Particle* p_P, Vecteur3D bounds);

	//Equivalent corps rigide.
	void boundBounceCheck(RigidBody* p_B, Vecteur3D bounds);

};

