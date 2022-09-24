/*
* Auteur : Caudron Beno�t
* Date de cr�ation : 16/09/2022
*/

class Vecteur3D
{
	//Propri�t�s de la classe 
	private:
		double x, y, z;
	
	//Listes des M�thodes de la classe Vecteur 3D
	public:

		//Constructeurs
		Vecteur3D();
		Vecteur3D(double x, double y, double z);

		void setX(double x);
		double getX();
		void setY(double y);
		double getY();
		void setZ(double z);
		double getZ();
		void display();

		
		

	//M�thode de calcul
	
		//Somme.
		Vecteur3D operator +(const Vecteur3D& B);

		//Multiplication par scalaire.
		Vecteur3D operator *(const double &b) const;

		//Produit scalaire pas saturation de l'op�rateur *.
		double operator *(Vecteur3D &B);

		//Produit vectoriel. D�fini en sens direct (r�gle de la main droite).
		Vecteur3D operator ^(Vecteur3D &B);

		//Norme euclidienne.
		double norm();

		//Produit vectoriel. D�fini en sens direct.
		Vecteur3D normalize();
};

