#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include<glad/glad.h>

class VBO
{
public:
	// ID pointeur (généralement l'intérêt des GLuint).
	GLuint ID;
	// Constructeur de VBO. Fonctionne par reliure à un tableau de point.
	VBO(GLfloat* vertices, GLsizeiptr size);

	// Connexion au contexte.
	void Bind();
	// Déconnexion du contexte
	void Unbind();
	// Destructeur
	void Delete();
};

#endif