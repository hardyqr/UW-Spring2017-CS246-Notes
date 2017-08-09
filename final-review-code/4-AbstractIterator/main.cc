#include <iostream>
#include "listiter.h"
using namespace std;
#include "absiter.h"
#include "setiter.h"

template <typename Fn>
  void foreach(AbstractIterator &start, AbstractIterator &end, Fn f) {
     while (start != end) {
        f(*start);
        ++start;
     }
  } //end function

void addFive(int &x){
  x = x+5;
}

int main() {
  List l;
  l.addToFront(1);
  l.addToFront(2);
  l.addToFront(3);
  l.addToFront(4);
  l.addToFront(5);

  for (auto it = l.begin(); it != l.end(); ++it) {
    cout << *it << endl;
  }
  cout << endl;

  List::Iterator temp = l.end();
  List::Iterator start = l.begin();
  foreach(start,temp,addFive);
  for (auto n : l) {
    cout << n << endl;
  }
  cout << endl;


  Set s;
  s.add(5);
  s.add(5);
  s.add(4);
  s.add(3);
  s.add(3);
  s.add(2);
  s.add(1);
  for (auto it = s.begin(); it != s.end(); ++it){
    cout << *it << endl;
  }
  cout << endl;
  
  Set::Iterator temp1 = s.end();
  Set::Iterator start1 = s.begin();
  foreach(start1,temp1,addFive);
  for (auto n : s) {
    cout << n << endl;
  }
  cout << endl;

  //Uncomment to see what happens if
  //the operands to operator== do not have
  //the same type
/*
  if(s.begin() == l.begin()){
    cout << "Bla" << endl;
  }
*/
} //end main
