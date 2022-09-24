/*
Environnement de jeu

Définit les particules existantes et les coordonnées limites.
*/

//Inclut aussi particule et vecteur par transitivité.
#include "PhysicsEngine.h"

//Pour la représentation graphique.
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#pragma once
class Environment
{
public:

	//ATTRIBUTS

	//Les limites en un vecteur.
	Vecteur3D bounds;

	//Mesure du temps.
	double time;

	//Le pas de mesure en deux instants.
	double tick;

	//Population de particules.
	std::vector<Particle> particlePopulation;

	//Moteur physique utilisé.
	PhysicsEngine engine;

	//METHODES

	//Constructeur
	Environment(double tck, PhysicsEngine e, double x_b, double y_b, double z_b, std::vector<Particle> particlePopulation);

	//Destructeur
	~Environment();

	/*
	L'environnement est ici amalgamé au moteur graphique, par simplicité.
	Idéalement, on aurait pris la peine de découpler aussi.

	Il y a correspondance d'indice entre populationParticle et
	populationTriangle. d'où le paramétrage.

	represent crée les triangles à associer aux particules.
	*/

	//represent(int index);

	void play();




};

