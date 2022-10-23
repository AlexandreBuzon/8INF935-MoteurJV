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


		engine.physicsLoop(&currentTime, &deltaTime, tick, bounds);


		//Mise � jour graphique.
				// Specifie la couleur du background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// efface le buffer noir et asigne la nouvelle couleur
		glClear(GL_COLOR_BUFFER_BIT);
		// Donne � OpenGL quelle Shader Program nous voulons utiliser
		shaderProgram.Activate();
		// Assigne une valeur � l'uniform; NOTE: Doit toujours �tre fait apr�s avoir activer le Shader Program
		glUniform1f(uniID, 0.5f);
		// Assemble le VAO pour que OpenGL puisse l'utiliser
		VAO1.Bind();
		
		glm::mat4 model = glm::mat4(1.0f);

		//Changement de coordonn�es par vecteurs.
		for (size_t j = 0; j < engine.p_particlePopulation->size(); j++)
		{//1
			

			float x = engine.p_particlePopulation->at(j)->position.getX();
			float y = engine.p_particlePopulation->at(j)->position.getY();
			float z = engine.p_particlePopulation->at(j)->position.getZ();

			glm::vec3 translateVector = glm::vec3((x-50)/1000, (y-50)/1000, (z-50)/1000);

			model = glm::translate(model, translateVector);


			int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");

			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

			// Dessine des primitives, nombre d'indices, datatype des indices, index des indices
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			
			
			
		}
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