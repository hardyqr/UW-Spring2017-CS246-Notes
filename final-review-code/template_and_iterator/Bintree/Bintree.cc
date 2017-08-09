#include "Bintree.h"

using namespace std;

Bintree::Bintree():root{nullptr}{}

Bintree::Bintree(const Bintree<T> &other):
	root{other.root?make_unique< Node<T> >(*other.root):unique_ptr< Node<T> >()} {}

Bintree::Bintree(Bintree<T> &&other):
	root{std::move(other.root)} {}

Bintree<T> &Bintree::operator=(const Bintree<T> &other){
	/*
	if(other.root) root = make_unique< Node<T> >(*other.root);
	else root = unique_ptr<Node<T>>();
	return *this;
	*/
	Bintree<T> temp = other; // use T's copy assignment operator
	root.swap(temp.root);
	return *this;
}

Bintree<T> &Bintree::operator=(Bintree<T> &&other){
	/*
	std::move(other.root);
	return *this;
	*/
	root.swap(other.root);
	return *this;
}

