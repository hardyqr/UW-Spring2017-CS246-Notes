# CS246
# Lecture 13: const methods, Invariants of Encaplsulation

## Const Methods

```cpp
struct Student{
	int assns, mt, final;
	float grade() {
		return assns*0.4+mt*0.2+final*0.4;
	}
	const Student billy{60,70,80};

	cout << billy.grade() << endl; // won't compile as grade "could" change the fields of billy
};
```

```cpp

struct Student{
	int assns, mt, final;
	float grade() const{
		return assns*0.4+mt*0.2+final*0.4;
	}
	const Student billy{60,70,80};

	cout << billy.grade() << endl; // compiles
};
```
You can only call **const methods** on **const object**.



```cpp
struct Student{
	int asssns,mt,final;
	int counter = 0;
	float grade() const {
		++counter;
		return assns*0.4+mt*0.2+final*0.4;
	}
};

```

- We can make a field mutable
	- const methdos can modify mutable fields

#### `static`

- `static` - can be applied on fields and member functions

- A `static` field is associated with a class and not the object of the class

```cpp
struct Student{
	static int numObjects; // just a declaration
	Student(...):...{
		++numObjects;
	}
};

```

C++ Rule: static fields must be defined in an external file.
```cpp
int Student::numObjects = 0; //definition
```

- A **static member function** is associated with the class 
	- **does not need an object to call this function**
	- since a static member function can be called without any object, the static member function does not have the `this` parameter
	- **static member functions can only access static fields and member functions.**

```cpp
struct Student{
	static int numObjects; // defined externally
	static int getCount() {
		return numObjects;
	}
};


int main() {
	Student s1{...},s2{...};
	cout << Student::numObjects << endl;
	cout << Student::getCount() << endl;
}
```

## Invariants of Encapsulation

```cpp
struct Student{
	int data;
	Node *next;
	Node(int data, Node *next):
		data{data},next{next} {}
	~Node() {delete next;}

};

int main() {
	Node n1{1, new Node{2,nullptr}};
	Node n2{3,nullptr};
	Node n3{4, &n2}; 
}
// most probabily it would crash

```

- invariance
- **remember: only delete allocated memory in heap!!!**
- `Node` class assumes the next is either `nullptr` or points to an object in the heap
	- next of `n3` is not an address in the heap
	- program will crash


Invariant: A statement / assumption that is supposed to hold true for a class for it to function correctly.


- stack class 
	- the last thing we pushed, is the first thing popped.

- It is hard to reason about programs if we cannot guarantee invariants.
- It is impossible to guarantee invariants if a client has fully access to member of a class.


### Encapsulation

- Objects should act like black boxes
	- a capsule
	- hide implementation details
	- clients interact through provided interface

Keyword: `private` / `public`

```cpp
struct Vec{
	Vec(int x, int y) ...
	//default visibility in a struct is public
	private: //change visibility to private
	int x;
	int y;
	puclic:
	Vec operator+(...) ...
};

int main() {
	Vec v{3,4};
	Vec v1 = v + v; // 2 parameter constructors and  operator + is public
	int num = v.x; // not allowed
	int num1 = v.y; // not allowed 
	// Vec::x, Vec::y are private and you are an outsider
}
```

Advice: at a minimum, keep all fields private.

**The keyword `class` makes a class that is exactly identical to one made using `struct`. The only difference: default visibility in a class is private.** 
```cpp
class Vec{
	//default visibility is private
	int x;
	int y;
	public:
	Vec() ...
	Vec operator+() ...
};
```

- to guarantee `Node` invariant

- `next` is either `nullptr` or points into heap

- create a class `List` that wraps `Node` objects

`List.h`

```cpp
class List{
	struct Node; //declared a private nested Node Class
	Node *theList;
	public:
	void addToFront(int n);
	int ith(int i);
	~List();
};
```

`List.cc`
```cpp
struct List::Node{
	int data;
	Node *next;
	Node(int data, Node *next): ...
	~Node(){ delete next;}
}

void List::addToFront(int n) {
	theList = new Node(n, theList); // new heap allocated memory whenever add a new node
}

int List::ith(int i) {
	Node *cur = theList;
	for(int j = 0; j < i && cur; i++){
		cur = cur->next;
	}
	return cur->data;
}

List::~List(){
	delete theList;
}
```
Typically, list traversal is O(n).

`class List` has O(n<sup>2</sup>) traversal, the i<sup>th</sup> method is O(n) and it must be called n-times to get all nodes.

Need to provide O(n) traversal without exposing `Node`s.



### Design Patterns

Recipe: "if you are facing this programming problem, then the following solution might help"

#### Iterator Design Pattern

- create an `Iterators` class which manage access to the `Node`s
- the `Iterator` will act as an abstraction of a pointer into the linked List

- see next note

