# CS246
# Tutotial 10

- Abstract Iterator

- Factory Pattern

- Template Method Pattern

## Abstract Iterator

- unified interface to iterate through a collection of objects

- solution: create an abstract iterator class to serve as the interface which defines the opearator of an iterator

- see tut code

// what's the purpose of using `explicit`???

## Factory Pattern

- create instances of subclass based on some crifteria which should be easily changed
- eg. probability, level of the game ...

- see `pizza` code

## Template Method Pattern



```cpp

class A{
	int f(){return g();}  // this->g()
	virtual g(){return 0;}
};

class B: public A{
	int g(){return 1;}
};

A *a = new B;
a->f(); // return 1

```
