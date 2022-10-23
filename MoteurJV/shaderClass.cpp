#include"shaderClass.h"

// Pour lire les defaults.
std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

// Constructeur de programme shader.
Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	// Lecture des defaults
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	/*
	Conversion en tableau de caractère format C pour une manipulation plus simple.
	OpenGL semble plus familier avec les structures C que la std C++.
	*/
	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	// Création d'un shader avec un pointeur.
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// On attache une "source".
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	// Le shader doit être interprété en direct par la machine, donc immediatement compilé.
	glCompileShader(vertexShader);
	// Simple flag pour la compilation.
	compileErrors(vertexShader, "VERTEX");

	// De même pour le fragment shader.
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);
	compileErrors(fragmentShader, "FRAGMENT");

	// Le programme de shaders, avec un pointeur.
	ID = glCreateProgram();
	// Les shaders sont mis en commun dans le programme par ces trois commandes.
	glAttachShader(ID, vertexShader);//Addition dans le shader.
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);//Fusion du tout, pratiquement.
	compileErrors(ID, "PROGRAM");

	// Nettoyage mémoire
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}

// Activation du programme
void Shader::Activate()
{
	glUseProgram(ID);
}

// Destructeur
void Shader::Delete()
{
	glDeleteProgram(ID);
}

// Pour vérifier la compilation
void Shader::compileErrors(unsigned int shader, const char* type)
{
	// Référence le status de compilation.
	GLint hasCompiled;
	// Pour imprimer le message d'erreur.
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_LINKING_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
}