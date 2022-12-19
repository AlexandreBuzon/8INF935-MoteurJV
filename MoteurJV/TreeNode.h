/*
Noeud de BVH.
*/

#include "RigidBody.h"

#pragma once

enum knownNodeType {LEAF, NODE};

class TreeNode
{

	friend class PhysicsEngine;

private:

	TreeNode* left;
	TreeNode* right;
	knownNodeType nodeType;

	std::vector<RigidBody*> VolumeElements;

	//Volume englobant.
	Vecteur3D BVposition;
	double BVradius;

	TreeNode();
	TreeNode(const TreeNode& tree);

	void _delete();

	//Construction d'un volume englobant sphérique.
	void buildBV(std::vector<RigidBody*> elements){

		if (elements.empty()) {
			return;
		}

		BVposition = elements.at(0)->position;

		BVradius = elements.at(0)->broadRadius;

		for (size_t i = 1; i < elements.size(); i++) {

			//Reprise partielle du travail d'Ericson.


			RigidBody* &p_rb = elements.at(i);

			Vecteur3D d = p_rb->position - BVposition;
			double dist = d.norm();

			//Lorsqu'inclusion de sphères, garder la plus grande.
			if (dist + BVradius <= p_rb->broadRadius) {//Cas où sphère de p_rb englobe.

				BVposition = p_rb->position;
				BVradius = p_rb->broadRadius;

			}
			else if (dist + p_rb->broadRadius <= BVradius) continue;//BV englobe déjà.

			//Cas sans inclusion.
			else {

				BVradius = (dist + BVradius + p_rb->broadRadius) / 2;

				//On s'épargne cet ajustement si les centres sont très proches.
				if (dist > 0.001)
					BVposition = BVposition + d * ((BVradius - p_rb->broadRadius) / dist);
			}

		}



	};

public:

	~TreeNode();

};

