# CS246
# Lecture 6: More I/O, Short topics


### Read/write to files
`#include<ifstream>`
- `ifstream` -- read from files
- `ofstream` -- write to files
eg. read + output contents of a file, `readfile.cc`

```cpp
int main() {
	ifstream filename{"myfile.txt"};
	//type, varname, init value
	string s;
	while(filestream>>s) {
		cout<<s<<endl;
	}
}
```

- The file is opened as part of initialization.
- The file is automatically closed when filestream variable goes out of scope.

- You can use `ifstream` variable exactly like `cin` (`istream`).
- You can use `ofsteam` variable exactly like `cout` (`ostream`).

You can use strings as a source of data.

`#include<sstream>`
- `istringstream` -- read from strings
- `ostringstream` -- write to a string

```cpp
int main(){
	int num;
	while(true){
		cout<<"Enter a number"<<endl;
		string s;
		cin>>s;
		istringstream ss{s};
		if(ss>>num) break;
		cout<<"Not a number"<<endl;
	}
}

```

- if `ss>>num` fails (intput not numbers), we don't need `ss.clear()` as `ss` is a local variable that is created 

## String
In C, we use char arrays that are null terminated (`\0`). 
- explicitly manage array length

C++ lib provides string type
- automatically resize if needed

`string s = "hello";`
- automatically convert a char array to C++ string, MAGIC!



|LOL | C string | C++ string|
|----|----|---|
|equality | `strcmp` | `s1==s2`|
|comparisons | `strcmp` | `!=`,`<`,`<=`,`>`,`>=`|
|length | `strlen` | `s.length()`|
|exact characters | `s[0]`,`s[1]`... |`s[0]`,`s[1]`,...|
|contact | `strcat(s1,s2)` | `s1=s2+s2` `s3=s1+s2`|


## Default Arguments
```cpp
void printFile(string name="myfile.txt") { 
	// if no input, this default "myfile.txt" gets used.
	string s;
	ifstream filestream filestream{name};
	while(filestream>>s) {
		cout<<s<<endl;
	}
}
```

To call,
```cpp
printFile(); // uses default
printFile("file2.txt"); // use "file2.txt"
```
- cannot follow a parameter with a default value with a parameter that does not have a default value.
```cpp
void test1(int num = 0, string str); // not allowed
void test2(int num = 0, string str = "bla"); // legal
```
- If you're going to leave out on argument, it must be the last (or last n).
```cpp
test2(); //legal
test2(1);//legal
test2(1,"bla2")//legal
test2("bla")//illegal
test2(,"bla")//illegal
```
- 省略的总是得在后面

## Function overloading
In C++ we can have functions that have the same name as long as differs in the number / types of parameters.
- Just differing on the return type is not ok
```cpp
int neg(int a) {return -1;}
int neg(bool a) {return !a;}
```
which is not possible in C.

```cpp
int a = 2;
int b = 3;
a = a>>b; //right bit shift operator. legal in C.
```
`>>j<<` are overloaded operators. 
`a+b` ---overloading

## Struct
In C,
```cpp
struct Node {
	int data;
	struct Node *next;
	// node *next; // legal in C++
};

struct Node n = {1, NULL} // legal C++ syntax
Node n = {1, NULL} // can omit struct in C++
Node n{1,NULL} // legal as well
```























