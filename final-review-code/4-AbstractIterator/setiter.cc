#include "setiter.h"

Set::Iterator::Iterator(int *p): p{p} {}
int &Set::Iterator::operator*() const { return *p; }
Set::Iterator &Set::Iterator::operator++() {
  ++p;
  return *this;
}

//Override operator== requires RHS to be AbstractIterator
//Will lead to mixed assignment unless we restrict RHS to Set::Iterator
bool Set::Iterator::operator==(const AbstractIterator &other) const {
  //RHS must also be Set::Iterator
  const Set::Iterator &rhs = dynamic_cast<const Set::Iterator &>(other);
  return p == rhs.p;
}

Set::Iterator Set::begin() { return Iterator(array); }
Set::Iterator Set::end() {return Iterator(array+capacity); }

Set::~Set() { delete [] array; }

void Set::resize(int newCapacity){
  int *temp = new int[newCapacity];
  for(int i=0; i < capacity; ++i){
    temp[i] = array[i];
  }
  delete [] array;
  array = temp;
  capacity = newCapacity;
}

/*
 * The set will not contain duplicates
 */
void Set::add(int n) { 
  //check if this would create a duplicate
  for(int i = 0; i < size; ++i){
    if(array[i] == n) return;
  }

  //check if we need to resize
  if(size == capacity){
      resize(2*capacity);
  }

  //have space, add at next spot
  array[size]=n;
  ++size;
}

int Set::ith(int i) {
  return array[i];
}

