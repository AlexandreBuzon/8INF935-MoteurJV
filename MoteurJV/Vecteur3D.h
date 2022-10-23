/*
* Auteur : Caudron Beno�t
* Date de cr�ation : 16/09/2022
*/

#pragma once
class Vecteur3D
{
	private:
		double x, y, z;
	
	public:

		Vecteur3D();
		Vecteur3D(double x, double y, double z);

		void setX(double x);
		double getX();
		void setY(double y);
		double getY();
		void setZ(double z);
		double getZ();
		void display();
		float magnitude();
		
		

	//M�thode de calcul
	
		//Somme.
		Vecteur3D operator +(const Vecteur3D& B);

		//Soustraction.
		Vecteur3D operator -(const Vecteur3D& B);

		//Soustraction.
		void operator -=(const Vecteur3D& B);

		//Multiplication par scalaire.
		Vecteur3D operator *(const double &b) const;

		//Produit scalaire par surcharge de l'op�rateur *.
		double operator *(Vecteur3D &B);

		//Produit vectoriel. D�fini en sens direct (r�gle de la main droite).
		Vecteur3D operator ^(Vecteur3D &B);

		//Norme euclidienne.
		double norm();

		//Vecteur unitaire de direction �gale � celle de l'objet.
		Vecteur3D normalize();
};

