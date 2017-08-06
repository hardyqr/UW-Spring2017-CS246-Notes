# Covered Topics

### Iterator Class for `List`

### `auto` keyword

### `friend` keyword

### accessor/mutator methods

### System Modelling (UML)

### Relationship 1: Composition

### Relationshop 2: Aggregation

### Relationship 3: Inheritance

### 4 steps to object creation

### protected visibility

### `virtual` keyword (`isItHeavy` example) 

### Polymorphism 

### Virtual Destructor: why and when

### `final` keyword

### Pure Virtual Methods

### Abstract vs Concrete Classes

### Template classes and functions

### STL: vector/iterators

- STL: Standard Template Library

### Exceptions

### Exceptional Control Flow 

### Stack unwinding

### Iterator Patter

### Observer Pattern

### Decorator Pattern

### Revisiting the big five with inheritance

### Partial Assignment problem

### Mixed Assignment problem

### Solution without making operator= virtual

### Factory Method Pattern

### Template Method Pattern

### NVI Idiom
- Non-Virtual Interface Idiom
- In NVI
	- all public methods are non-virtual
	- all virtual methods are private (the virtual destructor being an exception)

```cpp
class DigitalMedia{
	public:
	void play(){
		doPlay();
	}
	private:
	virtual void doPlay() = 0;
};
```

### STL map
- `map<K,V>`

```cpp
#include <map>
map<string, int> m;
m["abc"] = 10;

cout << m["abc"] << endl; // prints 10
cout << m["def"] << endl; // prints 0, since "def" is not yet created
// if a key is not found, a default key value pair is added (value is default constructed)

// we don't know if there exists ["def",0] originally or it's default constructed
// how to look up if some key exists?
if(m.count("def")){
	// return 1 if found, 0 otherwise
}


for(auto p : m) {
	cout << p.first << " " << p.second << endl;
}
// the type for p is std::pair<string, int>
// pair is a struct with public first and second fields
// a map is traversed in sorted key order

```

### Visitor Design Pattern (VDP)

- recall the enemy-turtle-bullet game

- the strike method to call depends on both enemy & weapon object

```cpp
class Enemy{
	public:
	virtual void strike(Weapon &) = 0;
};


class Turtle: public Enemy{
	public:
	void strike(Weapon &w) override {
		w.useOn(*this);
	}
	
};

class Bullet: public Enemy{
	public:
	void strike(Weapon &w) override {
		w.useOn(*this);
	}
};


class Weapon{
	public:
	virtual void useOn(Turtle &) = 0;
	virtual void useOn(Bullet &) = 0;
};

class Strike: public Weapon{
	public:
	void useOn(Turtle &t) override{...}
	void useOn(Bullet &b) override{...}
};

// why don't we implement useOn in Weapon???

```

### Double Dispatch

### Adding functionality without changing class hierarchy code

### Circular Dependencies: solution: forward declare when possible

### Compilation Dependencies: when to forward declare vs when to include

### pImpl Idiom

### Generalize the pImpl Idiom: Bridge Design Pattern

### Exception Safety

### RAII

### `unique_ptr`

### `shared_ptr`

### Three levels of exception safety

### Casting: 4 kinds of casts

### Solution to mixed/partial assignment problem with virtual operator=

### VTable and Vptr

# Other Problems

- what's the difference between "own" and "has" ?
