#ifndef _ABSITER_H_
#define _ABSITER_H_
class AbstractIterator {  
// Could make this a template...
 public:
 //dereference operation
  virtual int &operator*() const = 0;
  //prefix ++
  virtual AbstractIterator &operator++() = 0;
  
  bool operator!=(const AbstractIterator &other) const;

  // pure virtual == operator. Subclasses must implement
  // otherwise abstract
  virtual bool operator==(const AbstractIterator &other) const = 0;
    
   //virtual destructor to prevent any memory leaks
   virtual ~AbstractIterator();
};
#endif
