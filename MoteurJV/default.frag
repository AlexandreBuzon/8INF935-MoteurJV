#version 330 core

// Sortie des couleurs en RGBA
out vec4 FragColor;


// Entrée des couleur depuis les Vertex Shader
in vec3 color;


void main()
{
	FragColor = vec4(color, 1.0f);
}