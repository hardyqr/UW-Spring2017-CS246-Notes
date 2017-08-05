# CS246
# Lecture 14: Iterator Design Pattern, more encapsulation, a little UML


### Last time

```cpp
class List{
	struct Node;
	Node *theList = nullptr;
	public:
	void addToFront(int i);
	int ith(int i);// O(n)
	~List();
};
```


### Iterator Design Pattern

- create a calss (Iterator) that will manage access to `Node`s

- acts as an abstraction of a ptr into the linked list

#### Inspiration

```cpp
// arr is an int array
for(int *p = arr; p!=arr + array_size; ++p){
	//...
}
```

- The iterator class should support
	- `*` (dereference)
	- `++` operator
	- `!=` (==)

- begin and end method
```cpp
class List{
	struct Node;
	Node *theList = nullptr;
	public:
	class Iterator{
		Node *cur;
		public:
		explicit Iterator(Node *cur): cur{cur} {}
		// explicit keyword: prevent implicit conversion for single parameter constructors
		int &operator*() const{
			return cur->data;
		}
		Iterator &operator(){
			cur = cur->next;
			return *this;
		}
		bool operator==(const Iterator &other){
			return (cur == other.cur); // comparing addresses
		}
		bool operator!=(const Iterator &other){
			return !(*this == other)
		}
	}; // end Iterator class
	
	Iterator begin(){
		return Iterator{theList};
	}
	Iterator end(){
		return Iterator{nullptr};
	}
}; // end List class


// Client code
int main(){
	List lst;
	lst.addToFront(1);
	lst.addToFront(2);
	lst.addToFront(3); // 3->2->1

	for(List::Iterator it = lst.begin(); it != lst.end() ;++it){
		//would lst.end() is nullptr
		// loop goes on when lst does not point to a nullptr
		cout << *it << endl;
		int &temp = *it;
	}
}

```

auto keyword: automatic type deduction
`auto x = y; // define x to be the same type as y`


- C++ has built-in support for Iterator Design Pattern
	- range-based for loops
```cpp
// pass by value
// modifying a copy
for(auto n: lst){
	cout << n << endl;
}

// pass by reference
// modifying n
for(auto &n: lst){
	++n;
}
```

- A class C can use a range-based for loop if
	- it has methods `begin` and `end` that return iterator objects
	- the iterator class implements `*`, `++`, `!=`

### Encapsulation (contd.)

- Iterator constructor public
`auto it = Iterator{nullptr}`

- We'd like clients to use `begin` and `end`
	- let's make constructor for iterator private


```cpp
class List{
	//...
	public:
	class Iterator{
		Node *cur;
		explicit Iterator(Node *cur)//...
		public:
		//...
		friend class List;
	};

	Iterator begin(){
		return Iterator{theList};
	}
};

```
- make as few friends as possible
	- it breaks at encapsulation
	- if you change implementation, the friend might be effected

- Previous advice: keep fields private

If needed, provide accessors (getters) and mutators (setters)

```cpp
class Vec{
	int x,y;
	public:
	int getX() const {return x;}
	int getY() const {return y;}
	void setX(int x){this->x = x;}
	void setY(int y){this->y = y;}
};

```

- public accessors still allow changing implementation details

- public mutators still allow guaranteeing invariants since you wrote the implementation

### Scenario

- `Vec` fields are private 

- Suppose we do not want to make accessors

- want to implement output operator (`operator<<`)
	- recall we implement `operator<<` as a standalone function


```cpp
Class Vec{
	int x,y;
	public:
	//...
	firend ostream &operator<<(operator &out , const Vec &other);
};

ostream &operator<<(ostream &out, const vec &other){ // why "other" has to be a reference???
	out << other.x << other.y << endl;
}

```

## UML (Unified Modeling Language) System Modeling

- what classes are those

- what's the relation between classes

### A class in UML

|Vec|
|-x: Integer  -y: Integer|
|+getx: Integer +gety: Integer|

- `-` indicates private
- `+` indicates public

- it's good to be general in your design (Integer rather than `int`)
