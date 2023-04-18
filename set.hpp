#ifndef _DEFINITION_SET_HPP_
#define _DEFINITION_SET_HPP_

#include "declaration_set.hpp"

#include <iostream>
using namespace stl;

template <typename T>
void  set<T>::insertFix(set<T>::Node*& node)
{
	Node* uncle = nullptr;
	if (node->parent->parent != nullptr) {
		Node* P = node->parent;
		Node* GP = node->parent->parent;
		uncle = DefineUncle(node);
		if (P->color == RED && uncle != nullptr && 
			uncle->color == RED) {
			RedDumpDown(GP);
		} else if (uncle == nullptr) {
			MarginRotate(node);
		} else if (node->color == RED && P->color == RED && 
			uncle->color == BLACK) {
			node->left->parent = node; 
			node->right->parent = node; 
			GlobalRotate(node);
		}	
	}
	root->color = BLACK;
	root->parent = nullptr;
} // Insert fix function end

template <typename T>
void set<T>::MarginRotate(set<T>::Node*& node)
{
	Node* P = node->parent;
	Node* GP = node->parent->parent;
	if (node == P->right && P == GP->left) { 
		UncleNullNodeRightchildParentLeftchild(node);
	} else if (node == P->left && P == GP->left) {
		UncleNullNodeLeftchildParentLeftchild(node);
	} else if (node == P->left && P == GP->right) {
		UncleNullNodeLeftchildParentRightchild(node);
	} else if (node == P->right && P == GP->right) { 
		UncleNullNodeRightchildParentRightchild(node);
	}
}

template <typename T>
void set<T>::GlobalRotate(set<T>::Node*& node)
{
	Node* P = node->parent;
	Node* GP = node->parent->parent;
	if (P->right == node && P == GP->right) {
		UncleBlackNodeREDRightchildParentRedRightchild(node);
	} else if (node == P->left && P == GP->left) {
		UncleBlackNodeREDLeftchildParentRedLeftchild(node);
	} else if (node == P->left && P == GP->right) {
		UncleBlackNodeREDLeftchildParentRedRightchild(node);
	} else if (node == P->right && P == GP->left) {
		UncleBlackNodeREDRightchildParentRedLeftchild(node);
	}
}

template <typename T>
typename set<T>::Node* set<T>::DefineUncle(Node* node)
{		
	set<T>::Node* uncle = nullptr;
	Node* P = node->parent;
	Node* GP = node->parent->parent;
	if (GP->right != nullptr  &&
	    GP->left == P) {
		uncle = GP->right;
	} else if (GP->left != nullptr &&
		   GP->right == P) {
		uncle = GP->left;
	}
	return uncle;
}

template <typename T>
void set<T>::RedDumpDown(set<T>::Node* arg_node)
{
	arg_node->left->color = BLACK;
	arg_node->right->color = BLACK;
	if (arg_node == root) {
		arg_node->color = BLACK;
		return;
	}
	arg_node->color = RED;
	insertFix(arg_node);
}

// case 1 uncle is null node is rightchild parent is leftchild
template <typename T>
void set<T>::UncleNullNodeRightchildParentLeftchild(set<T>::Node* node)
{
	set<T>::Node* gp = node->parent->parent;
	if(gp->parent != nullptr) {
		if (gp == gp->parent->left) {
			gp->parent->left = node;
		} else if (gp == gp->parent->right) {
			gp->parent->right = node;
		}
	}
	Node* node_parent_parent = node->parent->parent;
	Node* node_parent = node->parent;
	Node* gp_parent = gp->parent;
	node->right = node_parent_parent;
	node->left  = node_parent;
	node->parent = gp_parent;
	node->right->parent = node;
	node->left->parent = node;
	if (node_parent_parent == root) {
		root = node;
	}
	root->color = BLACK;
	MakeNull(node->left);
	return;
}

// case 2 uncle is null node is leftchild parent is rightchild
template <typename T>
void set<T>::UncleNullNodeLeftchildParentRightchild(set<T>::Node* node)
{
	Node* gp = node->parent->parent;
	if(gp->parent != nullptr) {
		if (gp == gp->parent->left) {
			gp->parent->left = node;
		} else if (gp == gp->parent->right) {
			gp->parent->right = node;
		}
	}
	Node* node_parent = node->parent;
	Node* node_parent_parent = node->parent->parent;
	Node* gp_parent = gp->parent;
	node->right = node_parent;
	node->left = node_parent_parent;
	node->parent = gp_parent;
	node->left->parent = node;
	node->right->parent = node;
	if (root == node_parent_parent) {
		root = node;
	}
	root->color = BLACK;
	MakeNull(node->right);
	return ;
}

