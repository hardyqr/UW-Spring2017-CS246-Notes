#ifndef _SET_H_
#define _SET_H_

#include "absiter.h"
class Set {
  int *array = new int[5];
  int size = 0;
  int capacity = 5;

  void resize(int newCapacity);
 public:
  class Iterator : public AbstractIterator {
    int *p;
    explicit Iterator(int *p);
   public:
    int &operator*() const override;
    Iterator &operator++() override;
    bool operator==(const AbstractIterator &other) const override;
    friend class Set;
  };

  Iterator begin();
  Iterator end();
  
  void add(int n);
  int ith(int i);
  ~Set();
};

#endif
