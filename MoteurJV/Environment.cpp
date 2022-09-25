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

	//Initialisation du temps.
	high_resolution_clock::time_point currentTime = high_resolution_clock::now();

	/*
	Mesure de d�calage entre deux it�rations.
	Pour l'instant, rien.
	*/
	double deltaTime = 0;

	while (/*!glfwWindowShouldClose(window)*/1) {


		/*
		Synchronisation de la physique et de la r�alit�.

		Reprise de l'algorithme de pas semi-variable
		pr�sent� par Glenn Fiedler. 
		*/
		high_resolution_clock::time_point newTime = high_resolution_clock::now();

		/*
		somme du nouveau d�calage avec le d�calage existant.
		*/
		deltaTime = duration_cast<duration<double>>(newTime - currentTime).count() + deltaTime;

		newTime = currentTime;

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
		(ici 25, fix� arbitrairement).

		Cela devrait permettre de rattraper le retard.
		*/
		while ((deltaTime > 0)&&(i < 25)) {

			/*
			Calculs successifs par tick pour garder une continuit�
			dans la progression physique.
			*/
			if (deltaTime > tick) {

				engine.calculate(&particlePopulation, tick, bounds);

				deltaTime -= tick;
				i++;

			}
			/*
			Consommation du reste si le compteur i le permet.
			
			M.Fiedler proposait une interpolation explicite de l'�tat
			t � l'�tat t+tick. Or en sch�matisant, on ne voyait pas
			vraiment de diff�rence avec une simple int�gration de
			l'�tat t � l'�tat t+deltaTime. A approfondir, peut-�tre.
			*/
			else {

				engine.calculate(&particlePopulation, deltaTime, bounds);
				deltaTime = 0;

			}


		}

		while (
			
			duration_cast<duration<double>>(high_resolution_clock::now() - currentTime).count() 
			< tick) {
		
		//Simple sleep improvis� pour ne pas aller trop vite par rapport � la r�alit�.
		}



		//Mise � jour graphique.



	}
}