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

- some questions

1. display those lines from the first 10 lines of `file.txt` that constains the username of the currently logged in user.

```bash
head -10 file.txt | egrep "$(whoami)"
```
- notice that `()` is a must

2. create a file named `context.txt` that containing the filenames of all files including the hidden files in the user's in the home directory that contains "ab" in the filename.

```bash
ls -a ~ | egrep "ab" > content.txt
```

3. sort the contents of `input.txt` and append the results to `log.txt`.
```bash
sort inout.txt >> log.txt
```

4. regular expression: `(cs)*246`, will "CS246" be matched?

Yes. There'd be no `(cs)*`. Just `246`.

5. regular expression: `^(..)*.+$` will match all non-empty lines that contain an odd length of characters?

No. It can match both odd and even lines.

6. regular expression `^a*$` will begin with the character "a", followed by anything at all?

No. It would only followed by "a"/"aa"/"aa...".


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

### implicit conversion of a stream to boolean

- `<<` and `>>` are  binary operators: must produce an expression

- `<<` and `>>` cascading

### `cin.ignore()`,`cin.clear()`

### `std::string`

### semantics of reading from `cin`
read until a whitespace

### I/O Manipulators: e.g. hex, dec, showpoint, setprecision, boolalpha, header

- hex - `cout << hex;`
- go back to decimal - `cout <<dec;`

- stream abstraction for files: `ifstream`, `ofstream`

- stream abstraction for strings: `istringstream`, `ostringstream`

### converting string to an integer

- `stoi`

- strings in C++

### string operations: concat, length, comparisons

- `s1+s2`

- `s1.length()`

- `strcmp(s1,s2)`
	- returns `0` if succeed


- default arguments

### funtion overloading

- if # / type of parameter different, can share the same name

### overriding

- inherited class rewriting the virtual method of the base class


