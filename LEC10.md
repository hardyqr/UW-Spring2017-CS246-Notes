# CS246
# LEC 10 Constructors

### Default Constructor
- every class comes with a default constructor which takes no parameter
	- this constructor calls default constructors on fields that are objects

	```cpp
	//eg.
	struct A {
		int x;
		student y;
		vec *v;
	};
	
	A myA; // calls dafault constructor
	// only y's default constructor is used
	// we should not read x or v until we have written to them

	vec v; // calls default constructor
	// since vec only has 2 int fields, default constructor does nothing
	```

Rule: the default constructor goes away as soon as you implement any constructor. 
```cpp
struct vec {
	int x,y;
	vec(int x, int y) {
		this->x = x;
		this->y = y;
	}
};

vec v; // not allowed 
vec v{1,2}; // works
```


### Fields that are constants / Reference
	
```cpp
int x; 
//...
struct myStruct {
	const int a = 5; // in class initialization
	int &y = x;
};

```

```cpp
struct student{
	const int id;
	//...
};

// while id needs to be a const, the value needs to be different for each student object

```

- Can we do it inside the constructor body?
	- no

Rule: fileds must already be constructed before constructor body runs.


### Steps for object creation

1. space is allocated (stack/heap)

2. fileds that are objects are default constructed

3. constructor body runs

#### Hijack step 2 using **Members Initialization List (MIL)**

```cpp
struct student {
	const int id;
	int assns, mt, final;
	student(int id_value, int assns_value, int mt_value, int final_value): 
		id{id_value},
		assns{assns_value},
		mt{mt_value},
		final{final_value}{}
};



```

- MIL is not just restricted to consts and references

- In the MIL, the thing outside each pair must be a field

- Fileds in the MIL are always initilalized in class declaration order

- Using the MIL can be more efficient than using the constructor body

 ```cpp
vec student{
	int x = 0;
	int y = 0;
	vec(int x_value, int y_value) : 
		x{x_value}, 
		y{y_value} {}
};
```

MIL takes priority over in class initialization.


### Copy constructor 

```cpp
student billy {60,70,80} ;
student bobby = billy; // same as the next line
student bobby{billy}; // same as the previous line
```

- `bobby` is a copy of `billy` object.

Copy constructor is used to construct an object as a copy of an existing object.
- **you get a copy constructor for free** // how do we understand **for free**?
	- field for field copy


- Every class comes with
	- default constructor 
	- copy constructor 
	- copy assignment operator
	- deconstructor
	- move constructor 
	- move assignment operator


A copy constructor always takes a single reference of the class as a parameter.

 ```cpp
struct student{
	int assns,mt,final;
	student(const student &other): 
		assns{other.assns}, 
		mt{other.mt}, 
		filnal{other.final} {}
};
// exactly what a free copy constructor does
```

```cpp
struct Node {
	int data;
	Node *next;
	Node(int data_value, Node *next): 
		data{data_value}, 
		next{next_value} {}
	
	Node(const Node &other): 
		data{other.data}, 
		next{other.next} {} 
	// free copy constructor 

};

Node *np = new Node{1, new Node{2, new Node{3,nullptr}}};

Node n = *np; // Node n{*np}

Node *m = new Node{*np};

// these three lines are all calling the free copy constructor 

```

- If we want three distinct lists with no shared nodes, we need a "deep copy"

- Must implement our own copy constructor 

- typically when we have ptrs to heap allocated memory, we will need a deep copy

```cpp
struct Node{
	//...
	Node(const Node &other): 
		data{other.data}, 
		next{other.next ? new Node{*other.next}:nullptr} {}
};

// this is a deep copy
```

Places where a copy constructor is called:

1) constructing an object as a copy of another's

2) when a function has a parameter that is passed by value

3) when sth is returned by value

- Parameter of a copy constructor must be a reference
	- cannot be pass by value
	
```cpp
struct Node{
	//...
	Node(int data_value): 
		data{data_value}, 
		next{nullptr} {}
};

Node n{4};
Node n = 4; // also legal 

void foo(Node n){ //... }
foo(4); // legal
```

Single parameter constructor defines implicit automatic conversions

`string str = "hello"` means there is a constructor in `string`
