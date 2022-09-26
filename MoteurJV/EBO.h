#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include<glad/glad.h>

class EBO
{
public:
	// ID pointeur (g�n�ralement l'int�r�t des GLuint).
	GLuint ID;
	// Constructeur
	EBO(GLuint* indices, GLsizeiptr size);

	// Connexion au contexte pour son utilisation.
	void Bind();
	// D�connexion au contexte
	void Unbind();
	// Destructeur
	void Delete();
};

#endif