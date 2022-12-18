#include "TreeNode.h"

void TreeNode::_delete() {


	//On déclare les noeuds avec des new lors de la construction de l'arbre.
	if (nodeType == NODE) {

		if (left != 0) {

			left->_delete();
			delete left;
			left = 0;
		}
	

		if (right != 0)
			right->_delete();
			delete right;
			right = 0;

	}

}

TreeNode::~TreeNode() {

	_delete();

}

TreeNode::TreeNode() {

	nodeType = LEAF;

	left = 0;
	right = 0;

}