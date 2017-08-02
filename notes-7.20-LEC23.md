# CS246
# Lecture 23: Exception Safety

- 3 levels of exception safety

- basic guarantee
	- if an exception occurs the program will be in a valid but unspecified state
	- no memory leaks
	- no dangling pointers
	- class invariants still hold

- string guarantee
	- if an exception is raised while executing function `f`, the state of the program will be as if `f` was never called

- no throw guarantt
	- the function nver throws an exception and always succeeds in achieving its goal

```cpp
class A{};

class B{};


class C{
	A a;
	B b;
	public:
	void f(){
		a.method1();
		b.method2();
		// method1 and method2 may throw
		// they have strong guarantee but not no throw guarantee
	}
};
```
- if `method1` throws an exception, then it's as if `method1` was never called (strong guarantee) -> its as if `f()` was never called (strong giarantee)

- if `method2` throws an exception, then it's as if `method2` was never called (strong guarantee), but we've lost the strong guarantee for `f()` since method1 might have changed the state

- Let's assume that `method1` and `method2` do not have what we call Non-local side effects.


- debug with local side effects


- Idea: let's call `method1` and `method2` on copies of `a` and `b`. If sth fails, we'll still have strong guaranteeas as we haven't changed the original `a` and `b`

- we do copy and swap

```cpp

void C::f(){
	// copy ctors
	A atemp = a;
	B btemp = b;
	atemp.method1();
	btemp.method2();
	a = atemp;
	b = btemp;
}

```

- The code does not provoide a strong guarantee because if the assignment of `b` fails, then `a` has changed and `b` has not

- we know pointer assignment never throws an exception since it's just a copy of address

- we wanna copy and swap, but we only do that to pointers
	- `pImpl`
	- smart ptrs


```cpp

struct CImpl{
	A a;
	B b;
};


class C{
	unique_ptr<CInput> pIml;
	public:
	void f(){
		unique_ptr<CInput> temp{
			new CInput{*pImpl}}; // *pImpl is an object
		// auto temp - make_unique<CImpl>(*pImpl);
		temp->a.method1();
		temp->b.method2();
		std::swap(pImpl, temp);
		
	}
};
```

- we have *strong guarantee* on this

### Exception Safety & the STL

#### Vectors

- dynamic length "heap allocated" array

- this is an example of RAII

```cpp
{
	vector<MyClass> v;
	...
} // the dtor for v runs and deallocates the heap array (objects within the array destroyed first)
```

```cpp
vector<MyClass *> v;
```
- will not deallocate objects that the elements point to

	
```cpp
vector<Observer *> observers;
```
- when a subject is destroyed, it should not destroy its observers
- we have to manually delete the heap allocated memory
```cpp
for(auto &p : v) delete p;
```


- to get the final project smart pointer bonus, do the following

```cpp
vector<shared_ptr<MyClass>> v;
```


##### `emplace_back`

- `emplace_back` provides a strong guarantee

