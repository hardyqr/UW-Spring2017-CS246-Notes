# CS246
# Lecture 24: Casting


```cpp
Node n;
int *p =  (int *)&n;
```

#### `static_cast`
	- "sensible" casts
	- behavior is well defined

```cpp
void f(int x);
void f(double y);

double a = ...;
f(a); // calls f(double)

f(static_cast<int>(a));

Book *bp = new Text{...};
bp->getTopic(); // won't compile
// it only knows it's a Book, not know if it's a Text
Text *tp = static_cast<Text *>(bp);
tp->getTopic(); // compiles
```
- example of downcasting

- there must be an IS A relationship between the current type and the intended type

- unchecked cast
	- compiles is trusting you that `bp` does point to a `Text` object
	- if this is not true, behavior is undefined

#### `reinterpret_cast`

- essentially c-style casting
- rely on knowledge of internal workings of the compiler
- has "weired" behavior

```cpp
Student s;
Turtle *t = reinterpret_cast(Turtle *)&s;
t->draw();

```

#### `const_cast`

- can be used to remove const modifies


```cpp
const int *q = ...;
foo(q); // will not compile

foo(const_cast<int *>(q)) //compiles
```

- would work fine if `foo` does not actually modify `*p`
------

#### `dynamic_cast`

```cpp

```
-------

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
Comic &Comic::operator=(const Book &other) overrride{
	Comic &cother = dynamic_cast<const &>(other);
	Book::operator=(cother);
	hero = cother.here;
	return *this;
}
```

- if RHS is not a `Comic` ()in other words it is a mixed assignment), `operator=` will throw a `bad_cast` exception

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

- `p->isHeavy()`
	- use vptr to get to vtable
	- get the address of the method

- suppose `Comic` did not override `isItHeavy`
