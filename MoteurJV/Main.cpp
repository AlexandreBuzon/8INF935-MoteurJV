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

	PhysicsEngine& engine = PhysicsEngine::GetInstance();

	Cube C = Cube(1.2, 1,
		Vecteur3D(100,750,-450),Vecteur3D(-12, 23, 10),
		Vecteur3D(5,-7,1), Quaternion(1,0,0,0));


	std::vector<Particle*> pP = {};
	std::vector<RigidBody*> bP = {&C};

	std::map<std::string,
		std::unique_ptr<ForceGenerator>>
		lForce = {};

	std::map<std::string,
		std::unique_ptr<ConstraintGenerator>>
		lConstraints = {};

	engine.p_bodyPopulation = &bP;
	engine.p_particlePopulation = &pP;
	engine.p_constraints = &lConstraints;
	engine.p_universalForceRegistry = &lForce;


	//A PLACER EN INPUT.
	/*lForce.insert(std::make_pair(
		"g", new LinearFieldGenerator(Vecteur3D(0, -10, 0), false)));
	
	lForce.insert(std::make_pair(
		"p1", new LinearFieldGenerator(Vecteur3D(1.1, 0, 0), true)));

	lForce.insert(std::make_pair(
		"p2", new LinearFieldGenerator(Vecteur3D(0, -1, 0), true)));

	lForce.insert(std::make_pair(
		"p3", new LinearFieldGenerator(Vecteur3D(0, 0, 1.3), true)));

	lForce.insert(std::make_pair(
		"r", new StaticSpring(Vecteur3D(0, 0, 0), 5, 500)));
	*/
	lForce.insert(std::make_pair(
		"t", new FluidDrag(0, 0, 25)));

	Environment E = Environment(1.0 / 60.0,
		engine,
		1000, 1000, 1000);

	E.play();

	return 0;
}