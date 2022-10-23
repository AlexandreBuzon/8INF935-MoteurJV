/*
Environnement de jeu

Définit les particules existantes et les coordonnées limites.
*/


#include "PhysicsEngine.h"

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



using namespace std::chrono;




#pragma once
class Environment
{
public:

	Vecteur3D bounds;//Limites d'environnement.
	double tick;//Le pas de mesure entre deux instants.

	PhysicsEngine engine;

	//Constructeur
	Environment(double tck, PhysicsEngine e, double x_b, double y_b, double z_b);
	//Destructeur
	~Environment();

	//Méthode principale
	void play();

};

