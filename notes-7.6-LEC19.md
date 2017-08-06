# CS246
# Lecture 19: Design Patterns, the Big 5 (again!)

- Todo list for Iterator: 
	- `operator*`
	- `operator++`
	- `operator!=`

- create an abstract iterator class that defines the interface supported by iterators

```cpp
class AbstractIterator{
	public:
	virtual int &operator*() const = 0;
	virtual AbstractIterator &operator++() = 0;
	bool operator!=(const AbstractIterator other) const{
		return !(*this == other);
	}
	virtual bool operator==(const AbstractIterator &other) const = 0;
	virtual ~AbstractIterator();
};

class List{
	struct Node;
	//...
	public:
	class Iterator::public AbstractIterator{
		//...
	};
	//...
};

class set{
	...
	public:
	class Iterator::public AbstractIterator{
		//...
	};
};

template<typename Fn>

void foreach(AbstractIterator &lst; AbstarctIterator &end; Fn f){
	while(start != end){
		f(start);
		++start;
	}
}
```
## Revisiting Big 5
```cpp
class Book{
	...
	public:
	// has implemented Big 5
};

Text b{...,...,...,...};
Text c{b}; // copy constructor for Text
```
- calling the default constructor for Text
	- First calls Book's copt construtor
	- Then copies Text's field

```cpp
Text::Text(const Text &other):
	Book{other}, 
	topic{other.topic} {}
// only copy the Book field

// using superclass's copy constructor
```
- Assignment
	- First call Book's operator
	- then assign Text's field

```cpp
Text &Text::operator=(const Text &other){
	Book::operator=(other);
	topic = other.topic;
	return *this;
}
```
Move constructor:
```cpp
Text::Text(Text &&other):
	Book{other},
	topic{other.topic} {}
// wrong
// other is lvalue, so copy constructor is called

```

- `other` is an rvalue reference
- `other` is a constant pointer to an rvalue object

- However, `other` itself is an lvalue (it has address)

- So `Book{other}` calls the copy constructor instead of move comstructor

- Q: How do I treat `other` as an rvalue so that move constructor runs 
- A: A function does that!

- The C++ function `std::move` allows us to treat any lvalue as an rvalue

```cpp
Right version: Text::Text(Text &&other):
	Book{std::move(other)},
	topic{std::move(others.topic)} {}
	// because it is a string
```


- Move assignment operator (exactly the same)

```cpp
Text &Text::operator=(Text &&other){
	Book::operator=(std::move (other));
	topic = std::move(other.topic);
	return *this;
}

Text b1{"A", "Nomair", 200, "Physics"};
Text b2{"B", "Brad", 100, "CS"};
Book *pb1 = &b1;
Book *pb2 = &b2;
*pb1 = *pb2; // calling assignment operator on object (at compile time)
```

Here, the compiler looks at the declared type of `pb1`, so `Book::operator=` is called

- (problem: partial assignment)

- Now `b1` becomes `{"B", "Brad", 100, "Physics"}`

- Let's implement a virtual assginment operator

```cpp
class Book{
	//...
	public:
	virtual Book &operator=(const Book &other){
		//...
	}
};

class Text::Book{
	//...
	public:
	Book &operator=(const Text &other) override{
		//...
	}
};
// this will not compiler because the parameter name doesn't match

Text &Text::operator=(const Book &other) override{
	//...
}
// this is a a valid override (even though return types are different)
// this causing mixed assignment problem
```
- allowing the text to be assigned from a `Book`/`Comic`/`Text`

- How do we even assign the topic field??

- Let's restrict `Book`'s `operator=` to be called by restricting assigned through base class ptrs

- we could make `Book::operator=` protected

- here we even be able to assign a `Book` object to another object

- The problem is with our class hierachy

- the base class is not abstract

- Advice: keep base class abstract

```cpp
class AbstractBook{
	string title, author;
	int numPages;
	protected:
		AbstractBook &operator=(const AbstractBook &other) override;
	public:
		...
		virtual ~AbstractBook() = 0;
}

Text b1{...},{...};

AbstractBook *pb1 = &b1;
AbstractBook *pb2 = &b2;
*pb1 = *pb2; // won't compile
```

- solve partial/mixed problem by disallowing assignment through base class pointer

