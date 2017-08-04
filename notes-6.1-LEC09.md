# CS246
# LEC09 Seperate Completion / C++ Classes

## Seperate Completion
`g++14 vector.cc` <br>
-compiler tries to compile, link and produce executable

We can use `-c` option to tell the compiler to only compile.

`g++14 -c main.cc`
`g++14 -c vector.cc`<br>

- we get `.o` object files after running above
- tiny pieces of the executable

`g++ vector.o main.o`
- link the pieces of the program
- produces executable

### Gloabal Variables
in `abc.h`

`extern global; // declare "global" only`

in `abc.cc`

`int global; // declaration of definition`

- never compile a `.h` file
- never include a `.cc` file

(see `preprocess/example2`)


###

	???


- Always put include guards in header files
- Never put `using namespace std;` in header files
- Always use `std::string`, `std::iostream`, etc. in a header file

## C++ Classes
Big OOP Idea:<br>
Let's put function inside a structure.

```cpp
struct student{
	int assns, mt, final;
	float grade(){
		retutn 0.4*assgns+0.2*mt*0.4*final;
	}
};

student billy {60,70,75};

cout<<billy.grade()<<endl;

```

A `class` is simply a struct that may contain function.
- `class` keyword later

- An instance of a class is called an object, ie. a value of type `student` is a `student` object.

- A function defined inside a class is called a **member function** or **method**. `grade()` is a **method**.

You can only call a method of class C using an object of class C.
```cpp
billy.grade(); // allowed
grade(); // not allowed 
```
### Functions vs Methods

A method has a hidden parameter called `this`. `this` is a pointer to the method on which the method was called.

- inside `grade`, `this` == `&billy`

```cpp
student jane{70,70,70};
jane.grade();

// inside grade, this == &jane 
```



```cpp
struct student{
	int assns,mt,final;
	float grade(){
		return this->assns*0.4+this->mt*0.2+this->final*0.4;
	}
};

```

### Initial Objects

`student billy{60,70,75};` is a C-style initialization.
- value must be constants

In C++ we can write methods called **constructors** to construct objects.

>A class **constructor** is a special member function of a class that is executed whenever we create new objects of that class.
>A constructor will have exact same name as the class and it does not have any return type at all, not even void. Constructors can be very useful for setting initial values for certain member variables.



```cpp
struct student{
	int assns,mt,final;
	float grade(){/*...*/}
	student (int assns, int mt, int final) {
		this->assns=assns;
		this->int=int;
		this->final=final;
	}
	// notice: it has no return type.
};

```
- If a 3-parameter-constructor has been implemented, it is called
- Otherwise this uses C style initialization 

```cpp
student billy = student{60,70,80};
student billy = student(60,70,80); // we are actually calling the student method inside method class
// they're equivalent.
```
#### Uniform Initialization
```cpp
int x = 5;
string s = "hello";

// int C++
int x(5);
string s("hello");
// are they allowed? it's not that clear.


// so we use the following
int x{5};
string s{"hello"};
// this is the recommended we of initializing variables in Modern C++

```
#### Heap allocating objects
```cpp
student *pBilly = new student{60,70,75};

delete pBilly;

```
### Advantages of Constructors

- They are functions (if ,for ,etc.)
- Overloading allowed 
- Default Value to parameters
- Sanity check / class invariant


```cpp
struct student{
	int assns,mt,final;
	float grade() {...};
	student(int assns=0, int mt=0, int final=0) {
		this->assns=assns<0?0:assns;
		this->mt=mt<0?0:mt;
		this->final=final<0?0:final;
	}
};

student billy{60,70,80};
student billy2{60,70}; // final = 0
student billy3{60}; // mt = final = 0
student billy4{}; // assns = mt = final = 0
student billy4; // equivalent to the previous one

student billy4(); // not allowed

```
