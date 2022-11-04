#include "Quaternion.h"
#include<iostream>

//Dource https://lucidar.me/fr/quaternions/quaternion-product/

using namespace std;

float* Quaternion::getValue() {
	return this->value;
}

Quaternion::Quaternion() {
	this->value[0] = 0;
	this->value[1] = 0;
	this->value[2] = 0;
	this->value[3] = 0;
}

Quaternion::Quaternion(float w_,float i_,float j_,float k_) {
	this->value[0] = w_;
	this->value[1] = i_;
	this->value[2] = j_;
	this->value[3] = k_;
}



void Quaternion::Normalise() {

	double a = this->value[0];
	double b = this->value[1];
	double c = this->value[2];
	double d = this->value[3];
	double norme= sqrt(a*a+b*b+c*c+d*d);

	this->value[0] = a/norme;
	this->value[1] = b/norme;
	this->value[2] = c/norme;
	this->value[3] = d/norme;
	 
}

Quaternion Quaternion::operator*(const Quaternion& other) {
	double a = this->value[0];
	double b = this->value[1];
	double c = this->value[2];
	double d = this->value[3];

	double e = other.value[0];
	double f = other.value[1];
	double g = other.value[2];
	double h = other.value[3];


	//GLHF C PTETRE FAUX
	return Quaternion(a*e-b*f-c*g-d*h,a*f+b*e+c*h-d*g,a*g-b*h+c*e+d*f,a*h+b*g+c*f+d*e);
}

Quaternion* Quaternion::InverseQuaternion() {
	Quaternion inverse = Quaternion(this->value[0], -this->value[1], -this->value[2], -this->value[3]);
	inverse.Normalise();
	return &inverse;
}

void Quaternion::RotateByVector(const Vecteur3D& vector) {
	Quaternion q = Quaternion(0, vector.x, vector.y, vector.z);
	Quaternion p_inv = *this->InverseQuaternion();
	
	*this * q * p_inv;
	return;
}

void UpdateByAngularVelocity(const Vecteur3D& rotation, float duration) {

}
