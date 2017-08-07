# cs246
# Tutorial 8

### Class Relationships

#### Composition
```cpp
class A{
	...
};

class B{
	A a; // composition
};
```

#### Aggregation
```cpp
class A{
	...
};

class B{
	A a; // composition or aggregation, why???
};
```

#### Inheritance

```cpp
class A{
	int a;
	public:
	A(int a): a{a} {}; //constructor
};

class B: public A{
	int b;
	public:
	B(int a, int b): A{a}, b{b}{};
};
```


- `B` *inherits* from `A`
- every instance of `B` has the fields and methods `A` has

### Encapsulation and Inheritance


### Polymorphism


### Arrays and Inheritance

### `override` and `virtual`

