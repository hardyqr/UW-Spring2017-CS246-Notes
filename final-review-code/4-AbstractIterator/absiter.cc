#include "absiter.h"

bool AbstractIterator::operator!=(const AbstractIterator &other) const { 
  return !(*this == other);  // implemented in terms of ==
}

AbstractIterator::~AbstractIterator(){}

  