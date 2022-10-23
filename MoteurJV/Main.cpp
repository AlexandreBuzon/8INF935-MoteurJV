#include"imgui.h"
#include"imgui_impl_glfw.h"
#include"imgui_impl_opengl3.h"

#include "LinearFieldGenerator.h"
#include "Particle.h"
#include "Fireball.h"
#include "BallSansFrottements.h"
#include "BallForces.h"
#include "Environment.h"
#include "FluidDrag.h"
#include "ParticleSpring.h"
#include "StaticSpring.h"


#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

int main()
{	
	Vecteur3D anchor = Vecteur3D(150, 450, 150);
	Ball fireA = Ball(450, 400, 450, 0, 0, 0);
	Ball fireB = Ball(0, 50, 0, 0, 0, 0);
	BallForces fireD = BallForces(40, 10, 40, 0, 0, 0, "ParticuleSpring");
	BallSansFrottements fireC = BallSansFrottements(200, 50, 200, 0, 0, 0);
	
	std::vector<Particle*> ListePart = std::vector<Particle*>{&fireB};

	std::map<std::string, std::unique_ptr<ParticleForceGenerator>> listeLF;

	listeLF.insert(std::make_pair("gravity", new LinearFieldGenerator(Vecteur3D(0,-10,0))));
	listeLF.insert(std::make_pair("Fluid", new FluidDrag(10.0f,10.0f)));
	listeLF.insert(std::make_pair("ParticuleSpring", new ParticleSpring(&fireB, 10.0f, 10.0f)));
	//listeLF.insert(std::make_pair("ParticuleSpringA", new ParticleSpring(&fireB, 10.0f, 10.0f)));
	listeLF.insert(std::make_pair("StaticSpring", new StaticSpring(anchor, 10.0f, 10.0f)));
	
	ListePart.push_back(&fireC);
	ListePart.push_back(&fireA);
	ListePart.push_back(&fireD);

	Environment *envi = new Environment(1.0/60.0, PhysicsEngine(10.0,&ListePart,&listeLF), 1000,1000,1000);
	envi->play();

	return 0;
}