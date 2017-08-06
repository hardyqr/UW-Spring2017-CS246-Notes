# CS246
# Lecture 24: Casting

[Type Conversion](https://en.wikibooks.org/wiki/C%2B%2B_Programming/Programming_Languages/C%2B%2B/Code/Statements/Variables/Type_Casting)

> casting is the explicit type conversion

> **Explicit type conversion (casting)** is the use of direct and specific notation in the source code to request a conversion or to specify a member from an overloaded class. There are cases where no automatic type conversion can occur or where the compiler is unsure about what type to convert to, those cases require explicit instructions from the programmer or will result in error.

```cpp
Node n;
int *p =  (int *)&n;
```

#### `static_cast`

- `static_cast<target type>(expression)`

- "sensible" casts
- behavior is well defined

```cpp
void f(int x);
void f(double y);

double a = ...
f(a); // calls f(double)

f(static_cast<int>(a)); // param being treated as an int

Book *bp = new Text{...};
bp->getTopic(); // won't compile
// it only knows it's a Book, not know if it's a Text
Text *tp = static_cast<Text *>(bp);
tp->getTopic(); // compiles
```
- example of downcasting

- there must be an "IS A" relationship between the current type and the intended type

- unchecked cast
	- compiles is trusting you that `bp` does point to a `Text` object
	- if this is not true, behavior is undefined

#### `reinterpret_cast`

- essentially C-style casting
- rely on knowledge of internal workings of the compiler
- has "weired" behavior

```cpp
Student s;
Turtle *t = reinterpret_cast(Turtle *)&s;
t->draw();
```
- this is completely compiler-dependent

#### `const_cast`

- can be used to remove const identifier from a particular variable

```cpp
const int *q = ...
foo(q); // will not compile

foo(const_cast<int *>(q)) //compiles
```

- would work fine if `foo` does not actually modify `*p`
- if modifies, the behavior would be undefined

#### `dynamic_cast`

> The `dynamic_cast` keyword is used to casts a datum from one pointer or reference of a polymorphic type to another, similar to `static_cast` but performing a type safety check at runtime to ensure the validity of the cast. Generally for the purpose of casting a pointer or reference up the inheritance chain (inheritance hierarchy) in a safe way, including performing so-called cross casts.


```cpp
vector <Book *> collection;
// suppose we want to print out all topics of Textbook (only)
int len = collection.size();
for(int i = 0; i < len ;i++){
	Book *bp = collection[i];
	
	// Text *tp = static_cast<Text *>(bp);
	// the compiler doesn't check

	Text *tp = dynamic_cast<Text *>(bp);
	// if *bp is a Textbook, then cast
	// if *bp isn't, set tp to nullptr

	if(tp){
		tp->getTopic();
	} else {
		cout << "Not Text" << endl;
	}
}
```
- requirement: can only use `dynamic_cast` if a class has at least one virtual function


- `static_pointer_cast` & `const_pointer_cast` & `dynamic_pointer_cast`
	- used to cast `shared_ptr`s to `shared_ptr`s

#### RTTI: Runtime type Information
```cpp
void whatIsIt(shared_ptr<Book> b){
	if(dynamic_pointers_cast<Text>(b))
		cout << "It's a Text" << endl;
	else if(dynamic_pointers_cast<Comic>(b))
		cout << "It's a Comic" << endl;
	else
		cout << "It's a Book" << endl;
}
```

### Dynamic cast with References
```cpp
Comic c{...};
Book &b = c;
//...
Comic &cr = dynamic_cast<Comic &>(b);
```

- if `b` is not a reference to a `Comic`, `bad_cast` exception is thrown

### Partial & Mixed Assignment Problem
```cpp
Book *bp1 = new Comic{...};
Book *bp2 = new Comic{...};
*bp1 = *bp2;
```
- partial assignment
- mixed assignment

Previous solution: Make base class abstract with a protected assignment operator

- make `operator=` virtual

```cpp
Comic &Comic::operator=(const Book &other) override{
	Comic &cother = dynamic_cast<const &>(other);
	Book::operator=(cother);
	hero = cother.hero;
	return *this;
}
```

- if RHS is not a `Comic` (in other words it is a mixed assignment), `operator=` will throw a `bad_cast` exception

```cpp
class Book{
	string title;
	string author;
	int numPages;
	public:
	virtual bool isItHeavy();
};

class Text: public Book{
	string topic;
	public:
	virtual bool isItHeavy() override;
};

```

![vptr&vtable](vptr2vtable.jpeg)

- `p->isHeavy()`
	- use vptr to get to vtable
	- get the address of the method

- suppose `Comic` did not override `isItHeavy`
