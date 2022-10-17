#include"imgui.h"
#include"imgui_impl_glfw.h"
#include"imgui_impl_opengl3.h"
#include "Vecteur3D.h"
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

	Fireball fireB = Fireball(50, 50, 50, 25, 2, 10);
	Fireball fireC = Fireball(350, 350, 350, 25, 2, 10);
	
	std::vector<Particle*> ListePart = std::vector<Particle*>{&fireB};

	
	ListePart.push_back(&fireC);

	Environment *envi = new Environment(1.0/60.0, PhysicsEngine(10.0,&ListePart), 1000,1000,1000);
	envi->play();

	return 0;
}