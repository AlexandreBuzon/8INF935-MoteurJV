#include "Environment.h"

Environment::Environment(double tck, PhysicsEngine e, double x_b, double y_b, double z_b)
{
	tick = tck;
	engine = e;
	bounds = Vecteur3D(x_b,y_b,z_b);
}

Environment::~Environment(){}

void Environment::play()
{
	/*
	  Initialisation graphique.
	
	  Reprise du programme de Victor Gordan, avec modifications adapt�es.
	*/

	GLfloat vertices[] =
	{ // sur une ligne : x, y, z, R, V, B
		-0.1f, -0.1f, 0.0f, 1.0f, 0.0f, 0.0f,
		-0.1f, 0.1f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.1f, -0.1f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.1f, 0.1f, 0.0f, 1.0f, 0.0f, 0.0f,
	};

	// Indices pour l'ordre des vertices
	GLuint indices[] =
	{
		0,1,2,
		3,1,2
	};


	// Initialisation GLFW
	glfwInit();

	// Dit � GLFW quelle version de OpenGL nous utilisons
	// Dans notre cas on utilise OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// Dit � GLFW que nous utilisons le CORE profile
	// Donc nous n'avons besoin que des fonctions modernes
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Cr�e un objet GLFWwindow de 1000 par 1000 pixels
	GLFWwindow* window = glfwCreateWindow(1000, 1000, "MoteurJV OpenGL", NULL, NULL);


	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}
	// Met la fen�tre dans le context courant
	glfwMakeContextCurrent(window);

	//Charge GLAD pour configurer OpenGL
	gladLoadGL();

	// Specifie le viewport de OpenGL dans la fen�tre que nous avons cr�er
	// Dans notre cas le viewport vas de x = 0, y = 0, jusqu'� x = 800, y = 800
	glViewport(0, 0, 800, 800);



	// G�n�re les objets Shader en utilisant le code dans defualt.vert et default.frag
	Shader shaderProgram("default.vert", "default.frag");

	// G�n�re un tableau d'objets Vertex et les assembles
	VAO VAO1;
	VAO1.Bind();

	// G�n�re un buffer d'objets Vertex et les lie aux vertices
	VBO VBO1(vertices, sizeof(vertices));
	// G�n�re un buffer d'objet Element et les lie aux indices
	EBO EBO1(indices, sizeof(indices));

	// lie les attributs VBO comme des coordoner et des couleurs � VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	// d�lie tous pour �viter un accident en les modifiants
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	// r�cupp�re l'ID uniforme appel� "scale"
	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	//Initialisation du temps.
	high_resolution_clock::time_point currentTime = high_resolution_clock::now();

	/*
	Mesure de d�calage entre deux it�rations.
	Pour l'instant, rien.
	*/
	double deltaTime = 0;

	while (!glfwWindowShouldClose(window)) {


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


		// Si trop en retard (100 secondes ici), pas la peine d'essayer. On r�initialise.
		if (deltaTime > 100) {

			deltaTime = 0;

		}

		newTime = currentTime;
		engine.p_particlePopulation->front()->position.display();

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

		si, par hasard, la simulation va bien plus vite,
		alors on lui laisse l'opportunit� d'effectuer quelques
		calculs en plus pour rattraper davantage.

		*/
		while ((deltaTime > 0) && ((i < 25) ||
			(duration_cast<duration<double>>(
				high_resolution_clock::now() - currentTime).count()
				< tick))) {

			/*
			Calculs successifs par tick pour garder une continuit�
			dans la progression physique.
			*/
			if (deltaTime > tick) {

				engine.nextPosition(engine.p_particlePopulation->front(), tick, bounds);

				deltaTime -= tick;
				i++;

			}
			/*
			Consommation du reste si le compteur i le permet.

			M.Fiedler proposait une interpolation explicite entre l'�tat
			t et l'�tat t+tick. Or en sch�matisant, on ne voyait pas
			vraiment de diff�rence avec une simple int�gration de
			l'�tat t � l'�tat t+deltaTime. A approfondir, peut-�tre.
			*/
			else {

				engine.nextPosition(engine.p_particlePopulation->front(), deltaTime, bounds);
				deltaTime = 0;

			}

		}

		while (
			duration_cast<duration<double>>(high_resolution_clock::now() - currentTime).count()
			< tick) {

			//Simple sleep improvis� pour ne pas aller trop vite par rapport � la r�alit�.
		}


		//Mise � jour graphique.
				// Specifie la couleur du background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// efface le buffer noir et asigne la nouvelle couleur
		glClear(GL_COLOR_BUFFER_BIT);
		// Donne � OpenGL quelle Shader Program nous voulons utiliser
		shaderProgram.Activate();

		glm::mat4 model = glm::mat4(1.0f);

		//Changement de coordonn�es par vecteurs.
		model = glm::translate(model, glm::vec3(1.0f*(engine.p_particlePopulation->front()->position.getX()-50)/1000,
			1.0f* (engine.p_particlePopulation->front()->position.getY()-50)/1000,
			1.0f* (engine.p_particlePopulation->front()->position.getZ()-50)/1000));

		int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		// Assigne une valeur � l'uniform; NOTE: Doit toujours �tre fait apr�s avoir activer le Shader Program
		glUniform1f(uniID, 0.5f);
		// Assemble le VAO pour que OpenGL puisse l'utiliser
		VAO1.Bind();
		// Dessine des primitives, nombre d'indices, datatype des indices, index des indices
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		// �change les 2 buffer (avant et arri�re) afin qu'il s'alterne
		glfwSwapBuffers(window);
		// V�rifie tous les �v�nement GLFW
		glfwPollEvents();

	}

	//D�truit Fireball.
	//delete& fireB;
	//D�truit tous les objets que nous avons cr��s
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();
	// D�truit la fen�tre avant de fermer le programe
	glfwDestroyWindow(window);
	// Termine les actions de GLFW avant la fin du programe
	glfwTerminate();
}