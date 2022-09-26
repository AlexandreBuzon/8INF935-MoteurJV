#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include<glad/glad.h>

class VBO
{
public:
	// ID pointeur (g�n�ralement l'int�r�t des GLuint).
	GLuint ID;
	// Constructeur de VBO. Fonctionne par reliure � un tableau de point.
	VBO(GLfloat* vertices, GLsizeiptr size);

	// Connexion au contexte.
	void Bind();
	// D�connexion du contexte
	void Unbind();
	// Destructeur
	void Delete();
};

#endif