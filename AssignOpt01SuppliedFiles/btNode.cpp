#include "btNode.h"
#include <iostream>
#include <cmath>
using namespace std;

// returns number of nodes in the tree
int tree_size(btNode* avl_root) {
	if (avl_root == 0)
		return 0;
	return 1 + tree_size(avl_root->left) + tree_size(avl_root->right);
}

// returns height of the tree
int height(btNode* root) {
	if (root == 0) // base case
		return -1;
	int heightLST = height(root->left), heightRST = height(root->right);
	return (heightLST > heightRST) ? 1 + heightLST : 1 + heightRST;
}

// return true if AVL tree, otherwise false
bool isAVL(btNode* root) {
	if (root == 0)
		return true;
	int heightLST, heightRST;
	if (root->right != 0 || root->left != 0) {
		heightLST = height(root->left);
		heightRST = height(root->right);
		if (abs(heightLST - heightRST) > 1 || abs(heightRST - heightLST) > 1)
			return false;
	}
	return isAVL(root->left) && isAVL(root->right);
}

// a non-fancy way to display binary tree
void tree_print(btNode* root, int level) {
	tree_print_aux(root, root, level);
}

// recursive helper function called by tree_print
void tree_print_aux(btNode* root, btNode* ptr, int level) {
	if (ptr != 0) {
		tree_print_aux(root, ptr->right, level + 1);
		cout << '\n';
		if (ptr == root)
			cout << "ROOT-=< ";
		for (int i = 0; i < level && ptr != root; ++i)
			cout << "        ";
		cout << ptr->data;
		tree_print_aux(root, ptr->left, level + 1);
	}
}

// releases dynamically allocated node memory use by
// the tree to heap and set the tree to empty tree
void tree_clear(btNode*& root) {
	if (root == 0)
		return;
	tree_clear(root->left);
	tree_clear(root->right);
	delete root;
	root = 0;
}

//////////////////////////////////////////////////////////////////////

// wrapper function that initiates recursive process of avl_insert_aux
// (return value from the initiating call not captured/used)
void avl_insert(btNode*& avl_root, int insInt) {
	avl_insert_aux(avl_root, insInt);
}

// adds item (with data insInt) to tree rooted at avl_root
// tree is unchanged if a matching item already exists
// return value is the change in depth in the tree
// (for use by ancestor nodes to correct balance factors)
int avl_insert_aux(btNode*& avl_root, int insInt) {

	int initialDepth = height(avl_root);

	if (avl_root == nullptr) {
		avl_root = new btNode;
		avl_root->data = insInt;
		avl_root->left = nullptr;
		avl_root->right = nullptr;
		initialDepth = 1;
	} else if (insInt < avl_root->data) {
		avl_insert(avl_root->left, insInt);
		rebalanceL(avl_root->left);
		initialDepth = height(avl_root->left);
	} else if (insInt > avl_root->data) {
		avl_insert(avl_root->right, insInt);
		rebalanceR(avl_root->right);
		initialDepth = height(avl_root->right);
	}

	return initialDepth;
}

// rebalances an out-of-balance node with taller LST
// does single or double rotation depending on left child's bf
void rebalanceL(btNode*& avl_root) {

	int height_LST = height(avl_root->left);
	int height_RST = height(avl_root->right);
	avl_root->bf = height_RST - height_LST;

	if ((avl_root == nullptr) && (avl_root->bf == 0)) {
		return;
	}

	if (avl_root->bf > 1) {
		if (avl_root->left->bf > 0) {
			rotateL(avl_root);
			rotateL(avl_root);
		} else {
			rotateL(avl_root);
			rotateR(avl_root);
		}
	}
}

// rebalances an out-of-balance node with taller RST
// does single or double rotation depending on right child's bf
void rebalanceR(btNode*& avl_root) {

	int height_LST = height(avl_root->left);
	int height_RST = height(avl_root->right);
	avl_root->bf = height_RST - height_LST;

	if ((avl_root == nullptr) && (avl_root->bf == 0)) {
		return;
	}

	if (avl_root->bf < -1) {
		if (avl_root->right->bf > 0) {
			rotateR(avl_root);
			rotateL(avl_root);
		} else {
			rotateR(avl_root);
			rotateR(avl_root);
		}
	}
}

// does single left rotation of the tree
// does NOT update bf's (which must be done @ higher level of algorithm)
void rotateL(btNode*& avl_root) {

	while (avl_root) {
		btNode *temp;
		temp = avl_root->left;
		avl_root->left = temp->right;
		temp->right = avl_root;
	}
}

// does single right rotation of the tree
// does NOT update bf's (which must be done @ higher level of algorithm)
void rotateR(btNode*& avl_root) {
	while (avl_root) {
		btNode *temp;
		temp = avl_root->right;
		avl_root->left = temp->left;
		temp->left = avl_root;
	}
}

