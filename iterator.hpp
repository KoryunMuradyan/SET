#ifndef __ITERATOR_HPP__
#define __ITERATOR_HPP__

#include "declaration_set.hpp"

using namespace stl;

template <typename T>
typename set<T>::iterator& set<T>::iterator::operator++ ()
{
	if (current->right == nullptr) {
		Node* tmp_node = return_to_left_path(current);
		if (tmp_node->parent == nullptr) {
			current = current->right;
			return *this;
		}
		current = tmp_node->parent;
		return *this;
	} else {
		current = find_left_more_node(current->right);
	}
	return *this;
}

template <typename T>
T& set<T>::iterator::operator* ()
{
	assert(current != 0);
	return current->data;
}

template <typename T>
bool set<T>::iterator::operator== (const set<T>::iterator& o)
{
	return current == o.current;
}

template <typename T>
bool set<T>::iterator::operator!= (const set<T>::iterator& o)
{
	return this->current != o.current;
}

template <typename T>
typename set<T>::Node *set<T>::iterator::find_left_more_node(Node* arg_node)
{
	if (arg_node->left == nullptr) {
		return arg_node;
	} else {
		return find_left_more_node(arg_node->left);
	}
}

template <typename T>
typename set<T>::Node *set<T>::iterator::return_to_left_path(Node* arg_node)
{
	if (arg_node->parent == nullptr) {
		return arg_node;
	}
	else if (arg_node == arg_node->parent->right) {
		return return_to_left_path(arg_node->parent);
	} else {
		return arg_node;
	}
}		

template <typename T>
typename set<T>::iterator set<T>::begin()
{
	Node * tmp = find_left_more_node(root);
	return iterator(find_left_more_node(root));
}

template <typename T>
typename set<T>::iterator set<T>::end()
{
	return iterator(nullptr);
}

#endif // __ITERATOR_HPP__ 
