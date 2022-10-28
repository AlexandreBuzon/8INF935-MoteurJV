#pragma once
#include "Vecteur3D.h"
//#include "Quaternion.h"
class Matrix33 
{
private :
	float values[9];

public:
	Matrix33(float indice1, float indice2, float indice3, float indice4, float indice5, float indice6, float indice7, float indice8, float indice9);
	Matrix33 operator*(const Matrix33& other) const;
	
	Vecteur3D operator*(const Vecteur3D& vector) const;

	Matrix33 Inverse();

	Matrix33 Transpose();

	//void setOrientation(const Quaternion& q);
};