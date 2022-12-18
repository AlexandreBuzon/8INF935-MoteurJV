#include "ContactGenerator.h"

ContactGenerator::ContactGenerator() {}
ContactGenerator::~ContactGenerator(){}

Contact ContactGenerator::generateData(const Primitive& S1, const Primitive& S2) {

	std::cout << "pas la bonne surcharge\n";

	return { Vecteur3D(), Vecteur3D(), -1 };
}

Contact ContactGenerator::generateData(const Sphere& S1, const Sphere& S2) {


	double radiusSum = S1.radius + S2.radius;

	//Calcul des vecteurs positions en coordonnées globales.
	Vecteur3D PS1 = S1.body->transformMatrix * (S1.offset * Vecteur3D(0, 0, 0));
	Vecteur3D PS2 = S2.body->transformMatrix * (S2.offset * Vecteur3D(0, 0, 0));

	double distance = (PS1 - PS2).norm();

	if (radiusSum >= distance) {

		Vecteur3D u = (PS1 - PS2).normalize();

		return { u, //Normale d'interpénétration.
			PS1 + u * S1.radius, //Point de contact.
			radiusSum - distance };//Interpénétration.

	}

	return { Vecteur3D(), Vecteur3D(), -1 };

}

Contact ContactGenerator::generateData(const Sphere& S, const Plane& P) {

	Vecteur3D positionGlobale = S.body->transformMatrix * (S.offset * Vecteur3D(0, 0, 0));

	Vecteur3D planVersSphere = positionGlobale - P.Pdecalage;

	if (planVersSphere* P.normal <= S.radius){

		double distance = planVersSphere * P.normal;//Peut être négative. Le signe va d'ailleurs servir.

		return { P.normal,//Normale d'interpénétration.
			positionGlobale + P.normal * (-distance),//Point de contact.
			 S.radius - distance };//Interpénétration.

	}

	return { Vecteur3D(), Vecteur3D(), -1 };

}
Contact ContactGenerator::generateData(const Plane& P, const Sphere& S) {

	Vecteur3D positionGlobale = S.body->transformMatrix * (S.offset * Vecteur3D(0, 0, 0));

	Vecteur3D planVersSphere = positionGlobale - P.Pdecalage;

	if (planVersSphere * P.normal <= S.radius) {

		double distance = planVersSphere * P.normal;//Peut être négative. Le signe va d'ailleurs servir.

		return { P.normal,//Normale d'interpénétration.
			positionGlobale + P.normal * (-distance),//Point de contact.
			 S.radius - distance };//Interpénétration.

	}

	return { Vecteur3D(), Vecteur3D(), -1 };
}

Contact ContactGenerator::generateData(Vecteur3D& boxVertice, const Plane& P) {

	Vecteur3D planeToPoint = boxVertice - P.Pdecalage;
	double distance = planeToPoint * P.normal;

	if(planeToPoint * P.normal <= 0)
		return { P.normal,//Normale d'interpénétration.
			boxVertice + P.normal * (-distance),//Point de contact.
			 -distance };//Interpénétration.

	return { Vecteur3D(), Vecteur3D(), -1 };
}
Contact ContactGenerator::generateData(const Plane& P, Vecteur3D& boxVertice) {

	Vecteur3D planeToPoint = boxVertice - P.Pdecalage;
	double distance = planeToPoint * P.normal;

	if (planeToPoint * P.normal <= 0)
		return { P.normal,//Normale d'interpénétration.
			boxVertice + P.normal * (-distance),//Point de contact.
			 -distance };//Interpénétration.

	return { Vecteur3D(), Vecteur3D(), -1 };
}

Contact ContactGenerator::generateData(const Sphere& S, Box& B) {

	//Centre de sphère depuis base de la boîte.
	Vecteur3D SFromB = 
	B.offset.Inverse() * B.body->transformMatrix.Inverse()*
		S.body->transformMatrix* S.offset* Vecteur3D(0, 0, 0);

	//Projection du centre sur la boîte.
	Vecteur3D projOnBox = SFromB;

	//Processus de projection.
	if (projOnBox.x < -B.halfsize.x) projOnBox.x = -B.halfsize.x;
	if (projOnBox.x > B.halfsize.x) projOnBox.x = B.halfsize.x;

	if (projOnBox.y < -B.halfsize.y) projOnBox.y = -B.halfsize.y;
	if (projOnBox.y > B.halfsize.y) projOnBox.y = B.halfsize.y;

	if (projOnBox.z < -B.halfsize.z) projOnBox.z = -B.halfsize.z;
	if (projOnBox.z > B.halfsize.z) projOnBox.z = B.halfsize.z;

	if ((SFromB - projOnBox).norm() < S.radius)
		return { (SFromB - projOnBox).normalize(),//Normale d'interpénétration.
			projOnBox,//Point de contact.
			 (SFromB - projOnBox).norm() };//Interpénétration.

	return { Vecteur3D(), Vecteur3D(), -1 };

}
Contact ContactGenerator::generateData(Box& B, const Sphere& S) {

	//Centre de sphère depuis base de la boîte.
	Vecteur3D SFromB =
		B.offset.Inverse() * B.body->transformMatrix.Inverse() *
		S.body->transformMatrix * S.offset * Vecteur3D(0, 0, 0);

	//Projection du centre sur la boîte.
	Vecteur3D projOnBox = SFromB;

	//Processus de projection.
	if (projOnBox.x < -B.halfsize.x) projOnBox.x = -B.halfsize.x;
	if (projOnBox.x > B.halfsize.x) projOnBox.x = B.halfsize.x;

	if (projOnBox.y < -B.halfsize.y) projOnBox.y = -B.halfsize.y;
	if (projOnBox.y > B.halfsize.y) projOnBox.y = B.halfsize.y;

	if (projOnBox.z < -B.halfsize.z) projOnBox.z = -B.halfsize.z;
	if (projOnBox.z > B.halfsize.z) projOnBox.z = B.halfsize.z;

	if ((SFromB - projOnBox).norm() < S.radius)
		return { (SFromB - projOnBox).normalize(),//Normale d'interpénétration.
			projOnBox,//Point de contact.
			 (SFromB - projOnBox).norm() };//Interpénétration.

	return { Vecteur3D(), Vecteur3D(), -1 };

}

void ContactGenerator::narrowPhase(RigidBody& B1, RigidBody& B2) {

	for (Primitive P1 : B1.primitiveList) {

		for (Primitive P2 : B2.primitiveList) {

			resolveContact(B1, B2, generateData(P1, P2));

		}

	}

}