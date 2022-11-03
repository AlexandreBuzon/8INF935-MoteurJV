#pragma once
#include "Vecteur3D.h"

class Quaternion
{

	//Var
private:


	//Constructeur
	Quaternion();
	
	Quaternion(float w,float i, float j, float k);

	//Destructeur
	~Quaternion();


	//Méthodes 
public :
	float value[4];

	void Normalise();

	Quaternion operator*(const Quaternion& other);

	void RotateByVector(const Vecteur3D& vector);

	void UpdateByAngularVelocity(const Vecteur3D& rotation, float duration);

	float* getValue();
		

};

