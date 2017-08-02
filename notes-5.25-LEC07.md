# CS246
## LEC 07
## May 25, 2017

```cpp
// pass by value
void inc(int n) {
	n = n + 1
}

int x=5;
inc(x);
cout<<x<<endl;// prints 5

// pass by pointers 
void inc(int *n) {
	*n = *n + 1
}
int x = 5;
inc(&x);
cout<<x<<endl; // prints 6
```

```cpp
cin>>x;
// is equal to
operator>>(cin,x);
```

In C++, we have anothewr kind of "pointer-like" type: references.

Lvalue References

```cpp
int y = 10;
int &z = y; // z is a evalue reference to y
```

`z` acts like a constant pointer to `y`.

References are like constant pointers with automatic dereferencing.
```cpp
z = 15;
// no need to dereference, y gets updated to 15

int *p = &z;
// p gets the address of y

```

`z` always behaves like `y`. `z` is an alias for `y`.

Things you cannot do with references:

1. cannot leave references uninitialiezed. 
- a reference must be initialized to a Lvalue.

```cpp
int &z; //wrong
```

#### Lvalue vs Rvalue

> Anything that can appear on the left-hand side of an assignment expression is an lvalue.

l value is a storage location (sth to do with address) 
-	anything that can appear on LHS of an assignment 


Rvalue - acomputed value (temporary)

`x+y;`

- anything that can appear on the RHS of an assignment

```cpp
int &z=5;// wrong
int &z=x+y; // wrong
```

2. cannot create a pointer to a reference
- can create a reference  to a pointer

3. cannot create a reference to a reference
	
4. cannot create an array of references


We can pass by references.

```cpp
void inc(int &n) {
	n = n + 1;
}

int x = 5;
inc(x);

cout<<x<<endl; // prints 6

```

```cpp
cin>>x;
operator>>(cin,x);
// operator>> accepts the RHS of >> by reference
istream &operator>>(istream &in, int &n);
```

1st argument
- streams cannot be copied (pass by value is out)

why return an istream?
- for cascading to work

```cpp
cin>>x>>y;
// is equal to
operator>>(operator>>(cin,x),y);

```

Pass by value vs Pass by Reference
```cpp
struct ReallyBig {/*...*/};
int f(ReallyBig rb) {/*...*/};

ReallyBig db:/*...*/;

f(db); // expensive as a copy of db is made for function f

```


If we want to avoid the copy, the only option in C would be to pass the address 

```cpp
int g(ReallyBig *rb) {/*...*/};
```

C++ you have the added option to pass by reference 
```cpp
int h(ReallyBig &rb) {/*...*/};
```

```cpp
int i(const ReallyBig &rb) {/*...*/};
// pass by reference to const
// can only read it but not modify
```
- prevents the copy
- disallows updates to the value

```cpp
void f(int &n) {/*...*/};
void g(const int &n) {/*...*/};
f(5); // won't compile
f(x+y); // won't compile
g(5); // compiles
g(x+y); // compiles

```

## Dynamic (heap) Memory
In C,
```cpp
int *p = malloc(length * =sizeof(int));
//...
free(p);
```

valid in C++. Not allowed in CS246.

In C++, we use `new` and `delete`.
- `new` is a type aware

```cpp
struct Node {
	int data;
	Node *next;
};

Node *np = new Node;
```


- you get exactly the amount of memory needed by Node.
To free,

```cpp
delete np; \\ np must be a ptr returned by a call to new
```


```cpp
Node n;
Node *np=new Node;
// np is a ptr on stack
// n is on stack 
// new Node is on heap 
```

- heap memory lives on after a function returns
- forgetting to free/delete such memory leads to "memory leak"

```cpp
Node *np = new Npde[10];
// ...
delete [] np; // when deleting an array, add "[]"

```


```cpp
Node getMeNode(){
	Node n;
	return n;
}
// a copy of n is returned

Node *getMeNode() {
	Node n;
	return &n;
}
// results in a *dangling pointer* pointing to memory no longer yours
```

Never return a ptr/reference to stack allocated data.





```cpp
Node *getMeNode() {
	Node *np = new Node;
	return np;
}
```







