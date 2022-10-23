#include"VAO.h"

// Constructeur
VAO::VAO()
{
	glGenVertexArrays(1, &ID);
}

// Reliure des propriétés de la VAO à une Vertice Buffer Object pour représentation.
void VAO::LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
{
	VBO.Bind();
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	VBO.Unbind();
}

// Connexion au contexte.
void VAO::Bind()
{
	glBindVertexArray(ID);
}

// Déconnexion.
void VAO::Unbind()
{
	glBindVertexArray(0);
}

// Destructeur.
void VAO::Delete()
{
	glDeleteVertexArrays(1, &ID);
}