// case :3 uncle is null node is leftchild parent is leftchild
template <typename T>
void set<T>::UncleNullNodeLeftchildParentLeftchild(set<T>::Node* node)
{
	Node* gp = node->parent->parent;
	if(gp->parent != nullptr) {
		if (gp == gp->parent->left) {
			gp->parent->left = node->parent;
		} else if (gp == gp->parent->right) {
			gp->parent->right = node->parent;
		}
	}
	node->parent->right = node->parent->parent;
	node->parent->parent = node->parent->parent->parent;
	node->parent->right->parent = node->parent;
	if (gp == root) {
		root = node->parent;
	}
	root->color = BLACK;
	MakeNull(node);
	return ;
}

// case 4 uncle is null node is rightchild parent is rightchild
template <typename T>
void set<T>::UncleNullNodeRightchildParentRightchild(set<T>::Node* node)
{
	Node* gp = node->parent->parent;
	if(gp->parent != nullptr) {
		if (gp == gp->parent->left) {
			gp->parent->left = node->parent;
		} else if (gp == gp->parent->right) {
			gp->parent->right = node->parent;
		}
	}
	node->parent->parent = gp->parent;
	node->parent->left = gp;
	gp->parent = node->parent;
	if(root == gp) {
		root = node->parent;
	}
	root->color = BLACK;
	MakeNull(node);
	return ;
}

// case 5 uncle is BLACK node is RED and rightchild parent is RED and rightchild  
template <typename T>
void set<T>::UncleBlackNodeREDRightchildParentRedRightchild(set<T>::Node* node)
{
	Node* gp = node->parent->parent;
	if (gp!=root) {
		if (gp == gp->parent->right) {
			gp->parent->right = node->parent;
		} else {
			gp->parent->left = node->parent;
		}
	}
	Node* tmp_node = gp->parent;
	gp->parent = node->parent;
	gp->right = node->parent->left;
	node->parent->left->parent = gp;
	node->parent->left = gp;
	node->parent->parent = tmp_node;
	if (gp == root) {
		root = node->parent;
	}
	ColorFix(node);
	root->color = BLACK;
	return;
}

// case 6 uncle is BLACK node is RED and leftchild parent is RED and leftchild
template <typename T>
void set<T>::UncleBlackNodeREDLeftchildParentRedLeftchild(set<T>::Node* node)
{
	set<T>::Node* gp = node->parent->parent;
	if (gp!=root) {
		if (gp == gp->parent->right) {
			gp->parent->right = node->parent;
		} else {
			gp->parent->left = node->parent;
		}
	}
	set<T>::Node* tmp_node = gp->parent;
	gp->parent = node->parent;
	gp->left = node->parent->right;
	node->parent->right->parent = gp;
	node->parent->right = gp;
	node->parent->parent = tmp_node;
	ColorFix(node);
	if (gp == root) {
		root = node->parent;
	}
	root->color = BLACK;
	return;
}

// case 7 uncle is BLACK node is RED and leftchild parent is RED and rightchild
template <typename T>
void set<T>::UncleBlackNodeREDLeftchildParentRedRightchild(set<T>::Node* node)
{
	Node* gp = node->parent->parent;
	Node *gp_right = gp->right;
	Node *node_parent_left = node->parent->left;
	Node *node_parent_parent = node->parent->parent;
	Node *node_right_parent = node->right->parent;
	Node *node_right = node->right;
	Node *node_parent = node->parent;
	node->parent->left = node_right;
	node->parent->left->parent = node;
	gp->right = node;
	node->right = node_parent;
	node->right->parent = node;
	node->parent = gp;
	insertFix(node->right);
	root->color = BLACK;
}

