//Matrice 3x3

#pragma once
#include "Vecteur3D.h"
#include "Quaternion.h"

#include <stdexcept>
#include <exception>
#include <iostream>

class Matrix33 
{
private :

	double values[9];

public:

	Matrix33();

	Matrix33(double indice1, double indice2, double indice3,
			 double indice4, double indice5, double indice6,
			 double indice7, double indice8, double indice9);
	
	Matrix33 operator*(const Matrix33& other) const;
	
	Vecteur3D operator*(const Vecteur3D& vector) const;

	Matrix33 Inverse();

	Matrix33 Transpose();

	//Représentation matricielle d'un quaternion.
	void setOrientation(const Quaternion& q);

	void display();

};