#include "Environment.h"

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

// camera
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

//Temps
double deltaTime;

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

	/*
		GLfloat vertices[] =
	{ // sur une ligne : x, y, z, R, V, B
		-0.05f, -0.05f, 0.0f, 1.0f, 0.0f, 0.0f,
		-0.05f, 0.05f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.05f, -0.05f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.05f, 0.05f, 0.0f, 1.0f, 0.0f, 0.0f,
	}
	*/
;
	
	// Indices pour l'ordre des vertices
	/*/GLuint indices[] =
	{
		0,1,2,
		3,1,2
	};*/


	std::vector<GLfloat> vertices = engine.p_bodyPopulation
	->at(0)->GLvertices;

	std::vector<GLuint> indices = engine.p_bodyPopulation
	->at(0)->triangles;

	GLuint objectBufferId;

	/*glGenBuffers(1, &objectBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, objectBufferId);
	glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(GLfloat), &vertices.front(), GL_STATIC_DRAW);*/
	

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

	//Fonction des inputs
	glfwSetKeyCallback(window, keyCallback);

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}
	// Met la fen�tre dans le context courant
	glfwMakeContextCurrent(window);

	//Charge GLAD pour configurer OpenGL
	gladLoadGL();

	// Specifie le viewport de OpenGL dans la fen�tre que nous avons cr�e.
	// Dans notre cas le viewport vas de x = 0, y = 0, jusqu'� x = 1000, y = 1000
	glViewport(0, 0,1000, 1000);



	// G�n�re les objets Shader en utilisant le code dans defualt.vert et default.frag
	Shader shaderProgram("default.vert", "default.frag");

	// G�n�re un tableau d'objets Vertex et les assembles
	VAO VAO1;
	VAO1.Bind();

	// G�n�re un buffer d'objets Vertex et les lie aux vertices
	VBO VBO1(&vertices.front(), vertices.size() * sizeof(GLfloat));
	// G�n�re un buffer d'objet Element et les lie aux indices
	EBO EBO1(&indices.front(), indices.size() * sizeof(GLuint));

	// lie les attributs VBO comme des coordonn�es et des couleurs � VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	// d�lie tous pour �viter un accident en les modifiants
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	// r�cup�re l'ID uniforme appel� "scale"
	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	//Initialisation du temps.
	high_resolution_clock::time_point currentTime = high_resolution_clock::now();

	/*
	Mesure de d�calage entre deux it�rations.
	Pour l'instant, rien.
	*/
	 deltaTime = 0;

	 glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window)) {

		//Boucle physique.
		engine.physicsLoop(&currentTime, &deltaTime, tick, bounds);


		//Mise � jour graphique.
				// Specifie la couleur du background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// efface le buffer noir et asigne la nouvelle couleur
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Donne � OpenGL quelle Shader Program nous voulons utiliser
		shaderProgram.Activate();

		// Assigne une valeur � l'uniform; NOTE: Doit toujours �tre fait apr�s avoir activ� le Shader Program
		glUniform1f(uniID, 0.5f);

		// Assemble le VAO pour que OpenGL puisse l'utiliser
		VAO1.Bind();
		
		glm::mat4 model = glm::mat4(1.0f);

		//Camera
		glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		
		//Changement de coordonn�es par vecteurs.
		for (size_t j = 0; j < engine.p_bodyPopulation->size(); j++)
		{
			

			double x = engine.p_bodyPopulation->at(j)->position.getX();
			double y = engine.p_bodyPopulation->at(j)->position.getY();
			double z = engine.p_bodyPopulation->at(j)->position.getZ();
			/*double initialx = engine.p_particlePopulation->at(j)->initialX;
			double initialy = engine.p_particlePopulation->at(j)->initialY;
			double initialz = engine.p_particlePopulation->at(j)->initialZ;*/
			

			//std::cout << "X :" << (x - initialx) / 1000 << " Y : " << (y - initialy) / 1000 << "Z : " << (z - initialz) / 1000 << std::endl;

			

			glm::vec3 translateVector = glm::vec3((x) / bounds.x, (y) / bounds.y , (z) / bounds.z);

			model = glm::translate(model, translateVector);

			double qw = engine.p_bodyPopulation->at(j)->orientation.value[0];
			double qx = engine.p_bodyPopulation->at(j)->orientation.value[1];
			double qy = engine.p_bodyPopulation->at(j)->orientation.value[2];
			double qz = engine.p_bodyPopulation->at(j)->orientation.value[3];

			model = model * glm::toMat4(glm::quat(qw,qx,qy,qz));

			int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");

			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

			// Dessine des primitives, nombre d'indices, datatype des indices, index des indices
			glDrawElements(GL_TRIANGLES, indices.size() * sizeof(GLuint)/sizeof(int), GL_UNSIGNED_INT, 0);
			
			
			
		}
		// �change les 2 buffer (avant et arri�re) afin qu'il s'alterne
			glfwSwapBuffers(window);
			// V�rifie tous les �v�nement GLFW
			glfwPollEvents();
	}
	

	//Nettoyage.
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();

	// D�truit la fen�tre avant de fermer le programme
	glfwDestroyWindow(window);
	// Termine les actions de GLFW avant la fin du programe
	glfwTerminate();
}

//Callback de la fonction keyInput permetat de g�rer les input au clavier
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods){
	std::cout << key << std::endl;

	if (key == GLFW_KEY_SPACE) {
		std::cout << "espace" << std::endl;
		glfwSetWindowShouldClose(window, true);

	}

	if (key == GLFW_KEY_LEFT) {
	}
	if (key == GLFW_KEY_RIGHT) {
	}
	if (key == GLFW_KEY_DOWN) {
	}
	if (key == GLFW_KEY_UP) {
	}
	//Camera
	float cameraSpeed = static_cast<float>(2.5 * deltaTime);
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

}