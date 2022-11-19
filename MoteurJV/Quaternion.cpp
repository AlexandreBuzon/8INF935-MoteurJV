#include "Quaternion.h"
#include<iostream>

using namespace std;

double* Quaternion::getValue() {
	return this->value;
}

Quaternion::Quaternion() {
	this->value[0] = 1;
	this->value[1] = 0;
	this->value[2] = 0;
	this->value[3] = 0;
}

Quaternion::Quaternion(double w_,double i_,double j_,double k_) {
	this->value[0] = w_;
	this->value[1] = i_;
	this->value[2] = j_;
	this->value[3] = k_;
}

Quaternion::~Quaternion() {};



void Quaternion::Normalise() {

	double a = this->value[0];
	double b = this->value[1];
	double c = this->value[2];
	double d = this->value[3];
	double norme= sqrt(a*a+b*b+c*c+d*d);

	if(norme == 0)
		std::throw_with_nested(std::invalid_argument("Erreur : Normalisation de vecteur nul.\n"));

	this->value[0] = a/norme;
	this->value[1] = b/norme;
	this->value[2] = c/norme;
	this->value[3] = d/norme;
	 
}

Quaternion Quaternion::operator +(const Quaternion other) {

	double w1 = this->value[0];
	double x1 = this->value[1];
	double y1 = this->value[2];
	double z1 = this->value[3];

	double w2 = other.value[0];
	double x2 = other.value[1];
	double y2 = other.value[2];
	double z2 = other.value[3];

	return Quaternion(w1+w2,x1+x2,y1+y2,z1+z2);

}

Quaternion Quaternion::operator *(const Quaternion& other) {
	double w1 = this->value[0];
	double x1 = this->value[1];
	double y1 = this->value[2];
	double z1 = this->value[3];

	double w2 = other.value[0];
	double x2 = other.value[1];
	double y2 = other.value[2];
	double z2 = other.value[3];

	return Quaternion(w1*w2-x1*x2-y1*y2-z1*z2,
		w1 * x2 + x1 * w2 + y1 * z2 - z1 * y2,
		w1 * y2 + y1 * w2 + z1 * x2 - x1 * z2,
		w1 * z2 + z1 * w2 + x1 * y2 - y1 * x2);
}

Quaternion Quaternion::operator *(const double& a) {

	double w = a*this->value[0];
	double x = a*this->value[1];
	double y = a*this->value[2];
	double z = a*this->value[3];

	return Quaternion(w,x,y,z);
}

Quaternion Quaternion::InverseQuaternion() {
	Quaternion inverse = Quaternion(this->value[0], -this->value[1], -this->value[2], -this->value[3]);
	inverse.Normalise();
	return inverse;
}

void Quaternion::RotateByVector(const Vecteur3D& vector) {

	Quaternion q = Quaternion(0, vector.x, vector.y, vector.z);
	Quaternion p_inv = this->InverseQuaternion();
	
	*this * q * p_inv;
	return;
}

Quaternion Quaternion::UpdateByAngularVelocity(const Vecteur3D& rotation, double duration) {

	Quaternion omega = Quaternion(0,rotation.x,
									rotation.y,
									rotation.z);

	return (*this) + (*this * omega) * (duration / 2);

}

void Quaternion::display() {

	for (int i = 0; i < 4; i++)std::cout << value[i] << " ";

	std::cout << std::endl;

}