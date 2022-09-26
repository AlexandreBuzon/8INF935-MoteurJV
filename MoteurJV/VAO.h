#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include<glad/glad.h>
#include"VBO.h"

class VAO
{
public:
	// ID pointeur
	GLuint ID;
	// Constructeur
	VAO();

	// Reliure des propri�t�s de la VAO � une Vertice Buffer Object pour repr�sentation.
	void LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
	// Connexion au contexte.
	void Bind();
	// D�connexion.
	void Unbind();
	// Destructeur.
	void Delete();
};

#endif