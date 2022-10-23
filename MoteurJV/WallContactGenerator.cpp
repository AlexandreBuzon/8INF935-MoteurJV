#include "WallContactGenerator.h"

WallContactGenerator::WallContactGenerator() {

	restitution = 0;

	polygonPoints = {};

	normal = Vecteur3D();

	mainPoint = Vecteur3D();

}

WallContactGenerator::WallContactGenerator(double restitution,
	std::vector<Vecteur3D> polygonPoints,
	Vecteur3D normal, Vecteur3D mainPoint) {

	this->restitution = restitution;

	this->polygonPoints = polygonPoints;

	this->normal = normal;

	this->mainPoint = mainPoint;

}

WallContactGenerator::~WallContactGenerator(){}


void WallContactGenerator::solve(Particle* p_P) {

	//Replace Particule à une position respectant la contrainte.
	p_P->position = mainPoint + normal * p_P->rayonCollision;

	Vecteur3D projectedVelocity = normal * (p_P->velocity * normal);

	//Le mur absorbe la composante selon restitution.
	p_P->velocity = p_P->velocity - projectedVelocity * (2 - restitution);

}

bool WallContactGenerator::checkOnWall(Particle* p_P) {

	//Avec aussi peu de points, le mur est infini.
	if (polygonPoints.size() < 2) return true;


	Vecteur3D comparateur = polygonPoints.at(1) - polygonPoints.at(0);
	Vecteur3D relativePos = p_P->position - polygonPoints.at(0);

	double D = (relativePos^comparateur) * normal;

	double D_2 = 0;

	for (size_t i = 1; i < polygonPoints.size()-1; i++) {

		comparateur = polygonPoints.at(i+1) - polygonPoints.at(i);
		relativePos = relativePos = p_P->position - polygonPoints.at(i);

		D_2 = (relativePos ^ comparateur) * normal;

		/*
		Etant donné l'ordre de parcours des points, tous les 
		produits scalaires calculés sont de même signe
		si la projection de la particule est sur le polygone.
		*/
		if (D_2 / D < 0) return false;

	}

	comparateur = polygonPoints.at(0) - polygonPoints.at(polygonPoints.size() - 1);
	relativePos = relativePos = p_P->position - polygonPoints.at(polygonPoints.size() - 1);

	D_2 = (relativePos ^ comparateur) * normal;

	if (D_2 / D < 0) return false;

	return true;

}

bool WallContactGenerator::checkConflict(Particle* p_P) {

	Vecteur3D diff = mainPoint - p_P->position;

	double distance = diff * normal;

	return checkOnWall(p_P) && (distance > -p_P->rayonCollision) && (distance < p_P->rayonCollision);

}