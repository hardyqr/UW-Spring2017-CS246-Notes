# CS246
# Lecture 17: Templates, Exceptions

## Template

```cpp
class Stack{
	int size;
	int cap;
	int *contents;
	public:
	Stack(){...}
	void push(int x){...}
	int top(){...}
	void pop(){...}

};
```

- C++ Template class: class //???
	- parameterized on one or more types
```cpp
template <typename T>
class Stack{
	int size;
	int cap;
	T *contents;
	public:
	Stack(){...}
	void push(T x){...}
	int top(){...}
	void pop(){...}

};

Stack<int> sInts;
sInts.push(1);

Stack<Expression *> sExps;
sExps.push(...);
```

```cpp
class List{
	struct Node{
		int data;
		Node *next;
	};
	//...
};

template <typename T>
class List{
	struct Node{
		T data;
		Node *next;
	};
	Node *thelist = nullptr;
	public:
	class Iterator{
		Node *curr;
		explicit Iterator(...) {...}
		public:
		T &operator*(){...}
		//...
		friend class List<T>;
	};
	void addToFront(const T &t){...}
	T ith(int i){...}
};

List<int> l1;
l1.addToFront(10);

List<List<int>> l2;
l2.addToFront(l1);

for(List<int>::iterator it = l1.begin(); it != l1.end(); ++it){...}
```
- can replace `List<int>::iterator` with `auto`

### STL Library

- lib `vector` provides Dynamic length array

- `vector` is a template class that'll automatically adjust the capacity of the internal array

```cpp
#include <vector>

vector<int> vecs{3,4}; // creates [3,4]

vecs.emplace_back(5); // [3,4,5]

vecs.emplace_back(6); // [3,4,5,6]

// warning
// `{}` and `()` diffrent here
vector<int> vecs(3,4); // creates [4,4,4]

for(int i; i < vecs.size() ; i++){
	cout << vecs[i] << endl;
}


// can replace `vector<int>::iterator` with `auto`
for(vector<int>::iterator it = vecs.begin(); it != vecs.endl() ;++it){
	cout << *it << endl;
}


for(vector<int>::reverse_iterator it = vecs.rbegin(); it!=vecs.rend(); ++it){
	// rbegin is end
	// rend is the iterm before begin
	//...
}

vecs.pop_back(); // removes last element

auto it = vecs.erase(vecs.begin()); // removes the first element
// why return an iterator?
// because the previous iterator is removed

vecs.erase(vecs.begin()+3);


vecs.erase(vecs.end() - 1);
// end() is the next of the last element

vecs[i] ...; // unchecked
// program does not check that i is in range
// which means it's the programmer's job

vecs.at(i); // a checked method
// it'll check if i is in range
// throw exception if not in range
```

- notice that we'll always need an anchor the position of the beginning/end of the iterator list
- like we need `vecs.begin()`/`vecs.end()` in `erase`

## C++ Exceptions

- client code
```cpp
vector<int> vec;
//...

vec.at(i); //i is out of range
// this code knows that an error has occurred

 ```

 - in C
 	- use return value to indicate error
	- set global error variable (`errno`)
	- make programming awkward
	- programmers need to continuously check for errors

- in C++
	- when an error occurs, the code can raise/throw an exception
		- if an exception is thrown, the default behavior is that the program terminates

- if you don't want your program to terminate, you must handle/`catch` the exception

- `vector::at` throws `out_of_range` exception

```cpp
#include <stdexpect>

int main(){
	vector<int> vecs;
	try{
		vecs.at(10);
		cout << "Done try" << endl;
	} catch{
		cout << "Handled" << endl;
	}
	cout << "Done Main" << endl;
}

// it prints "Handled\nDone Main\n"
// "Done try" is not print
```
- for multiple catch, syntax is 
	- `try{}catch{}cathch{}`


- `exceptions/callchain.cc`

```cpp
void f(){
	cout << "start f" <<endl;
	throw out_of_range {"f threw"}; // call constructor for object `out_of_range`
	cout << "end f";
}

void g(){
	cout << "start g" <<endl;
	f();
	cout << "end g";
}

void h(){
	cout << "start h" <<endl;
	g();
	cout << "end h";
}

int main(){
	cout << "start" ;
	try{
		h();
	} catch(out_of_range){
		cout << "Caught";
	}
	cout << "Done Main";
}

// this prints 
// "start
// start h
// start g
// start f
// Caught
// Done Main"

```

- when an exception occurs, the call stack is popped repeatedly until a suitable `catch` is found

- this is called **catch unwinding**

- Error recovery can be done in stages

```cpp
try{
	//...
} catch(someExp e){
	// partial recovery
	throw someOtherExp {...};
	throw e;// OR throw // they have subtle difference?
}
```


