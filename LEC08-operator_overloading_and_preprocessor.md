# CS246
# Lecture 8: Operator overloading, Preprocessor

- `<<, >>`
	- bitshift operators
	- I/O operators
- `+`

We can give meaning to C++ operators for user defined types.


```cpp
struct vec{
	int x,y;
};

vec v1{1,2};
vec v2{3,4};

vec add(vec v1, vec v2);

add(v1,v2);

// vec v3 = v1+v2
vec operator+(const vec &LHS, const vec &RHS){
	vec v{LHS.x+RHS.x,LHS.y+RHS.y};
	return v;
}

// vec v4 = 3*v3
vec operator*(int k, const vec &v){
	return {k*v.x, k*v.y};
}

// vec v5 = v4*5
vec operator(const vec &v, int k){
	return k*v; // * is already overloaded
}

// vec v6 = v1 + v2 + v3
// -> vtemp+v3
// -> vtemp2
```

## Overload I/O Operators
```cpp
struct Grade{
	int mark;
};

Grade g;
cout<<g; // cout<<g<<endl; // if you want a newline

operator<<(ostream &out,const Grade &g){
	out<<"your grade:"<<g.mark<<"%";
	return out;
}

Grade g;
cin >> g;

iostream &operator>>(istream &in, Grade &g){
	in >> g.mark;
	if(g.mark<0) g.mark=0;
	if(g.mark>100) g.mark=100;
	return in;
}
```


## Preprocessor

Before the compiler sees the code, the preprocessor runs.

- preprocessor edit the program text before compiler sees it

- `#` --- preprocessor, a directive

`#include<iostream>` <br>
- copy and paste 

`#include <...>`
- include file from standard library ( `/usr/share/c++`  `/sur/include/c++`)

```cpp
#include "..." // "..." means path
```

`g++14 -E -P file.cc`
- only runs the preprocessor

`#define VAR VALUE`
- search and replace all occurences of VAR with VALUE

using this is discouraged. use `const` instead.

### Conditional Completion
Suppose we want a variable of type `short int` but BBOS needs `long long int`.

(see `preprocess.cc`)

By changing OS to IOS or BBOS we can change the type of "public key".
Problem: the change was done manually.

The `-D` compile argument allows setting preprocessor variable from the command line.

syntax: `g++14 -E -P -DVAR=VALUE [files]`

eg: `g++14 -E -P -DOS=IOS preprocess.cc`

```cpp
#if OS == BBOS
	long long int key;
#elif OS == IOS
	short int key;
#endif
```

### Comments

```cpp
#if 0
	#if 0
	//...
	#endif
//...
#endif
```
the `#` comment syntax allows nesting

`#define FLAG`
- value of `FLAG` is the empty string


`#ifdef VAR // if VAR is defined`
`#ifndef VAR // if not`

(see `Debug.cc`)

### Separate Compilation
Interface files (header `files .h`)
- type definition, forward declarations<br>

Implementation file (`.cc`)<br>
- function implementation

NEVER compile header files

- `g++ *.cc`
- `g++ main.cc vec.cc`

I want to compile individual c++ files separately to produce tiny parts of the executable then merge these parts.


