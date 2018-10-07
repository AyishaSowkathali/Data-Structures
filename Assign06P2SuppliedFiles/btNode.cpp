#include "btNode.h"

void dumpToArrayInOrder(btNode* bst_root, int* dumpArray) {
	if (bst_root == 0)
		return;
	int dumpIndex = 0;
	dumpToArrayInOrderAux(bst_root, dumpArray, dumpIndex);
}

void dumpToArrayInOrderAux(btNode* bst_root, int* dumpArray, int& dumpIndex) {
	if (bst_root == 0)
		return;
	dumpToArrayInOrderAux(bst_root->left, dumpArray, dumpIndex);
	dumpArray[dumpIndex++] = bst_root->data;
	dumpToArrayInOrderAux(bst_root->right, dumpArray, dumpIndex);
}

void tree_clear(btNode*& root) {
	if (root == 0)
		return;
	tree_clear(root->left);
	tree_clear(root->right);
	delete root;
	root = 0;
}

int bst_size(btNode* bst_root) {
	if (bst_root == 0)
		return 0;
	return 1 + bst_size(bst_root->left) + bst_size(bst_root->right);
}

// write definition for bst_insert here
bool bst_insert(btNode*& bst_root, int insInt) {
	if (bst_root == 0) {
		bst_root = new btNode;
		bst_root->data = insInt;
		bst_root->left = 0;
		bst_root->right = 0;
		return true;
	}

	if (bst_root->data == insInt) {
		bst_root->data = insInt; // overwritten data field with insInt
		return false;
	}

	btNode* cur = bst_root;
	bool flag = false;
	while (!flag) {
		if (insInt < cur->data) {
			if (cur->left == 0) {
				cur->left = new btNode;
				cur->left->data = insInt;
				cur->left->left = 0;
				cur->left->right = 0;
				flag = true;
			} else {
				cur = cur->left;
			}
		} else if (insInt > cur->data) {
			if (cur->right == 0) {
				cur->right = new btNode;
				cur->right->data = insInt;
				cur->right->left = 0;
				cur->right->right = 0;
				flag = true;
			} else {
				cur = cur->right;
			}
		} else {
			cur->data = insInt;
			return false;
		}
	}
	return flag;
}

// write definition for bst_remove here 
bool bst_remove(btNode*& bst_root, int remInt) {
	if(bst_root == 0 )
		return false;
	
	if(remInt < bst_root->data) {
		return bst_remove(bst_root->left, remInt);
	} else if(remInt > bst_root->data) {
		return bst_remove(bst_root->right, remInt);
	} else if (remInt == bst_root->data) {
		if(bst_root->left == 0 && bst_root->right == 0) {
			btNode* root = bst_root;
			bst_root = 0;
			delete root;
		} else if (bst_root->left == 0 || bst_root->right == 0) {
			if(bst_root->right == 0) {
				btNode* root = bst_root;
				bst_root = bst_root->left;
				delete root;
			} else {
				btNode* root = bst_root;
				bst_root = bst_root->right;
				delete root;
			}
		} else {
			bst_remove_max(bst_root->left, bst_root->data);
		}
	}
	return true;
}

// write definition for bst_remove_max here
void bst_remove_max(btNode*& bst_root, int& item) {
	if (bst_root->right == 0) {
		item = bst_root->data;
		btNode* root = bst_root;
		bst_root = bst_root->left;
		delete root;
	} else {
		bst_remove_max(bst_root->right, item);
	}
}

