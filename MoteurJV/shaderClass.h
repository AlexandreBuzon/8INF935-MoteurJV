#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include<glad/glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>

std::string get_file_contents(const char* filename);

class Shader
{
public:
	// Pointeur pour y accéder. Les objets OpenGL sont souvent accessibles uniquement par pointeur.
	GLuint ID;
	// Constructeur de programme shader à partir des deux que nous utilisons.
	Shader(const char* vertexFile, const char* fragmentFile);

	// Activation du programme
	void Activate();
	// Destructeur de programme
	void Delete();
private:
	// Vérifie que la compilation a fonctionné.
	void compileErrors(unsigned int shader, const char* type);
};


#endif