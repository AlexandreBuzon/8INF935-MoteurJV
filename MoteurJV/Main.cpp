#include"imgui.h"
#include"imgui_impl_glfw.h"
#include"imgui_impl_opengl3.h"

#include "LinearFieldGenerator.h"
#include "FluidDrag.h"
#include "ParticleSpring.h"
#include "StaticSpring.h"
#include "Particle.h"
#include "Fireball.h"
#include "Environment.h"

#include<iostream>
#include<stdlib.h>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

int main()
{

	srand(time(NULL));
	float largeur = 1500;
	float longueur = 1500;

	bool menu = true;
	bool menu2 = true;

	float nbPart;
	int choix;
	while (menu) {
		menu = true;
		menu2 = true;
		std::cout <<"Générateur de force et contraintes" << std::endl;
		std::cout << "Combien de particule souhaitez vous afficher ? (entre 1 et 10)  " << std::endl;



		std::cin >> nbPart;

		if (nbPart > 10 || nbPart < 0 || std::cin.fail()) {
			menu = false;
			menu2 = false;
			
		}
		std::cin.clear(); // effacer les bits d'erreurs 
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // supprimer la ligne erronée dans le buffer
		if (menu) {
			std::string force[3] = {"gravity","ressort","fluid"};
			Vecteur3D anchor = Vecteur3D(0, 300, 0);
			std::map<std::string, std::unique_ptr<ParticleForceGenerator>> listeLF;
			std::cout << "Quelle force ?" << std::endl;
			std::cout << "1 : Gravite " << std::endl;
			std::cout << "2 : Ressort " << std::endl;
			std::cout << "3 : Fluide " << std::endl;
			std::cout << "4 : Quitter" << std::endl;
			while (menu2)
			{
				std::cin >> choix;
				switch (choix)
				{
				case 1:
					//A faire
					listeLF.insert(std::make_pair("gravity", new LinearFieldGenerator(Vecteur3D(0, -10, 0))));
					menu2 = false;
					break;
				case 2:
					//A faire
					listeLF.insert(std::make_pair("ressort", new StaticSpring(anchor,10.0f,10.0f)));
					menu2 = false;
					break;
				case 3:
					//A faire
					listeLF.insert(std::make_pair("fluid", new FluidDrag(10.0f,10.0f)));
					listeLF.insert(std::make_pair("gravity", new LinearFieldGenerator(Vecteur3D(0, -10, 0))));
					menu2 = false;
					break;
				case 4:
					return 0;
				default:
					std::cout << "Choix Incorrect" << std::endl;
					break;
				}
			}



			Ball fireB = Ball(-300, 0, 0, 0, 0, 0, force[choix-1]);
			std::vector<Particle*> ListePart = std::vector<Particle*>{ &fireB };



			for (float i = 1; i < nbPart; i++)
			{
				Ball fireB = Ball(rand()%500-250, rand() % 500 - 250, 0, 0, 0, 0, force[choix - 1]);
				ListePart.push_back(&fireB);
				std::cout << i << std::endl;
			}

			//ListePart.push_back(&fireC);

			std::map<std::string, std::unique_ptr<ParticleConstraintGenerator>> listeC;

			Environment* envi = new Environment(1.0 / 60.0, PhysicsEngine(&ListePart, &listeLF, &listeC), 1000, 1000, 1000);

			std::cout << "Pour quitter le programme appuyer sur 'SPACE'  " << std::endl;
			envi->play();
			listeC.clear();

			delete envi;
		}

		menu = true;
	}



	return 0;
}