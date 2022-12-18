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

	void _delete();

public:

	~TreeNode();

};

