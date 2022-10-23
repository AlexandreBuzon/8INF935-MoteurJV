#include"imgui.h"
#include"imgui_impl_glfw.h"
#include"imgui_impl_opengl3.h"

#include "LinearFieldGenerator.h"
#include "Particle.h"
#include "Fireball.h"
#include "Environment.h"

#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

int main()
{	
	int x_depart = -2000;
	bool menu = true;
	int nbPart;
	while (menu) {
		std::cout << "Combien de particule souhaitez vous afficher ? (entre 1 et 10)  " << std::endl;
		std::cin >> nbPart;
		if (nbPart < 10 && nbPart>0) {
			menu = false;
		}



		Ball fireB = Ball(0, 0, 0, 0, 0, 0);
		std::vector<Particle*> ListePart = std::vector<Particle*>{ &fireB };

		for (int i = 1; i < nbPart; i++)
		{
			Ball fireB = Ball((double)(50 * i), 0, 0, 0, 0, 0);
			ListePart.push_back(&fireB);
		}




		std::map<std::string, std::unique_ptr<ParticleForceGenerator>> listeLF;

		listeLF.insert(std::make_pair("gravity", new LinearFieldGenerator(Vecteur3D(0, -10, 0))));

		//ListePart.push_back(&fireC);

		Environment* envi = new Environment(1.0 / 60.0, PhysicsEngine(&ListePart, &listeLF), 1000, 1000, 1000);

		std::cout << "Pour quitter le programme appuyer sur 'SPACE'  " << std::endl;
		envi->play();
		menu = true;
	}
	return 0;
}