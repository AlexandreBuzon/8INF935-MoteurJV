#include "Environment.h"

Environment::Environment(double tck, PhysicsEngine e, double x_b, double y_b, double z_b,
	std::vector<Particle> pPopulation)
{
	tick = tck;
	engine = e;
	bounds = Vecteur3D(x_b,y_b,z_b);
	time = 0;
	particlePopulation = pPopulation;
}

Environment::~Environment()
{
	//Nettoyage de la m�moire allou�e.
	delete &bounds;
	delete &engine;

	//"Echange" avec un vecteur vide pour lib�rer la m�moire.
	std::vector<Particle>().swap(particlePopulation);
}

void Environment::play()
{
	//Phase d'initialisation graphique.

	//Parcours de la population.
	for (auto P : particlePopulation) {

		//D�finition graphique.

	}

	while (!glfwWindowShouldClose(window)) {

		engine.calculate(&particlePopulation, tick, time, bounds);

	}

	//A Faire: multithreading ou jsp.
}