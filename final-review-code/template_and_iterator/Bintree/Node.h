#include <iostream>


template <typename T>
class Node{
	T data;
	std::unique_ptr<Node> left;
	std::unique_ptr<Node> right;
	public:
	Node(const Node &other);
	Node(Node &&other);
	Node &operator=(const Node &other);
	Node &operator=(Node &&other);
};


