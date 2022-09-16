/*
* Auteur : Caudron Benoît
* Date de modification : 16/09/2022
*/

class Vecteur3D
{
	//Propriétés de la classe 
	private:
		double x, y, z;
	
	//Listes des Méthodes de la classe Vecteur 3D
	public:
		void setX(double x);
		double getX();
		void setY(double y);
		double getY();
		void setZ(double z);
		double getZ();
		void afficher();

	//Méthode de calcul
		Vecteur3D somme(Vecteur3D B);
		Vecteur3D scalaire(double b);
		double produitScalaire(Vecteur3D B);
		Vecteur3D produirVectoriel(Vecteur3D B);
};

