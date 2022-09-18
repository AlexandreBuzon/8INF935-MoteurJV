#include"imgui.h"
#include"imgui_impl_glfw.h"
#include"imgui_impl_opengl3.h"
#include "Vecteur3D.h"
#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

int main() {

	Vecteur3D A(1, 2, 3);
	Vecteur3D B(4, 5, 6);
	Vecteur3D C=A.somme(A);

	A.afficher();

	return 0;
	
	//C'est dans le tuto pour que ca marche faut pas y toucher pour l'instant 
	GLFWwindow* window;
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window,true);
	ImGui_ImplOpenGL3_Init("#version 330");
	
}