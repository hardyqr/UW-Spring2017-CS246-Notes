# CS246
# Lecture 12: Rvalue References + short topics 


(example `classes.cc`/`rvalue.cc`/`node.cc`)

```cpp
Node plusOne(Node n){
	//...
	return n;
}

Node n{1, new Node{2, nullptr}};

Node n2{plusOne(n)};

```

If the RHS is a **temporary** then steal, otherwise copy.

Rvalue Reference (`&&`) - refers to a temporary object

Lvalue Reference (`&`)

#### Move constructor

- 1 parameter, a rvalue reference

```cpp
struct Node{
	//...
	Node(Node &&other):
		data{other.data},
		next{other.next} {
			other.next = nullptr; 
			// ***important to do since other is a rvalue ref.
		}
};

```

- `other` is a rvalue ref. which means it's a temporary 
	- it's about to be destroyed

Note: Now 4 calls to copy constructor, 1 call to move constructor

#### Move assignment operator

```cpp
Node m = //...
m = plusOne(n); // plusOne(n) is rvalue

Node &operator=(Node &&other) {
	swap(other);
	return *this;
}

```

- Move copy / assignment operator
	- you get one for free
	- these go away as soon as you implement any of copy constructor / copy assignment / deconstructor / move constructor / move assignment


- A program will always use the move version of copy / copy assignment if 
	- they are available
	- `other`(rhs) is a rvalue reference


#### Rule of 5

- If you write a custom version of 
	- copy constructor 
	- copy assignment operator 
	- deconstructor 
	- move constructor 
	- move assignment operator
- then you typically need to implement all of them 

### Copy / Move elision 
(elison n.元音省略)

(see `/8-elison/vec.cc`)
```cpp
Node plusOne(Node n){
	//...
	return n;
}
Node n://...
Node n2{plusOne(n)};
```

```cpp
Vec makeAVec(){return {3,4};}

Vec v = makeAVec();
```

- If you run this, copy/move constructors are not  called
	- program directly writes `{3,4}` to `v`

- A compiler is allowed (not required) to skip copy/move constructor in certain situations
	- even if the constructor have side affects

To turn off this optimization: `g++14 -fno-elide-constructors [files]`



## Standalone functions vs Methods - operator overloading 

- `operator=` must be implemented as a method
	- LHS is the `this` pointer

We can implement other operators as methods.
```cpp
struct Vec{
	int x,y;
	Vec operator+(const Vec &v){
		return {x+v.x,y+v.y};
	}
	Vec operator*(int k){
		return {x*k,y*k};
	}
};

// we now can do v*5, v1+v2

Vec operator*(int k, const Vec &v){
	return v*k;
}
// now we can even do 5.operator*(v)
```


What about I/O operators? <br>
`cout << v;` `cin >> v;`

```cpp
struct Vec{
	ostream &operator(ostream &out) {
		//...
		return out;
	}
};

v2<<(v1 << out);
```



- While it is possible to implement I/O operator as methods, do not do it 
	- it makes writing output statement confusing as we need to ??? the LHS and RHS

- Some operators must be implemented as methods
	- `operator=`
	- `operator[]`
	- `operator()`
	- `operator->`

## Arrays of Objects

```cpp
struct Vec{
	int x, y;
	Vec(int x, int y): x{x},y{y} {}
};

Vec vecs[3];// stack allocated array of Vec objects
Vec *vecs1 = new Vec[3]; // heap allocated array of Vec objects
// but either will compile
```

- Won't compile because we are unable to default construct `Vec` objects
	- no default constructor 

- Fix to this
	- provide default (0 param) constructor 
	- stack array: use array initialization `Vec vecs[3]:{Vec{0,0}, Vec{1,2}, Vec{3,4}};`
	- work for both stack / heap allocation: create array of pointers to objects 
		```cpp
		Vec *vecs[3]; // stack allocated array of Vec *
		Vec **vecs1 = new Vec*[3];` `vecs1[0] = new Vec{1,2}; //???
		
		// how do we free all the memories?
		for(int i = 0; i < vecsize; i++ )
			delete vecs1[i];
		delete [] vecs1;
		```

## Seperater Completion

headers `.h` - type definitions, function headers

implementation `.cc` - function definitions

Method headers go into the header files.

Method implementation in `.cc` file.

`node.h`

```cpp
#ifndef NODE_H
#define NODE_H

struct Node{
	int data;
	Node *next;
	Node{int data, Node *next};
	int getData();
	// ...
};

#endif
```

`node.cc`
```cpp
#include "node.h"

Node::Node(int data, Node *next):
	data{data}, next{next} {}
	int Node::getData(){retyrn data;}
// Node:: is the only difference
// :: is the scope resolution operator
```

## Const Methods

```cpp
struct Student{
	int assns, mt, final;
	float grade(){
		return assgn*0.4 + mt*0.2+final*0.4;
	}
};

const Student billy{60,70,80};

cout << billy.grade() << endl; // won't compile
```
```cpp
struct Student{
	int assns, mt, final;
	float grade() const{
		return assgn*0.4 + mt*0.2+final*0.4;
	}
};

const Student billy{60,70,80};

cout << billy.grade() << endl; // compiles

```

- `billy` is const
	- the first `grade` does not promise it will not change fields

If you declare a method const, you are promising not to change the fields of the object on which the methods was called.
