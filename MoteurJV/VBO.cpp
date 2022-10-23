#include"VBO.h"

// Constructeur de VBO. Fonctionne par reliure à un tableau de point.
VBO::VBO(GLfloat* vertices, GLsizeiptr size)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

// Connexion au contexte.
void VBO::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

// Déconnexion du contexte
void VBO::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// Destructeur
void VBO::Delete()
{
	glDeleteBuffers(1, &ID);
}