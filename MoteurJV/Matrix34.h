#pragma once
#include "Vecteur3D.h"
#include "Quaternion.h"
class Matrix34
{
private:
	float values[12];

public:
	Matrix34(float indice1, float indice2, float indice3, float indice4, float indice5, float indice6, float indice7, float indice8, float indice9, float indice10, float indice11, float indice12);
	Matrix34 operator*(const Matrix34& other) const;

	Vecteur3D operator*(const Vecteur3D& vector) const;

	Matrix34 Inverse();

	void setOrientationAndPosition(const Quaternion& q, const Vecteur3D& p);

	Vecteur3D TransformPosition(const Vecteur3D& vector);

	Vecteur3D TransformDirection(const Vecteur3D& vector);
};