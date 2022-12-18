/*
Gère les collisions.

Originellement les données étaient générées par les primitives,
mais cela amène à des problèmes d'inclusion à cause de la surcharge
des méthodes.
*/

#pragma once

#include "RigidBody.h"
#include "Plane.h"

//DBL_MAX.
#include<float.h>

struct Contact {

	//Coordonnées globales
	Vecteur3D normal;
	Vecteur3D pointContact;

	double penetration;

};

class ContactGenerator
{

public:

	ContactGenerator();
	~ContactGenerator();

	Contact generateData(const Primitive& P1, const Primitive& P2);

	//Sphère-Sphère.
	Contact generateData(const Sphere& S1, const Sphere& S2);

	//Sphère-Plan.
	Contact generateData(const Sphere& S, const Plane& P);
	Contact generateData(const Plane& P, const Sphere& S);

	//Boîte-Plan.
	Contact generateData(Vecteur3D& boxVertice, const Plane& P);
	Contact generateData(const Plane& P, Vecteur3D& boxVertice);

	//Boîte-Sphère.
	Contact generateData(const Sphere& S, Box& B);
	Contact generateData(Box& B, const Sphere& S);

	//Boîte-Boîte. (Separating Axis Test, Millington)

	//Fonction intermédiaire pour un axe.
	double penetrationOnAxis(Box& B1, Box& B2,
		Vecteur3D& axis, Vecteur3D& toCenter) {

		//Projections des boîtes sur l'axe.
		double proj1 = 2 * (B1.halfsize * axis);
		double proj2 = 2 * (B2.halfsize * axis);

		double distance = abs(toCenter * axis);

		return proj1 + proj2 - distance;

	};

	//On a deux points de contact sur un cas Edge-Edge. On en veut qu'un.
	Vecteur3D getContactPoint(
		Vecteur3D& axis1, Vecteur3D& axis2,
		Vecteur3D& ptOnEdge1, Vecteur3D ptOnEdge2) {
	
		Vecteur3D p1p2 = ptOnEdge2 - ptOnEdge1;

		//Juste une mesure de chaque point sur leur arête.
		double proj1 = ptOnEdge1 * axis1;
		double proj2 = ptOnEdge2 * axis2;


		double n1 = ptOnEdge1.norm();
		double n2 = ptOnEdge2.norm();

		double dotProdAxes = axis1 * axis2;

		//"Distance" totale.
		double d = n1 + n2 - dotProdAxes * dotProdAxes;

		//Mesure pour déterminer le point le plus proche.
		double m1 = (dotProdAxes * proj2 - n2 * proj1) / d;
		double m2 = (n1 * proj2 - n2 * dotProdAxes ) / d;

		return (ptOnEdge1 + axis1 * (m1 / 2)) + (ptOnEdge2 + axis2 * (m2 / 2));
	
	};

