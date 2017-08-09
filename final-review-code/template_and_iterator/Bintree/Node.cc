#include "Node.h"

using namespace std;

Node::Node(const Node<T> &other):
	data{other.data},
	left{other.left?make_unique<Node<T>>(other.left):unique_ptr<Node<T>>()},
	right{other.right?make_unique<Node<T>>(other.right):unique_ptr<Node<T>>()} {}

Node::Node(Node<T> &&other):
	data{other.data},
	left{std::move(other.left)},
	right{std::move(other.right)} {}


Node<T> &Node::operator=(const Node<T> &other){
	data = other.data;
	if(other.left){
		left = make_unique<Node<T>>(*other.left);
	} else {
		left = unique_ptr<Node<T>>();
	}
	if(other.right){
		right = make_unique<Node<T>>(*other.right);
	} else {
		right = unique_ptr<Node<T>>();
	}
	return *this;
}

Node<T> &Node::operator=(Node<T> &&other){
	data = other.data;
	left = std::move(other.left);
	right = std::move(other.right);
}
