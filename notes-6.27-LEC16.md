# CS246 
# Lecture 16: Method Overrdding, Dynamic Dispatch


- Book `isHeavy` if > 200 pages
- Text > 500 pages
- Comic > 30 pages

`c++/inheritance/example2`

```cpp
class Book{
	//...
	int numPages;
	public:
	int getNumPages() const{ return numPages;}
	bool isHeavy() const{return numPages > 200;}
};

class Comic:public Book{
	public:
	bool isHeavy()const{return getNumPages()>30;}
};

// Comic::isHeavy overrides Book::isHeavy
Book b{"smallBook","auth",50};
b.isHeavy();// Book::isHeavy runs, false

Comic c{"BigComic","auth",40,"Batman"};

c.isHeavy();// Comic::isHeavy runs, true

Book b2 = comic{"BigComic",auth,40,"Batman"}; // legal because comic is a book

b2.isHeavy(); // Book::isHeavy runs

```
- Book
	- title
	- author
	- numPages

- Comic
	- title
	- author
	- numPages
	- hero

- `hero` field is sliced here

- this is called **Object Cohesion**
	- When place a subclass object in a super class variable, the subclass object is sliced

- Using superclass pointers to point to subclass object


```cpp
Comic c(...,...,40,...);

Comic *cp{&c};
cp->isHeavy(); // Comic::isHeavy runs

Book *bp{&c};
bp->isheavy(); // Book::isHeavy runs

// cp, bp are all pointing to the begining of the Comic object
```
- **Static Dispatch**
	- the compiler looks at the declared type of the ptr, finds it to be a `Book` ptr, and makes the decision that `Book::isHeavy` will be called

- This default behavior is not what we typically want
 	- we'd like to use `Book` ptrs to point to any kind of `Book`, but still have the overriden methods run
	- use keyword `virtual`

`inheritance/example3`

```cpp

class Book{
	public:
	virtual bool isHeavy() const{...}
};

class Comic:public Book{
	public:
	bool isHeavy()const override{...}
};

Comic c{...,...,40,...};

Comic *cp{&c};
Book *bp{&c};
Book &rb{c}; // a reference of c


cp->isHeavy(); // Comic::isHeavy runs
bp->isHeavy(); // Comic::isHeavy runs as well
rb.isHeavy(); // Comic::isHeavy runs

```

- For a virtual method, the decision of which method to call is delayed till the program is running
	- the chosen method depends on the runtime type of the object pointed to it
	- this is called **Dynamic Dispatch**

- costs more than static dispatch


##### collections of `Book`s

```cpp
Book *collection[20];
// each element can point to a Book, Text or Comic

//...

for(int i = 0;i<20;i++){
	collection[i]->isHeavy();
}
```

- the `Book` array can accommodate different (multiple) types of `Book`s under one abstraction
	- this is called **Polymorphism** (n.多态性) 

```cpp
ostream &operator<<(ostream &out, const class &c){
	//...
}

```
- `ostream` is the superclass of `ostringstream`

- The same function can be used to write to `cout`, or to a file as `ostringostream`

### Destructor Revisited

`inheritance/example5`

```cpp
class X{
	int *x;
	public:
	X(int n): X{new int[n]} {}
		
	~X() {delete [] x;}
	//Virtual ~X() {delete [] x;}
}

class Y:public X{
	int *y;
	public:
	Y(int n, int m): X{n},y{new int[m]} {}
	~Y(){delete [] y;}
};

```

- `~Y()` does not need to delete `X`
 - **when a subclass object is destroyed, the superclass destructor is automatically called**

```cpp
X *myx = new Y(10,20);

delete myx; // leaks memory

```
- only `X`'s destructor is called
	- `Y::y` has leaked

- Solution
	- make `~X()` virtual

- Advice: if you expect your class to have subclasses, make destructor virtual even if it does nothing

If a class is not to have subclasses, you can insist on this by making the class `final`

```cpp
class Y final:public X{
	//...
};

```


```cpp
class Student{
	//...
	public:
	virtual int fees() = 0; // P.V. method
};

class coop:public Student{
	//...
	public:
	int fees() override{...}
};

class regular:public Student{
	//...
	public:
	int fees() override{...}
};_i


```
- we haven't implemented `Student::fees`

- we can indicate that the method has no implementation by making it **Pure Virtual**

- virtual
	- subclasses could replace behavior


- pure virtual
	- subclasses must provide behavior

- `Student` class is incomplete
	- cannot create instances (objects)
	- `Student s;` won't compile

- A class with at least one *pure virtual* method is called an **abstract class**

- Abstract classes are used to 
	- organize subclasses
	- place shared fields / methods
	- Polymorphism `Student *cs246[250];` `Student **cs246 = new Student[X];`

- a subclass of an abstract class is also abstract
	- **unless it implements all P.V. methods**

- A class with no *P.V. methods* is called *concrete class*


- in UML
	- Virtual/P.V. method - *italics*
	- abstract class - *italics*
	- static - __underline__