// case 8 uncle is BLACK node is RED and leftchild parent is RED and rightchild
template <typename T>
void set<T>::UncleBlackNodeREDRightchildParentRedLeftchild(set<T>::Node* node)
{
	Node *gp = node->parent->parent;
	Node *gp_left = gp->left;
	Node *node_parent_right = node->parent->right;
	Node *node_parent_parent = node->parent->parent;
	Node *node_left_parent = node->left->parent;
	Node *node_left = node->left;
	Node *node_parent = node->parent;
	node->parent->right = node_left;
	node->parent->right->parent = node;
	gp->left = node;
	node->left = node_parent;
	node->left->parent = node;
	node->parent = gp;
	insertFix(node->left);
	root->color = BLACK;
}

template <typename T>
void set<T>::MakeNull(set<T>::Node*& node)
{
	Node* sibling = nullptr;
	node->left = nullptr;
	node->right = nullptr;
	if (node->parent->left == node) {
		sibling = node->parent->right;
	} else {
		sibling = node->parent->left;
	}
	sibling->left = nullptr;
	sibling->right = nullptr;
	ColorFix(node);
}

template <typename T>
void set<T>::ColorFix(set<T>::Node*& node)
{
	set<T>::Node* sibling = nullptr;
	if (node->parent->left == node) {
			sibling = node->parent->right;
	} else {
			sibling = node->parent->left;
	}
	sibling->color = RED;
	node->color = RED;
	node->parent->color = BLACK;
}

template <typename T>
typename set<T>::Node* set<T>::InOrder (set<T>::Node* ptr)
{
	if (ptr != nullptr) {
		InOrder(ptr->left);
		std::cout<< ptr->data<< "   " << ptr->color << std::endl;
		InOrder(ptr->right);
	}
	return ptr;
}

template <typename T>
typename set<T>::Node* set<T>::find_right_more_node(set<T>::Node* node)
{
	if (node->right == nullptr) {
		return node;
	} else {
		return find_right_more_node(node->right);
	}
}

template <typename T>
typename set<T>::Node* set<T>::find_left_more_node(set<T>::Node* node)
{
	if (node->left == nullptr) {
		return node;
	} else{
		return find_left_more_node(node->left);
	}
}

// new node insertion with checking if the member data is unique or not
template <typename T>
void set<T>::InsertFromGivenNode(set<T>::Node* node,
	 set<T>::Node* current, bool& isEqual)
{
	if (node->data == current->data) {
		isEqual = false;
		delete node;
		return;
	} else if (node->data < current->data && current->left != nullptr) {
		InsertFromGivenNode(node, current->left, isEqual);
	} else if (node->data > current->data && current->right != nullptr) {
		InsertFromGivenNode(node, current->right, isEqual);
	} else if (node->data < current->data && current->left == nullptr) {
		current->left = node;
		node->parent = current;
		return;
	} else if (node->data > current->data && current->right == nullptr) {
		current->right = node;
		node->parent = current;
		return;
	}
}

template <typename T>
void set<T>::DeleteTheGivenVal (set<T>::Node* current, set<T>& arg_ob, T& arg_int)
{
	if (current != nullptr) {
		DeleteTheGivenVal(current->left, arg_ob, arg_int);
		if(current->data != arg_int) {
			arg_ob.insert(current->data);
		}
		DeleteTheGivenVal(current->right, arg_ob, arg_int);
	}
}

template <typename T>
void  set<T>::FreeSpace(set<T>::Node* ptr)
{
	if (ptr != nullptr) {
		FreeSpace(ptr->left);
		FreeSpace(ptr->right);
		delete ptr;
	}
}

template <typename T>
void  set<T>::insert(T arg_int)
{
	if (set<T>::root != nullptr) {
		bool isEqual = true;
		set<T>::Node* new_node = new set<T>::Node;
		new_node->data = arg_int;
		new_node->color = RED;
		InsertFromGivenNode(new_node, root, isEqual);
		if (isEqual) {
			insertFix(new_node);
		}
	} else {
		root = new Node;
		root->data = arg_int;
		root->color = BLACK;
		root->parent = nullptr;
	}
}

template <typename T>
void set<T>::Delete(T key)
{
	set  new_ob;
	DeleteTheGivenVal(root, new_ob, key);
	shutFreeSpace = true;
	Node* tmp_node;
	tmp_node = this->root;
	this->root = new_ob.root;
	new_ob.root = tmp_node;
}

#endif  // _DEFINITION_SET_HPP__
