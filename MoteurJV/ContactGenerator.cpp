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

void ContactGenerator::resolveContact(RigidBody& B1,
	RigidBody& B2,
	Contact data) {

	if (data.penetration == -1)return;

	std::cout << "CONTACT\n"
		<< "Normale : ";
	data.normal.display();
	std::cout << "Point de contact : ";
	data.pointContact.display();
	std::cout << "Interpenetration : " << data.penetration << std::endl;

	Matrix33 M_t = orthonormalBasis(data.normal).Transpose();

	Vecteur3D qRel1 = data.pointContact - B1.position;
	Vecteur3D u1 = qRel1 ^ data.normal;
	Vecteur3D theta1 = B1.inverseInertia * u1;
	Vecteur3D q_p1 = theta1 ^ qRel1;

	Vecteur3D qRel2 = data.pointContact - B2.position;
	Vecteur3D u2 = (qRel2 ^ data.normal) * -1;
	Vecteur3D theta2 = B2.inverseInertia * u2;
	Vecteur3D q_p2 = theta2 ^ qRel2;

	Vecteur3D velocity = q_p1 + B1.velocity + q_p2 + B2.velocity;

	velocity = M_t * velocity;

	double desiredVelocity = -2 * velocity.x;

	Vecteur3D impulse = M_t * Vecteur3D(desiredVelocity, 0, 0);

	B1.velocity = B1.velocity + (impulse * B1.inverseMass);
	B1.angularV = B1.angularV + B1.inverseInertia * (qRel1 ^ impulse);

	B2.velocity = B2.velocity - (impulse * B2.inverseMass);
	B2.angularV = B2.angularV - B2.inverseInertia * (qRel2 ^ impulse);

	//Résolution de l'interpénétration.
	double inverseInertia = 1 / (B1.inverseMass + B2.inverseMass);

	Vecteur3D penetration = data.normal * data.penetration;

	Vecteur3D linearMove1 = penetration * (B1.inverseMass * inverseInertia);
	Vecteur3D linearMove2 = penetration * -(B2.inverseMass * inverseInertia);

	B1.position = B1.position + linearMove1;
	B2.position = B2.position + linearMove2;

}