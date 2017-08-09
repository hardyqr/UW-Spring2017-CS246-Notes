# CS246
# Lecture 11: Destructors, Copy Assignment Operator

## Destructors 

- When an object is destroyed, the destructor runs.
	- when a stack allocated object goes out of scope
	- when a heap allocated object is deleted (delete the ptr to the object)

#### 3 steps to destroy an object

1. destructor body runs

2. fields that are objects are destroyed (reverse declaration order)

3. space is de-allocated

- a class can have only one destructor 

- the destructor is named `~ClassName()`

- every class comes with a destructor 
	- simply calls destructor on fields that are objects

```cpp
Node *np = new Node{1, new Node{2, new Node{3, nullptr}}};
```

If we do not delete `np`, then 3 nodes are leaked.

- If we write `delete np;`
	- we are deleting Node 1
	- Node 2, Node 3 are still leaked

We need our own destructor.

```cpp
struct Node{
	...
	~Node(){
		delete next;
	}
	// reclaim the entire linked list
};
```

## Copy Assignment Operator

```cpp
student billy{60,70,80};

student bobby = billy; // copy constructor

student jane;

jane = billy; // copy assignment operator
```

Sometimes the free operator `=` is not what we want.

```cpp
struct Node{
	...
	Node &operator=(const Node &others) {
		data = others.data;
		delete next;
		next = others.next?new Node(*otehrs.next):nullptr;
		return *this;
	}
};
```


```cpp
n1 = n2 = n3;

// it is calling:
n1.operator=(n2.operator=(n3));
```

- Since `operator=` updates on existing object, next could already be pointing to heap allocated memory.
	- we must delete that first

```cpp
Node n{1, new Node{2, nullptr}};
n = n;
```

- We delete `n.next` and then read `n.next`
	- `next` is a dangling ptr

- Add a self assignment check

```cpp
struct Node{
	...
	Node &operator=(const Node &other) {
		if(this == &other) return *this;
		data = other.data;
		delete next;
		next = other.next?new Node(*other.next):nullptr;
		return *this;
	}
};

```
```cpp
Node &operator=(const Node &other){
	if(this == &other) return *this;
	Node *tmp = next;
	next = other.next?new Node(*other.next):nullptr;
	dalete tmp;
	data = other.data;
	return *this;
}
// exception safe code
```

### Implement `operator=` using copy and swap

```cpp
#include <utility>
struct Node{
	...
	void swap(Node &other){
		using std::swap;
		swap(data, other.data);
		swap(next, other.next);
	}
}
```

```cpp
Node &operator=(const Node &others){
	Node tmp = other; // relies on deep copy constructor
	swap(tmp);	
	return *this;
}
```

- After `swap`, `this` is a copy of others
	- `tmp` contains `this`'s old data
		- whch is designed when `tmp`(stack allocated) goes out of scope
		- relies on correctly implemented destructor


(see `classes.cc`/`rvalue.cc`)


