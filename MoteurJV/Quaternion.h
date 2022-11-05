#pragma once
#include "Vecteur3D.h"

class Quaternion
{
	private:



public :

	float value[4];

	//Constructeur
	Quaternion();
	
	Quaternion(float w,float i, float j, float k);

	//Destructeur
	~Quaternion();


	//Méthodes 
public :
	

	void Normalise();

	Quaternion operator +(const Quaternion other);

	Quaternion operator *(const Quaternion& other);

	Quaternion operator*(const double& a);

	Quaternion InverseQuaternion();

	void RotateByVector(const Vecteur3D& vector);

	Quaternion UpdateByAngularVelocity(const Vecteur3D& rotation, double duration);

	float* getValue();
		

};

