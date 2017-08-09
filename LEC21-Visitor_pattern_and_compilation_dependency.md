# CS246
# Lecture 21: Visitor Design Pattern (contd.), Compilation Dependencies


## Visitor Design Pattern

- Add functionality to an inheritance hierarchy without actually changing/adding code to the hierarchy.
	- we can do this as long as the hierarchy already contains method that accept visitors

```cpp
class Book{
	public:
	virtual void accept(BookVisitor &v){
		v.visit(*this);
	}
};

class Text: public Book{
	public:
	void accept(BookVisitor &v) override{
		v.visit(*this);
	}
};

class Comic: public Book{
	public:
	void accept(BookVisitor &v) override{
		v.visit(*this);
	}
};

class BookVisitor{
	public:
	virtual void visit(Book &b) = 0;
	virtual void visit(Text &t) = 0;
	virtual void visit(Comic &c) = 0;
};

```
- let's catalogue our collection of books

- use another name for `Book` - # of books by author

- use topic for `Text` - # of texts for this topic

- use hero for ``Comic - # of comics for this hero

```cpp
class Catalogue: public BookVisitor{
	map<string,int> myCatalog;
	public:
	void visit(Book &b) override {
		myCatalog[b.getAuthor()] = myCatalog[b.getAuthor()] + 1;
		// ++ mycatalog[b.getAuthor()];
	}
	
	void visit(Text &t) override {
		++ myCatalog[t.getTopic()];
	}

	void visit(comic &c) override {
		++ myCatalog[c.getHero()];
	}
};
```
## Compilation Dependencies


- `se/visitor/broken`

- there is a compilation dependency between `Book.h` and `BookVisitor.h`

- an `include` creates a compilation dependency
	- if the included file changes, the file which has a `include` must be recompiled

- unnecessary `include` slows down compile time

It is best to avoid unnecessary `include`.

- advice: always prefer to **forward declare** a class/type instead of including it.

```cpp
class XYZ; // forward declaration
```

- `a.h`
```
class A{...};
```

- `b.h`
```
#include "a.h" // compiler needs to know what's in a since b is going to have/inherit members from A
class B: public A{
	...
};

```

- `c.h`
```
#include "a.h" // compiler needs to know the size of C -> needs to know size of A -> needs fields in A
class C{
	A a;
};
```

- `d.h`
```cpp
class A; // size of a ptr is always fixed, we can simply tell the compiler that type A will exist

class D{
	A *myA;
};
```

- `e.h`

```cpp
class A;
class E {
	A foo(A x); // A is the param type and return type
};

```

- `d.c`

```cpp
#include "a.h" // we're using the method of A, we need to know what's inside
D::foo(){
	myA->someMethod();
}
```

### Reducing Compilation Dependencies

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
- Note that a file includes `window.h` would need to recompile even if the change in window.h is to a **private** member

- **pImpl Idiom**: pointer to implementation
- take the private members into a seperate implementation class 
- replace there with a pointer to the implementation class

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
#include "window.h"
#include "xwindowImpl.h"

Xwindow::Xwindow(): pImpl{new XwindowIplm} {}

~Xwindow(){delete pImpl;}

```

- Bridge Design Pattern (similar to Strategy Pattern)
