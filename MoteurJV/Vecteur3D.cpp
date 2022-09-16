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

void Vecteur3D::afficher() {
	cout << "X : " << this->x << "Y : " << this->y << "Z : " << this->z << endl;
}

Vecteur3D Vecteur3D::somme(Vecteur3D B) {
	Vecteur3D C;
	double x, y, z;
	x=this->getX() + B.getX();
	y = this->getY() + B.getY();
	z = this->getZ() + B.getZ();
	C.setX(x);
	C.setY(y);
	C.setZ(z);
	return C;
}

