# CS246
# Tutorial 9

- Abstract classes, Pure Virtual methods
- Destructors
- Vectors
- Exceptions

- abstarct class has at least one P.V. method (including unimplemented superclass P.V. methods)
- any class that is not abstract is concrete

```cpp
class Animal{
	...
	public:
		virtual void eat() = 0; // no implementation
};

Animal a; // wrong
new Animal; // wrong

```
- you cannot create an abstract class with P.V. method

```cpp
class A{
	...
	~A(){}
};
class B: public A{
	...
	~B(){}
};

A *a = new B;
delete a; // memory leak
// Fix: ~A() virtual

class C: public B{
	...
	~C(){}
};

B *b = new C;
delete b; // OK. ~B() is virtual. So does ~A(), ~C()


class S{
	virtual ~S() = 0;
};

S::~S(){}

```

### Exception

- In C (in linux)
	- errors (global value) -> `cin`, `cout`, `istreams`, ... 
	- return value (0 if succeed, 1 tailed)

- above, can be ignored

- In C++, Exceptions 
	- require the programmers to reactively solve problems in program excecution

```cpp
try{
	throw 42; // can throw any value
} catch(int &i){...}
catch(int i){...} // runs
catch(...){...} // "..." means match any exception

int &i = 42;
```

- to avoid copies, always catch by reference (when throwing objects)

- recommendations
	- throw by value
	- catch by reference (otherwise slicing  could occur) ???
