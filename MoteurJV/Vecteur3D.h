/*
* Auteur : Caudron Benoît
* Date de création : 16/09/2022
*/

class Vecteur3D
{
	//Propriétés de la classe 
	private:
		double x, y, z;
	
	//Listes des Méthodes de la classe Vecteur 3D
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

		
		

	//Méthode de calcul
	
		//Somme.
		Vecteur3D operator +(const Vecteur3D& B);

		//Multiplication par scalaire.
		Vecteur3D operator *(const double &b) const;

		//Produit scalaire pas saturation de l'opérateur *.
		double operator *(Vecteur3D &B);

		//Produit vectoriel. Défini en sens direct (règle de la main droite).
		Vecteur3D operator ^(Vecteur3D &B);

		//Norme euclidienne.
		double norm();

		//Produit vectoriel. Défini en sens direct.
		Vecteur3D normalize();
};

