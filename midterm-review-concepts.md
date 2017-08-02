

# covered topics, Nomair section

- Shell

- Linux File System

- Linux Commands Handout e.g. `cd`, `pwd`, `ls`, `echo`, `rm`

- Globbing patterns (glob n.通配符)

- `cat` 

- input/output redirection

- pipes `|`

## `egrep`

- `egrep .`  - any char.

- `egrep .*` - zero or more any char。

- `egrep .+` - one or more any char.

- `egrep .?` - zero or one any char

- `egrep ^.+$` - match strictly from begin to end: one or more char. 

## file permissions (`chmod`)

`chmod +x file.sh` before run


- Shell variables (`PATH`) 
	
- Shell Scripts 

- Command Line Argument to a script - `$#`, `$0`,`$1`

- `#`, `?`, `/dev/null`, `0`

- script functions

- if statements

- while loop

- for loop

- C++: Hello World


- compiling / executing C++ programs


- Stream Objects (`cin`,`cout`,`cerr`)

- I/O Operators (`<<`,`>>`)

## `cin.fail()`, `cin,eof()`
	see notes

- implicit conversion of a stream to bool

- `<<` and `>>` are  binary operators: must produce an expression

- `<<` and `>>` cascading

## `cin.ignore()`,`cin.clear()`

- `std::string`

## semantics of reading from `cin` 
read until a whitespace

## I/O Manipulators: e.g. hex, dec, showpoint, setprecision, boolalpha, header

- hex - `cout << hex;`
- go back to decimal - `cout <<dec;`

- stream abstraction for files: `ifstream`, `ofstream`

- stream abstraction for strings: `istringstream`, `ostringstream`

## converting string to an integer 

- `stoi`

- strings in C++

## string operations: concat, length, comparisons

- `s1+s2`

- `s1.length()` 

- `strcmp(s1,s2)`
	- returns `0` if succeed


- default arguments

- funtion overloading

- Lvalue references

- pass by reference

- pass by value **vs** passing a pointer **vs** pass by reference : pros and cons of each

## dynamic memory allocation: `new` and delete`

are all `new` memory heap allocated?

- operator overloading ,examples: `Vec`, `Grade`

- the C and C++ **preprocessor** (`#include`, `#define`, using `#define` for conditional compilation)

- seperate compilation

- C++ classes

- initializing objects

- constructors

- default constructor

- initialize consy and reference fields

- member initialization list (MIL)

## copy constructor

- a deep copy

- a constructor, do not return anything


## explicit keyword ???

## deconstructor

## copy assignment operator (`operator=`) 


- Rvalue references

- move constructor

- move assginment operator

- superficial knowledge of copy / move elision (elision n.元音省略)

## rule of 5


- member functions **vs** standalone functions

## array of abjects
- `Target **targets = new Target[10]; `

- seprate compilation of classes (`::` the scope resolution opeartor)

- const methods

- mutable keywords

## static keyword in C++
> When we declare a member of a class as static it means no matter how many objects of the class are created, there is only one copy of the static member.

- invariants

## encapsulation: class keyword
- `class` - fields default private
- `struct` - fields default public

- invariant example: `List` and `Node` class




# CS246 Review session
### June 20, 2017

## bash
- check number of arguments

- for each file in suite (`$1`)
	- run the program somehow
	- verify output is correct
	- print


```{r, engine='bash', #1}
#!/bin/nash

if [ $# -ne 2 ] ; then
	echo "wrong number of arguments"  1>&2 
	# 1>&2 means output to strerr
	exit 69 
fi


for file in $(cat "$1"); do
	if ![  -f $file ] ; then	
		touch $file.in
	# touch means create empty file test.in
	fi
	testout=$(mktemp)
	"$2" < $file.in > $testout
	if ! [ diff $test.out $testout &>/dev/null ] ; then
		echo "test failed: $test"
		echo "input"
		cat $testin
		echo "Expected:"
		cat $textexp
		echo "Actual:"
		cat $testout
	fi
done

```

## C++ #1

```cpp
#include <sstream>
#include <iostream>
#include <cstdlib>

using namespace std;

char tolower(char c){
	if('A' <=c && c <= 'Z'){
		return c + 'a' - 'A';
	} else {
		return c;
	}
}

int main(){
	string line;
	while(getline(cin, line)){
		string userid = "";
		string name;
		istringstream iss(line);
		while(iss >> name){
			userid += tolower(name[0]);
		}
		userid+=name.substr(1); // "hit" from "shit"
		line =line.substr(0,line.length() - name.length() - 1);
		cout << name << ";" << "(" << userid << ")" << endl;
	}
	return 0;
}

```


## C++ #2: Big 5

- copy constructor

-  copy assognment operator

- deconstructor

- move constructor

- move assginment operator

### deconstructor

```cpp
~Data(){
	delete [] arr;
}

```

### copy constructor

```cpp
Data(const Data &other):
	arr{(other.capacity == 0) ? nullptr : new int[other.capacity]},
	datalen{other.datalen},
	capacity{other.capacity} {
		for(int i ; i < datalen ; ++i ){
			arr[i] = other.arr[i];
		}
	}

//const and & are important
```

### move constructor

```cpp
Data(Data &&other):
	arr{other.array},
	datalen{other.datalen},
	capacity{other.capacity} {
		other.arr = nullptr;
	}
```

### copy assignment operator
```cpp
#include <utility>
Data &operator=(const Data &other){
	Data temp = other; // call copy constructor
	swap(arr, temp.arr);
	swap(datalen, temp.datalen);
	swap(capacity, temp.capacity);

	return *this;
	// temp deconstructed automatically after this
}
```


### move assignment operator
#### version 1.1, use `swap`
```cpp
Data &operator=(Data &&other){ //&& means other is about to be deleted
	swap(arr, other.arr);
	swap(datalen, other.datalen);
	swap(capacity, other.capacity);
	// if we don't use swap, we have to delete [] arr of the left hand side

	return *this;
}
```

### version 1.2, use `swap` the smart way
```cpp
Data &operator=(Data &&other){
	std::swap(*this, other);
	return *this;
}

```

#### version 2, not use `swap`

```cpp
Data &operator=(Data &&other){
	delete [] other.arr;
	arr = other.arr; // since it's a deep copy, we can just assign the address to arr directly
	datalen = other.datalen;
	capacity = other.capacity;
	other.arr = nullptr;
	other.datalen = 0; // optional
	other.capacity = 0; // optional
	return *this;
}
```


- what does `swap` do exactly?
	- it swaps everything from the RHS to the LHS
	- ptr to ptr 
	- value to value
