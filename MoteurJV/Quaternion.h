#pragma once

#include "Vecteur3D.h"

class Quaternion
{
	private:



public :

	double value[4];

	//Constructeur
	Quaternion();
	
	Quaternion(double w,double i, double j, double k);

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

	double* getValue();

	void display();
		

};

