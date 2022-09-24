/*
Environnement de jeu

D�finit les particules existantes et les coordonn�es limites.
*/

//Inclut aussi particule et vecteur par transitivit�.
#include "PhysicsEngine.h"

//Pour la repr�sentation graphique.
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

	//Moteur physique utilis�.
	PhysicsEngine engine;

	//METHODES

	//Constructeur
	Environment(double tck, PhysicsEngine e, double x_b, double y_b, double z_b, std::vector<Particle> particlePopulation);

	//Destructeur
	~Environment();

	/*
	L'environnement est ici amalgam� au moteur graphique, par simplicit�.
	Id�alement, on aurait pris la peine de d�coupler aussi.

	Il y a correspondance d'indice entre populationParticle et
	populationTriangle. d'o� le param�trage.

	represent cr�e les triangles � associer aux particules.
	*/

	//represent(int index);

	void play();




};

