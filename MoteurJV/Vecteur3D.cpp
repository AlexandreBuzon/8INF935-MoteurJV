/*
* Auteur : Caudron Benoît
* Date de création : 16/09/2022
*/

#include "Vecteur3D.h"
#include<iostream>

using namespace std;


void Vecteur3D::setX(double x) {
	this->x = x;
}

double Vecteur3D::getX() {
	return this->x;
}

void Vecteur3D::setY(double y) {
	this->y = y;
}

double Vecteur3D::getY() {
	return this->y;
}

void Vecteur3D::setZ(double z) {
	this->z = z;
}

double Vecteur3D::getZ() {
	return this->z;
}

//Constructeurs
Vecteur3D::Vecteur3D() {

	x = 0;
	y = 0;
	z = 0;

}

Vecteur3D::Vecteur3D(double x, double y, double z) {

	this->setX(x);
	this->setY(y);
	this->setZ(z);

}

//Simple affichage en console.
void Vecteur3D::display() {
	cout << "X : " << this->getX() << " Y : " << this->getY() << " Z : " << this->getZ() << endl;
}

//Somme.
Vecteur3D Vecteur3D::operator +(const Vecteur3D &B) {
	Vecteur3D C;
	
	//Pas besoin d'accesseurs ni de mutateurs quand c'est défini dans la classe.
	C.x = x + B.x;
	C.y = y + B.y;
	C.z = z + B.z;

	return C;
}

//Soustraction.
Vecteur3D Vecteur3D::operator -(const Vecteur3D& B) {
	Vecteur3D C;

	//Pas besoin d'accesseurs ni de mutateurs quand c'est défini dans la classe.
	C.x = x - B.x;
	C.y = y - B.y;
	C.z = z - B.z;

	return C;
}

//Soustraction.
Vecteur3D Vecteur3D::operator -=(const Vecteur3D& B) {

	//Pas besoin d'accesseurs ni de mutateurs quand c'est défini dans la classe.
	x = x - B.x;
	y = y - B.y;
	z = z - B.z;
}

//Multiplication par scalaire.
//Attention, écrire "vecteur point scalaire" pour que ça marche.
Vecteur3D Vecteur3D::operator *(const double& b) const {
	Vecteur3D C;
	
	C.x = b * x;
	C.y = b * y;
	C.z = b * z;

	return C;
}

//Produit scalaire pas saturation de l'opérateur *.
double Vecteur3D::operator *(Vecteur3D &B) {

	double result = x * B.x + y * B.y + z * B.z;

	return result;
}

//Produit vectoriel. Défini en sens direct.
Vecteur3D Vecteur3D::operator ^(Vecteur3D &B) {

	Vecteur3D C;
	C.x = y * B.z - z * B.y;
	C.y = z * B.x - x * B.z;
	C.z = x * B.y - y * B.x;
	return C;
}

//Norme euclidienne.
double Vecteur3D::norm() {
	double result,x,y,z;
	x = this->getX();
	y = this->getY();
	z = this->getZ();
	result = sqrt(x * x + y * y + z * z);
	return result;
}

//Vecteur unitaire de direction égale à celle de l'objet.
Vecteur3D Vecteur3D::normalize() {

	Vecteur3D C;

	double normeInverse= 1/this->norm();

	C = *this * normeInverse;

	return C;
}

float Vecteur3D::magnitude() 
{
	float res = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
	return res;
}