# Covered Topics

## before midterm


### Shell

### Linux File System

### Linux Commands Handout e.g. `cd`, `pwd`, `ls`, `echo`, `rm`

### Globbing patterns (glob n.通配符)

- globbing matching

- `*` - 0 or more chars

- `?` - single character


### `cat`

### input/output redirection

### pipes `|`

### `egrep`

- `?` - zero or one proceeding character

- `*` - zero or more proceeding character

- `+` - one or more proceeding character

- `.` - any character

- `^` - beginning of the line

- `$` - end of the line

- `[...]` or (...|...|...) - any one of the given expressions

- `[^...]` - any one of the characters not listed


- `egrep "."`  - any char.

- `egrep ".*"` - zero or more any char。

- `egrep ".+"` - one or more any char.

- `egrep ".?"` - zero or one any char

- `egrep "^.+$"` - match strictly from begin to end: one or more char.

- `egrep "[^abc]"` - all characters except `a`/`b`/`c`

### file permissions (`chmod`)


- permission
	- `r` - read
	- `w` - write
	- `x` - execute 
- class of user
	- `u` - user
	- `g` - group
	- `o` - other
	- `a` - all
- operators
	- `+` - add permission
	- `-` - substract permission
	- `=` - set permission

- `chmod u+x file.sh` before run

### Shell variables (`PATH`)

- global variable

### Shell Scripts

### Command Line Argument to a script - `$#`, `$0`,`$1`,`$?`

- `$0` - name of the shell script
- `$1` - first argument in the command line
- `$#` - number of arguments

- `test.sh`
```bash
!#/bin/bash
echo $#
```
if run `test.sh`, ouput is `0`
if run `test.sh 0`, ouput is `1`

- `$?` - exit status of the most recently executed program

if `0`, normal
if other, abnormal

### `#`, `?`, `/dev/null`, `0`

### script functions

- arithmetic
	- `x = $((x+1))`

### `if` statements

### `while` loop

### `for` loop

### C++: Hello World


### compiling / executing C++ programs


### Stream Objects (`cin`,`cout`,`cerr`)

### I/O Operators (`<<`,`>>`)

### `cin.fail()`, `cin,eof()`
	see notes

- implicit conversion of a stream to boolean

- `<<` and `>>` are  binary operators: must produce an expression

- `<<` and `>>` cascading

## `cin.ignore()`,`cin.clear()`

- `std::string`

## semantics of reading from `cin`
read until a whitespace

## I/O Manipulators: e.g. hex, dec, showpoint, setprecision, boolalpha, header

- hex - `cout << hex;`
- go back to decimal - `cout <<dec;`

- stream abstraction for files: `ifstream`, `ofstream`

- stream abstraction for strings: `istringstream`, `ostringstream`

## converting string to an integer

- `stoi`

- strings in C++

## string operations: concat, length, comparisons

- `s1+s2`

- `s1.length()`

- `strcmp(s1,s2)`
	- returns `0` if succeed


- default arguments

- funtion overloading

- Lvalue references

- pass by reference

- pass by value **vs** passing a pointer **vs** pass by reference : pros and cons of each

## dynamic memory allocation: `new` and `delete`

are all `new` memory heap allocated?

- operator overloading ,examples: `Vec`, `Grade`

- the C and C++ **preprocessor** (`#include`, `#define`, using `#define` for conditional compilation)

- seperate compilation

- C++ classes

- initializing objects

- constructors

- default constructor

- initialize consy and reference fields

- member initialization list (MIL)

## copy constructor

- a deep copy

- a constructor, do not return anything


## explicit keyword ???

## deconstructor

## copy assignment operator (`operator=`)


- Rvalue references

- move constructor

- move assginment operator

- superficial knowledge of copy / move elision (elision n.元音省略)

## rule of 5


- member functions **vs** standalone functions

## array of abjects
- `Target **targets = new Target[10]; `

- seprate compilation of classes (`::` the scope resolution opeartor)

- const methods

- mutable keywords

## static keyword in C++
> When we declare a member of a class as static it means no matter how many objects of the class are created, there is only one copy of the static member.

- invariants

## encapsulation: class keyword
- `class` - fields default private
- `struct` - fields default public

- invariant example: `List` and `Node` class




## adter midterm


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

- **pImpl** means pointer to implementation

- `window.h`

```cpp
#include <X11/Xlib.h>

class XWindow{
	Display *d;
	Window w;
	GC gc;
	...
	public:
	...
};
```
- notice that a file includes `window.h` would need to be recompiled even if a private member in `window.h` has changed

- to reduce compilation dependencies

- we take the private members into seperate implementation class

- `xwindowimpl.h`
```cpp
struct XWindowImpl{
	Display *d;
	Window w;
	GC gc;
	...
};
```

- `window.h`
```cpp
class XWindowImpl;
class XWindow{
	XWindowImpl *pImpl;
	public:
	...
};
```
- `window.cc`
```cpp
...
```


### Generalize the pImpl Idiom: Bridge Design Pattern

### Exception Safety

### RAII

- Resource Aquisition Is Initialization (RAII Idiom)

### `unique_ptr`

### `shared_ptr`

### Three levels of exception safety

- basic guarantee

- strong guarantee

- no throw guarantee


### Casting: 4 kinds of casts

- `static_cast`

- `reinterpret_cast`

- `const_cast`

- `dynamic_cast`


### Solution to mixed/partial assignment problem with virtual `operator=`

### VTable and Vptr
// what do we have to know about these concepts???

# Other Problems

### what's the difference between "owns" and "has" ?

- owns
	- responsible for deleting the object it owns
	- the owned object goes away when it goes away
