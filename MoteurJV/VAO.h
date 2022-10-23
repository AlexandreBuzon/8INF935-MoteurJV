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

	// Reliure des propriétés de la VAO à une Vertice Buffer Object pour représentation.
	void LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
	// Connexion au contexte.
	void Bind();
	// Déconnexion.
	void Unbind();
	// Destructeur.
	void Delete();
};

#endif