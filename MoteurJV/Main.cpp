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

//Code source de shaders élémentaires pour représenter des points.
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"uniform mat4 transform;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";

int main()
{	
	PhysicsEngine physicsE = PhysicsEngine(10.0);
	std::vector<Particle> ListePart = std::vector<Particle>{};
	Environment envi = Environment(1.0/60.0, physicsE, 1000,1000,1000,ListePart);
	envi.play();

	//Cause une exception delete_scalar 
	//delete& envi;

	return 0;
}