# CS246
# Lecture 22: Exception Safety

```cpp
void f(){
	MyClass *p = new MyClass;
	MyClass m;
	g();
	delete p;
}
```

- if `g()` throws an exception, then `f()` exits without having deleted `p`. memory leak.

- Exceptions are mean to be covered from
	- program should be in some consistant state
		- dangling pointers/class invariants
		- memory leaks	

- C++ Guarantee:
	- During stack unwinding, all stack allocated memory is reclaimed (dtors execute)


- For `f()`, `p` has leaked, `m` is reclaimed

- It makes sense for the program to not automatically delete pointers
	- pointers could be  a stack address
	- someone else might be owners

```cpp
void f(){
	MyClass *p = new MyClass;
	MyClass m;
	try{
		g();
	} catch(...){
		delete p;
		throw; // re-throw the exception out
	}
	delete p;
}

```

- Some languages have a "finally" clause/block that executes irrespective of normal normal as exceptions.

- C++ does not have this

- C++ stack unwinding guarantee is enough
	- maximize the use of stack allocated objects

- **RAII**: Resource Acquisition Is Initialization (**RAII Idiom**)

- Every resource should be wrapped within a stack allocated object whose job is to release the resource. 

- Reading from a file

```cpp
{
	ifstream file{"myfile.txt"};
	...
	// We don't have to run file.close() since it's stack allocated and will call dtor automatically when go out of scope
}

```

- The ctor for `ifstream` acquises the resource
	- file in the file system

- The dtor closes/releases the resource 

- Irrespective of normal control as exception, the dtor always runs




- we want to wrap heap allocated objects within an object that's on the stack

- C++ standard library provides a template class `std::unique_ptr`
	- create objects of type `unique_ptr` on the stack
	- contain a field that points to heap memory

- Dtor for `unique_ptr` always deletes the pointer field

- a stack allocated	`unique_ptr` can be treated as a ptr as it overloads `operator*` & `operator->`

```cpp
void f(){
	std::unique_ptr<MyClass> p{new MyClass};
	// allocate
	// auto p = std::make_unique<MyClass>();
	MyClass m;
	g();
}
```

- Irrespective of how we return from `f()`, dtor for `p` always runs
	- deletes the heap allocated `MyClass` object

- `c++/13-unique_ptr`

- the `bp` is stack allocated, but `MyClass` it points to is heap allocated


#### Copying vs Moving unique ptrs

```cpp
class c{...};
unique_ptr<c> p{new c};
unique_ptr<c> q = p; //copy ctor
// won't compile
// copy ctor of unique_ptr is disabled

```

- cannot copy a `unique_ptr`
- cannot copy assign a `unique_ptr`

```cpp
template <typename T>
class unique_ptr{
	T *ptr; // points to heap allocated memory
	public:
	unique_ptr(T *p) : ptr{p} {}
	~unique_ptr(){delete ptr;}
	unique_ptr(const unique_ptr<T> &other) = delete;
	unique_ptr<T> &operator=(const unique_ptr<T> &other) = delete;
	unique_ptr(unique_ptr<T> &&other):
		ptr{other.ptr}{other.ptr = nullptr;}
	unique_ptr<T> &operator=(unique_ptr<T> &&other){
		using std::swap;
		swap(ptr, other.ptr);
		return *this;
	}

	T &operator*(){return *ptr;}
	T *operator->(){return ptr;}
};
```
//??? wtf are those
- `std::shared_ptr`
```cpp
void g(){
	auto p = make_shared<MyClass>();
	if(...){
		auto q = p; // copy ctor call
		...
	}
}
```

- when `g()` goes out of scope, dtor runs 
	- realize that it's not the "last" ptr to the heap allocated object so does not delete the object

- when `p` goes out of scope it finds the "reference count" to be zero
	- deallocates the object

- `shared_ptr`s maintain reference counts
	- deallocate objects when the reference count reaches 0

- Never let a dtor throw an exception

- if an except occurs and the stack is unwinding, dtors for all stack allocated objects will be called
	- if one of these throw an exception, the program termiantes

- Exception safety does not mean that the program doesn't use/throw exceptions

#### 3 levels of Exception Safety

- see Lecture 23
