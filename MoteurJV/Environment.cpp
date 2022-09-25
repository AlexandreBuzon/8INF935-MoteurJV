#include "Environment.h"

Environment::Environment(double tck, PhysicsEngine e, double x_b, double y_b, double z_b,
	std::vector<Particle> pPopulation)
{
	tick = tck;
	engine = e;
	bounds = Vecteur3D(x_b,y_b,z_b);
	particlePopulation = pPopulation;
}

Environment::~Environment()
{
	//Nettoyage de la mémoire allouée.
	delete &bounds;
	delete &engine;

	//"Echange" avec un vecteur vide pour libérer la mémoire.
	std::vector<Particle>().swap(particlePopulation);
}

void Environment::play()
{
	//Phase d'initialisation graphique.

	//Parcours de la population.
	for (auto P : particlePopulation) {

		//Définition graphique.

	}

	//Initialisation du temps.
	high_resolution_clock::time_point currentTime = high_resolution_clock::now();

	/*
	Mesure de décalage entre deux itérations.
	Pour l'instant, rien.
	*/
	double deltaTime = 0;

	while (/*!glfwWindowShouldClose(window)*/1) {


		/*
		Synchronisation de la physique et de la réalité.

		Reprise de l'algorithme de pas semi-variable
		présenté par Glenn Fiedler. 
		*/
		high_resolution_clock::time_point newTime = high_resolution_clock::now();

		/*
		somme du nouveau décalage avec le décalage existant.
		*/
		deltaTime = duration_cast<duration<double>>(newTime - currentTime).count() + deltaTime;

		newTime = currentTime;

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
		(ici 25, fixé arbitrairement).

		Cela devrait permettre de rattraper le retard.
		*/
		while ((deltaTime > 0)&&(i < 25)) {

			/*
			Calculs successifs par tick pour garder une continuité
			dans la progression physique.
			*/
			if (deltaTime > tick) {

				engine.calculate(&particlePopulation, tick, bounds);

				deltaTime -= tick;
				i++;

			}
			/*
			Consommation du reste si le compteur i le permet.
			
			M.Fiedler proposait une interpolation explicite de l'état
			t à l'état t+tick. Or en schématisant, on ne voyait pas
			vraiment de différence avec une simple intégration de
			l'état t à l'état t+deltaTime. A approfondir, peut-être.
			*/
			else {

				engine.calculate(&particlePopulation, deltaTime, bounds);
				deltaTime = 0;

			}


		}

		while (
			
			duration_cast<duration<double>>(high_resolution_clock::now() - currentTime).count() 
			< tick) {
		
		//Simple sleep improvisé pour ne pas aller trop vite par rapport à la réalité.
		}



		//Mise à jour graphique.



	}
}