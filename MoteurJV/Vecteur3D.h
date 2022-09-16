/*
* Auteur : Caudron Beno�t
* Date de modification : 16/09/2022
*/

class Vecteur3D
{
	//Propri�t�s de la classe 
	private:
		double x, y, z;
	
	//Listes des M�thodes de la classe Vecteur 3D
	public:
		void setX(double x);
		double getX();
		void setY(double y);
		double getY();
		void setZ(double z);
		double getZ();
		void afficher();

	//M�thode de calcul
		Vecteur3D somme(Vecteur3D B);
		Vecteur3D scalaire(double b);
		double produitScalaire(Vecteur3D B);
		Vecteur3D produirVectoriel(Vecteur3D B);
};

