#include "Environment.h"

Environment::Environment(float tck, PhysicsEngine e, Vecteur3D b)
{
	tick = tck;
	engine = e;
	bounds = b;
	time = 0;
}

Environment::~Environment()
{
	//Nettoyage de la m?moire allou?e.
	delete &bounds;
	delete &engine;
}

void Environment::play()
{
	//A Faire: multithreading.
}
