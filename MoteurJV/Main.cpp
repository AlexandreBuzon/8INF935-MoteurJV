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

	Ball fireB = Ball(50, 50, 50, 0, 0, 0);
	Ball fireC = Ball(350, 350, 350, 0, 0, 0);
	
	std::vector<Particle*> ListePart = std::vector<Particle*>{&fireB};

	std::map<std::string, std::unique_ptr<ParticleForceGenerator>> listeLF;

	listeLF.insert(std::make_pair("gravity", new LinearFieldGenerator(Vecteur3D(0,-10,0))));
	
	ListePart.push_back(&fireC);

	Environment *envi = new Environment(1.0/60.0, PhysicsEngine(10.0,&ListePart,&listeLF), 1000,1000,1000);
	envi->play();

	return 0;
}