	//Méthode finale.
	Contact generateData(Box& B1, Box& B2) {

		Vecteur3D axes[15];


		//Les différents axes.
		axes[0] = B1.body->transformMatrix * (B1.offset * Vecteur3D(B1.halfsize.x, 0, 0));
		axes[1] = B1.body->transformMatrix * (B1.offset * Vecteur3D(0, B1.halfsize.y, 0));
		axes[2] = B1.body->transformMatrix * (B1.offset * Vecteur3D(0, 0, B1.halfsize.z));

		axes[3] = B2.body->transformMatrix * (B2.offset * Vecteur3D(B2.halfsize.x, 0, 0));
		axes[4] = B2.body->transformMatrix * (B2.offset * Vecteur3D(0, B1.halfsize.y, 0));
		axes[5] = B2.body->transformMatrix * (B2.offset * Vecteur3D(0, 0, B1.halfsize.z));

		axes[6] = axes[0] ^ axes[3];
		axes[7] = axes[0] ^ axes[4];
		axes[8] = axes[0] ^ axes[5];
		axes[9] = axes[1] ^ axes[3];
		axes[10] = axes[1] ^ axes[4];
		axes[11] = axes[1] ^ axes[5];
		axes[12] = axes[2] ^ axes[3];
		axes[13] = axes[2] ^ axes[4];
		axes[14] = axes[2] ^ axes[5];


		//Meilleur axe de projection.
		double bestOverlap = DBL_MAX;
		unsigned int bestCase = 0;

		Vecteur3D toCenter = B2.body->transformMatrix * (B2.offset * Vecteur3D(0, 0, 0))
			- B1.body->transformMatrix * (B1.offset * Vecteur3D(0, 0, 0));

		for (unsigned int i = 0; i < 15; i++) {

			//Filtre les arêtes quasi-parallèles.
			if (axes[i].norm() < 0.001)continue;

			axes[i] = axes[i].normalize();

			double overlap = penetrationOnAxis(B1, B2, axes[i], toCenter);

			if (overlap < 0) return {};

			if (overlap < bestOverlap) {

				bestOverlap = overlap;
				bestCase = i;

			}

			Vecteur3D& axis = axes[bestCase];

			if (bestCase < 3) {
				//Face de B2 et Point de B1.

				//Deux faces possibles pour un axe.
				if (toCenter * axis < 0) axis = axis * -1;

				Vecteur3D vertex = B2.halfsize;

				if (axes[3] * axis < 0)vertex.x *= -1;
				if (axes[4] * axis < 0)vertex.y *= -1;
				if (axes[5] * axis < 0)vertex.z *= -1;

				vertex = B1.body->transformMatrix * (B1.offset * vertex);

				return { axis, vertex, bestOverlap };

			}
			else if (bestCase < 6) {
				//Face de B1 et Point de B2.

				Vecteur3D vertex = B1.halfsize;

				if (axes[0] * axis < 0)vertex.x *= -1;
				if (axes[1] * axis < 0)vertex.y *= -1;
				if (axes[2] * axis < 0)vertex.z *= -1;

				vertex = B2.body->transformMatrix * (B2.offset * vertex);

				return { axis, vertex, bestOverlap };

			}
			else {
				//Edge-Edge.

				Vecteur3D ptOnEdge1 = B1.halfsize;
				Vecteur3D ptOnEdge2 = B2.halfsize;

				//Construction ptOnEdge1
				for (unsigned int i = 0; i < 3; i++) {

					//astuce arithmétique pour associer axes et indices du tableau.
					//bestCase = (indiceAxe1 + 2)*3 + (indiceAxe2-3)
					if (i == int(bestCase / 3) - 2) {
					
						switch (i) {

						case 0:
							ptOnEdge1.x = 0;
							break;
						case 1:
							ptOnEdge1.y = 0;
							break;
						case 2:
							ptOnEdge1.z = 0;
							break;

						default:
							break;

						}
					
					}
					else if (axes[1] * axis > 0) {

						switch (i) {

						case 0:
							ptOnEdge1.x *= -1;
							break;
						case 1:
							ptOnEdge1.y *= -1;
							break;
						case 2:
							ptOnEdge1.z *= -1;
							break;

						default:
							break;

						}

					}

				}

				//Construction PtOnEdge2
				for (unsigned int i = 3; i < 6; i++) {

					//astuce arithmétique pour associer axes et indices du tableau.
					//bestCase = (indiceAxe1 + 2)*3 + (indiceAxe2-3)
					if (i == bestCase % 3 + 3) {

						switch (i) {

						case 3:
							ptOnEdge1.x = 0;
							break;
						case 4:
							ptOnEdge1.y = 0;
							break;
						case 5:
							ptOnEdge1.z = 0;
							break;

						default:
							break;

						}

					}
					else if (axes[1] * axis > 0) {

						switch (i) {

						case 3:
							ptOnEdge1.x *= -1;
							break;
						case 4:
							ptOnEdge1.y *= -1;
							break;
						case 5:
							ptOnEdge1.z *= -1;
							break;

						default:
							break;

						}

					}

				}

				//Conversion coordonnées globales.
				ptOnEdge1 = B1.body->transformMatrix * (B1.offset * ptOnEdge1);
				ptOnEdge2 = B2.body->transformMatrix * (B2.offset * ptOnEdge2);

				return {axis,
						getContactPoint(axes[int(bestCase / 3) - 2],
							axes[bestCase % 3 + 3],
							ptOnEdge1, ptOnEdge2),
						bestOverlap};

			}

		}

	}

	//Base orthonormale exprimée en coordonnées globales.
	Matrix33 orthonormalBasis(Vecteur3D normal) {

		if (normal.norm() == 0) {

			std::cout << "Erreur : normale nulle.\n";

			return Matrix33();

		}

		Vecteur3D b, c;

		if (normal.y == 0 && normal.z == 0) {

			b = Vecteur3D(0, 1, 0);
			c = (normal ^ b).normalize();

		}
		else {

			b = Vecteur3D(1, 0, 0);

			c = (normal ^ b).normalize();

			b = (c ^ normal).normalize();
		
		}

		return Matrix33(normal.x, b.x, c.x,
						normal.y, b.y, c.y,
						normal.z, b.z, c.z);

	};

	//Résolution de contact.
	void resolveContact(RigidBody& B1,
		RigidBody& B2,
		Contact data) {

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
	
	};

	//Méthode générale comparant les primitives de deux corps rigides.
	void narrowPhase(RigidBody& B1, RigidBody& B2);

};

