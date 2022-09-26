#include "Environment.h"
#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "EBO.h"
#include "VBO.h"
#include "VAO.h"
#include "shaderClass.h"
#include "Fireball.h"
#include "Particle.h"

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
	/*
	* Initialisation graphique.
	*
	Reprise du programme de Victor Gordan, avec modifications adaptées.
	*/

	//Fireball ici.
	Fireball fireB = Fireball(50,50,50,25,2,10);
	particlePopulation.push_back(fireB);
	// Vertices coordinates
	GLfloat vertices[] =
	{ // sur une ligne : x, y, z, R, V, B
		-0.1f, -0.1f, 0.0f, 1.0f, 0.0f, 0.0f,
		-0.1f, 0.1f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.1f, -0.1f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.1f, 0.1f, 0.0f, 1.0f, 0.0f, 0.0f,
	};

	// Indices for vertices order
	GLuint indices[] =
	{
		0,1,2,
		3,1,2
	};


	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
	GLFWwindow* window = glfwCreateWindow(800, 800, "YoutubeOpenGL", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	//Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, 800, 800);



	// Generates Shader object using shaders defualt.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");



	// Generates Vertex Array Object and binds it
	VAO VAO1;
	VAO1.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	// Generates Element Buffer Object and links it to indices
	EBO EBO1(indices, sizeof(indices));

	// Links VBO attributes such as coordinates and colors to VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	// Gets ID of uniform called "scale"
	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	//Initialisation du temps.
	high_resolution_clock::time_point currentTime = high_resolution_clock::now();

	/*
	Mesure de décalage entre deux itérations.
	Pour l'instant, rien.
	*/
	double deltaTime = 0;

	while (!glfwWindowShouldClose(window)) {


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


		// Si trop en retard (100 secondes ici), pas la peine d'essayer. On réinitialise.
		if (deltaTime > 100) {

			deltaTime = 0;

		}

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
		(ici 25, fixé arbitrairement) ET un tick est passé
		en réalité.

		Intérêt du couplage i et chronometre :
		si trop lent pour suivre, i joue son rôle de
		plafond de ralentissement expliqué précédemment.

		si, par hasard, la simulation va bien plus vite,
		alors on lui laisse l'opportunité d'effectuer quelques
		calculs en plus pour rattraper davantage.

		*/
		while ((deltaTime > 0) && ((i < 25) ||
			(duration_cast<duration<double>>(
				high_resolution_clock::now() - currentTime).count()
				< tick))) {

			/*
			Calculs successifs par tick pour garder une continuité
			dans la progression physique.
			*/
			if (deltaTime > tick) {

				engine.calculate(&particlePopulation.front(), tick, bounds);

				deltaTime -= tick;
				i++;

			}
			/*
			Consommation du reste si le compteur i le permet.

			M.Fiedler proposait une interpolation explicite entre l'état
			t et l'état t+tick. Or en schématisant, on ne voyait pas
			vraiment de différence avec une simple intégration de
			l'état t à l'état t+deltaTime. A approfondir, peut-être.
			*/
			else {

				engine.calculate(&particlePopulation.front(), deltaTime, bounds);
				deltaTime = 0;

			}

		}

		while (

			duration_cast<duration<double>>(high_resolution_clock::now() - currentTime).count()
			< tick) {

			//Simple sleep improvisé pour ne pas aller trop vite par rapport à la réalité.
		}


		//Mise à jour graphique.
				// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();

		glm::mat4 model = glm::mat4(1.0f);

		//Changement de coordonnées par vecteurs.
		model = glm::translate(model, glm::vec3(1.0f*(particlePopulation.front().position->getX()-50)/100,
			1.0f* (particlePopulation.front().position->getY()-50)/100,
			1.0f* (particlePopulation.front().position->getZ()-50)/100));

		int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		// Assigns a value to the uniform; NOTE: Must always be done after activating the Shader Program
		glUniform1f(uniID, 0.5f);
		// Bind the VAO so OpenGL knows to use it
		VAO1.Bind();
		// Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();

	}

	//Détruit Fireball.
	//delete& fireB;
	// Delete all the objects we've created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
}