### reference, general
- cannot create ptr to a reference (ref. doesn't have its own address) 
	- `int& *p` is not allowed

- cannot have reference ot a reference 
	- `int &&a` is not allowed
- but can have reference to a ptr

### Lvalue references



### pass by reference

### pass by value **vs** passing a pointer **vs** pass by reference : pros and cons of each

- pass by value
	- do a copy, expensive

- pass by ptr
	- can be Null

- pass by reference
	- like pass in an alias
	- cannot be Null

### dynamic memory allocation: `new` and `delete`

are all `new` memory heap allocated? yes.
```cpp
Node *np = new Node;
...
delete np;


int *arr = new int [n];
...
delete [] arr;
```

- problems
	- memory leak: forget to free previous storage
	- dangling ptr: result of dereference is undefined

### operator overloading ,examples: `Vec`, `Grade`

### the C and C++ **preprocessor** (`#include`, `#define`, using `#define` for conditional compilation)

- **preprocessor** is a text editor that modifies the program text before compilation

- `define VAR VALUE`

- conditional compilation
```cpp
#define BBOS 1
#define IOS 2
#define OS BBOS
#if OS == BBOS
	long long int key;
#elif OS ==IOS
	short int key;
#endif
```

- check `define`s
```cpp
#ifndef MYDEF_H
#define MYDEF_H
...
#endif
```
- exclude code
```cpp
if 0
...
#endif
```

- `DEBUG`
```cpp
#if DEBUG
...
#endif
```
`g++ -DDEBUG file.cc`

- define symbols via compiler args
```cpp
int main(){
	cout << X << endl;
}
```
`g++ -DX=1 file.cc`


### seperate compilation

- preprocessor -> compiler (compiles files seperately) -> linker (put object files together into exec)

`g++ -c vector.cc` - only compiles, get `.o`,does not link

`g++ vector.o main.o -o program` - links all `.o` files into exec

### makefile



### C++ classes

### initializing objects

### constructors

### default constructor

### initialize const and reference fields

### member initialization list (MIL)

### copy constructor

- a deep copy (allocate new memory)

- a constructor, do not return anything


### explicit keyword

- avoid implicit conversion

### deconstructor

### copy assignment operator (`operator=`)


### Rvalue references

### move constructor

### move assginment operator

### superficial knowledge of copy / move elision (elision n.元音省略)

### rule of 5
- if create one of the five, create all of the five
	- destructor
	- copy constructor
	- copy assignment operator
	- move constructor
	- move assignment operator

### member functions **vs** standalone functions

### array of abjects
- `Target **targets = new Target[10]; `

### seprate compilation of classes (`::` the scope resolution opeartor)

- `AAA::BBB` 
	- scope resolution operator
	- means `BBB` is in the context of `AAA`

### const methods

### mutable keywords

### static keyword in C++
> When we declare a member of a class as static it means no matter how many objects of the class are created, there is only one copy of the static member.

- invariants

### encapsulation: `class` keyword
- `class` - fields default private
- `struct` - fields default public

- invariant example: `List` and `Node` class

### Coupling & Cohesion
- coupling: degree to which modules depend on each other
- cohesion: how closely related elements of a module are to each other

- goal: low coupling (reusability, extensibility) and high cohesion (easy to use and understand)




## after midterm


### Iterator Class for `List`

```cpp
class List{
	class Node;
	Node *theList = nullptr;
	public:
	class Iterator{
		Node *p;
		explicit Iterator(Node *p); // ctor
		public:
		int &operator*() const;
		Iterator &operator++();
		bool operator==(const Iterator &other) const;
		bool operator!=(const Iterator &other) const;
		// overload *, ++, !=, ==
		// notice, except ++, all const methods

		friend class List;
		~Iterator(); // dtor
	};

	Iterator begin();
	Iterator end();

	void addToFront(int i);
	int ith(int i);

	~List(); //dtor
};

struct Node{
	int data;
	Node *next;
	Node(int data, Node *n): data{data}, next{n} {}
	~Node{delete next;}
};

List::Iterator::Iterator(Node *p): p{p} {}

int &List::Iterator::operator*() const{
	return p->data;
}

List::Iterator &List::Iterator::operator++(){
	p = p->next;
	return *this;
}

bool List::Iterator::operator==(){
	//return p == other.p;
	return *this == other;
}

bool List::Iterator::operator!=(){
	return !(*this == other);
}

List::Iterator List::begin(){return Iterator{theList};}

List::Iterator List::end(){return Iterator{nullptr};}

void List::addToFront(int i){
	theList = new Node{i, theList};
}

int ith(int i){
	Node *cur = theList;
	for(int j = 0; j < i && cur; ++j, cur = cur->next);
	return cur->data;
}

int main(){
	List lst;
	lst.addToFront(1);
	lst.addToFront(2);
	lst.addToFront(3); // 3-2-1
	for(List::Iterator it = lst.begin(); it != lst.end() ; ++it){
		cout << *it << endl; // prints 3\n2\n1\n
	}
	// alternative
	/*
	for(auto it: lst){
		cout << *it <<endl;
	}
	*/
}
```

### `auto` keyword

### `friend` keyword

### accessor/mutator methods

### System Modelling (UML)

### Relationship 1: Composition
- "owns a"

### Relationshop 2: Aggregation
- "has a"

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

- when exit a scope, stack allocated objects' destructor are called (the process of destroying local objects)

### Iterator Pattern

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
```

### Double Dispatch

- Visitor Design Pattern

- overloading (multiple types of parameters) + overriding (overrides virtual method of superclass)


### Adding functionality without changing class hierarchy code
- Decorator pattern???

### Circular Dependencies: solution: forward declare when possible

### Compilation Dependencies: when to forward declare vs when to include

### pImpl Idiom

- **pImpl** means pointer to implementation

- `window.h`

```cpp
#include <X11/Xlib.h>

class Xwindow{
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
struct XwindowImpl{
	Display *d;
	Window w;
	GC gc;
	...
};
```

- `window.h`
```cpp
class XwindowImpl;
class Xwindow{
	XwindowImpl *pImpl;
	public:
	...
};
```
- `window.cc`
```cpp
Xwindow::Xwindow(): pImpl{new XwindowImpl} {}

Xwindow::~Xwindow(delete pImpl;)
```


### Generalize the pImpl Idiom: Bridge Design Pattern





### Exception Safety

### RAII

- Resource Aquisition Is Initialization (RAII Idiom)

- always use a wrapper to make memory being alocated on stack and gets automatically freed


### `unique_ptr`

### `shared_ptr`

### Three levels of exception safety

- basic guarantee

- strong guarantee

- no throw guarantee


### Casting: 4 kinds of casts

- `static_cast`
	- does not check the actual type

- `reinterpret_cast`

- `const_cast`

- `dynamic_cast`
	- checks the actual type

- for smart ptrs
	- `static_pointer_cast`
	- `dynamic_pointer_cast`
	- `const_pointer_cast`

### Solution to mixed/partial assignment problem with virtual `operator=`

- there're 2 solutions

- first is to make the base class abstract (has Pure Virtual method)
```cpp
class AbstractBook{
	string title, author;
	int numPages;
	protected:
	virtual AbstractBook &operator=(const AbstractBook &other);
	public:
	virtual ~AbstractBook() = 0;// dtor
};

class normalBook:public AbstractBook{
	public:
	normalBook &operator=(const AbstractBook &other) override;
};

class Text: public AbstractBook{
	string topic;
	...
};

class Comic: public AbstractBook{
	string hero;
	...
};
```


### VTable and Vptr
- exist when there is virtual method

- dynamic dispatch is expensive
	- dereference twice
	- need space for vtable and vptr


# Other Problems

### what's the difference between "owns" and "has" ?

- owns
	- responsible for deleting the object it owns
	- the owned object goes away when it goes away
