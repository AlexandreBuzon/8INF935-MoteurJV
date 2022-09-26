#version 330 core

//Positions/Coordonnées
layout (location = 0) in vec3 aPos;
// Couleurs
layout (location = 1) in vec3 aColor;


// Sortie des couleurs pour le Fragment Shader
out vec3 color;
// Controle le scale des vertices
uniform float scale;


uniform mat4 model;

void main()
{
	// Sortie des positions/coordonnées de tous les vertices
	gl_Position = model * vec4(aPos, 1.0);
	// Assigne les couleurs depuis le Vertex Data au "color"
	color = aColor;
}