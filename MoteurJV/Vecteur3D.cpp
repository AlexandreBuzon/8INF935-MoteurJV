/*
* Auteur : Caudron Benoît
* Date de modification : 16/09/2022
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

Vecteur3D::Vecteur3D(double x=0, double y=0, double z=0) {
	this->setX(x);
	this->setY(y);
	this->setZ(z);
}
void Vecteur3D::afficher() {
	cout << "X : " << this->getX() << "Y : " << this->getY() << "Z : " << this->getZ() << endl;
}

Vecteur3D Vecteur3D::somme(Vecteur3D B) {
	Vecteur3D C;
	double x, y, z;
	x = this->getX() + B.getX();
	y = this->getY() + B.getY();
	z = this->getZ() + B.getZ();
	C.setX(x);
	C.setY(y);
	C.setZ(z);
	return C;
}

Vecteur3D Vecteur3D::scalaire(double b) {
	Vecteur3D C;
	double x, y, z;
	x = this->getX() * b;
	y = this->getY() * b;
	z = this->getZ() * b;
	C.setX(x);
	C.setY(y);
	C.setZ(z);
	return C;
}

double Vecteur3D::produitScalaire(Vecteur3D B) {
	double result;
	result = this->getX() * B.getX() + this->getY() * B.getY() + this->getZ() * B.getZ();
	return result;
}

Vecteur3D Vecteur3D::produitVectoriel(Vecteur3D B) {
	Vecteur3D C;
	double x, y, z;
	x = this->getY() * B.getZ() - this->getZ() * B.getY();
	y = this->getZ() * B.getX() - this->getX() * B.getZ();
	z = this->getX() * B.getY() - this->getY() * B.getX();
	C.setX(x);
	C.setY(y);
	C.setZ(z);
	return C;
}

double Vecteur3D::calculNorme() {
	double result,x,y,z;
	x = this->getX();
	y = this->getY();
	z = this->getZ();
	result = sqrt(x * x + y * y + z * z);
	return result;
}

Vecteur3D Vecteur3D::normalisation() {
	double norme = this->calculNorme();
	setX(this->getX() / norme);
	setY(this->getY() / norme);
	setZ(this->getZ() / norme);
}