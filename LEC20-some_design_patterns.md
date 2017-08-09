# CS246
# Lecture 20: Design Patterns

### Factory Method Pattern

- a game

- level
	- normal
	- castle

- enemy
	- turtle
	- bullet


```cpp

Enemy *e = ...
Level *l = ... // let level decides what enemy to create
Players *p = ...

while(p->notDead()){
	// create enemy
	e = l->createEnemy();
	// allocate players
}
```

- let's create a factory of enemy inside the level classes

```cpp
class Level{
	public:
	virtual Enemy *createEnemy() = 0;
};
class Nomair: public Level{
	public:
	Enemy *createEnemy() override {//more turtles}
};
class Castle: public Level{
	public:
	Enemy *createEnemy() override {//more bullets}
};
```

#### Virtual Constructor Pattern

- similar to Factory Pattern (same?)

- constructors are made private
- provide public methods that act as virtual constructors i.e. factories

- eg. the begin/end method for `List::Iterator`



### Template Methods Pattern

- nothing to do with Template

- the base class implements **some** (can't be nothing, or the class is going to be virtual) feature/function and allows/requires subclasses to modify/fill in parts of the feature

- there are two kinds of turtles
	- green
	- red

```cpp
class Turtle{
	public:
		void draw(){
			drawHead();
			drawShell();
			drawFeet();
		}
	private:
		void drawHead(){...}
		virtual void drawShell() = 0;
		void drawFeet(){...} 
};

```
- given a turtle ptr, the only way to draw a turtle is to call the `draw` method
- can't just draw parts of a turtle as the helpers are all private

```cpp
class RedTurtle: public Turtle{
	void drawShell() override{// draw some red shell}
};
```

### Non-Virtual Interface (NVI) Idiom

- take any *public virtual* method

- to have public method to call private method

- `public:` 
	- used by client code
	- comes with pre/post conditions

- `virtual` 
	- invites subclasses to replace behavior


- there is no way to guarantee that a subclass that overrides a virtual method still guarantees the past conditions

- In the NVI idiom
	- all public methods are non-virtual
	- all virtual methods are private (the virtual destructor being an exception)

```cpp
class DigitalMedia{
	public:
	virtual void play() = 0; // not using NVI 
};
```

- with NVI
```cpp
class DigitalMedia{
	public:
	void play(){doPlay();}
	private:
	virtual void doPlay() = 0;
};
```

- you still get the control of what's going to happen before `doPlay()`


#### `STL: map<K,V>`

- Template class paramterized on two types
- generalization of an array
	- can map elements of type `K` to elements of type `V`
	- internally implemented using balanced binary trees

```cpp
#include <map>

map<string, int> m;
m["abc"] = 5; // inserts ["abc", 5]

cout << m["abc"] << endl; // prints 5
cout << m["def"] << endl; // prints 0 since def is not yet created
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

### Visitor Design Pattern

- Used to implement double dispatch 
	- we can consider double dispatch as overloading + overriding
- Dynamic Dispatch, use the `virtual` keyword

- sometimes the right method to call depends on the runtime type of two objects

- go back to the enemy-turtle-bullet game

- weapon
	- stick
	- rock

- four combinations
	- the `strike` method to call depends on both the `Enemy` & `Weapon` object

```cpp
class Enemy{
	public:
		virtual void strike(Rock &) = 0;
		virtual void strike(Stick &) = 0;
}
```

- the problem
```cpp
Enemy *e = ...
Weapon *w = p->chooseWeapon();
e->strike(*w);
// c++ does not support dynamic dispatch on arguments
```

- The VDP uses a combination of 
	- overriding (virtual methods)
	- overloading (some methods name different parameter types)

```cpp
class Enemy{
	public:
	virtual void strike(weapon &) = 0;
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
```

