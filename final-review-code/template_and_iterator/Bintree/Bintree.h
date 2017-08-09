#include <iostream>
#include "Node.h"

template <typename T>
class Bintree{
	std::unique_ptr<T> root;
	public:
	Bintree();
	Bintree(const Bintree<T> &bt);
	Bintree(Bintree<T> &&bt);
	Bintree<T> &operator=(const Bintree<T> &bt);
	Bintree<T> &operator=(Bintree<T> &&bt);
	~Bintree();
};

