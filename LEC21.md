# CS246
# Lecture 21: Visitor Design Pattern (contd.), Compilation Dependencies



//??? what's the context?

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

It is best to avoid unnecessary `include`

- advice: always prefer to **forward declare** a class/type instead of including it.

```cpp

class XYZ; // forward declaration
```

- `a.h`
```cpp
class A{...};
```

- `b.h`
```cpp
#include "a.h" // compiler needs to know what's in a since b is going to have/inherit members from A
class B: public A{
	...
};

```

- `c.h`
```cpp
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

- **pImpl Idiom**: pointer to implamentation
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
...
```
