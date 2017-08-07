# CS246
# Lecture 15: System Modeling (UML), Class Relationships


### UML: Unified Modeling Language

| Vec |
|---------- |
|-x: Integer|   
|-y: Integer|
|+getX: Integer|
|+getY: Integer|

// ??? what does optional mean?

- `-` indicates private
- `+` indicates public

### Composition
```cpp
class Vec{ 
	int x, y;
	public:
	Vec(int x, int y): 
		x{x},
		y{y} {}
};

class Basis{
	Vec v1, v2;
};

Basis b; // won't compile since v1, v2 require default constructor
```

- to fix this
	1. provide default constructor for `Vec`
	2. use the MIL to call an alternate constructor
	```cpp
	Basis::Basis(): 
		v1{0,1},
		v2{2,3} {}
	
	Basis b;
	// Now it compiles
	```

Composition: embedding an object inside another

- Basis "OWNS" the `Vec`

- typically, `class A` "OWNS" `class B`
	- if `B` has no existence of its own
	- if `A` is copied, `B` is copied (deep copy)
	- if `A` is destroyed, `B` is destroyed

- it's like parts in a car


[a UML graph for comp.]


### Aggregation 
- n.聚合

- "parts in a car" vs "parts in a catalog" ("HAS A")

- typically, `class A` "HAS" `class B`
	- if `B` can exist on its own
	- if we copy `A`, we don't copy `B` (shallow copy)
	- if we destroy `A`, we don't destroy `B`

[a UML graph for agg.]

### Inheritance
- n. 继承

|Book|
|----|
|- title: String|
|- author: String|
|- numPages: Integer|


|Text|
|----|
|- title: String|
|- author: String|
|- numPages: Integer|
| - topic: String|


|Comic|
|------|
|- title: String|
|- author: String|
|- numPages: Integer|
|- hero: String|

- In C
 	- union type 
	- array of `void*i`
- which is not elegant

#### Observation

- a `Text` is a `Book` with an extra topic field
- a `Comic` is a `Book` with an extra comic field

[a pic. showing their relations]

A child class inherits members (fields, methods) from its parent. Any method that you can call on a `Book` object, you can call on a `Text`/`Comic`.

Anything you can do with `cin` (`istream`) you can do with variabels of `ifstream` or `istringstream`.

### Inheriting Private Members

- Subclasses inherit private fields / methods 

- `Text` has inherited `title`, `author`, `numPages`

Rule: since `title`, `author`, `numPages` is private in `Book`, it is not accessible

```cpp
class Text:public Book{
	string topic;
	public: 	
	Text:(...):title{...} ... {}
};
// won't compile
```

- Won't compile since
 	- `title`, `author`, `numPages` are all private in `Book`
	- even if those inherited fields were public, still won't compile
		- rule: the MIL for `Text` can only use fields it declared ( which is only `topic` in our case)
	- steps for object construction:
		1. space is allocated
		2. superclass part of the object is constructed
		3. field initialization for fields declared in the class
		4. constructor body
	- the `Text` constructor won't compile since in step 2 of object construction, the `Book` part is default constructed, but we don't have a default constructor

- how to fix this
 	1. provide default `Book` constructor
	2. call a non-default constructor in the MIL
	```cpp
	Text::Text(string title, string author, int numPages, string topic):
		Book{title, author, numPages},
		topic{topic}, {}
	// this compiles
	```

### Protected Visibility

```cpp

class Book{
	protected:
	string title, author;
	int numPages;
	public:
	// ...
};
```
Protected members are accessible by **the class** but also **the subclass**.


The `Text` class could implement:

```cpp
void Text::addAuthor(string auth){
	author += auth;
}
```
- can access `author` as `Text` is a child and `author` is protected

```cpp

int main(){
	Text t = //...
	t.author = //...
   	// won't compile
}
```

- won't compile since this code is not in `Book` or subclass of `Book`

#### Protected breaks encapsulation

- subclass has access to protected members, it can break any **invariant** for those members.

ADVICE: keep fields private, if needed, give protected

(see `accessors/mutators`)

```cpp
class Book{
	string title, author;
	int numPages;
	protected:
	void addAuthor(string auth){
		//...
		author+=auth;
	}
};

```
