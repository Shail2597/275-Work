#ifndef INTSET_H_
#define INTSET_H_
#include <iostream>

class intSet {
  int *elements;
  int elementCount;
  int currentCapacity;
  
  int indexOf(int val) const;
  void swap(intSet& otherSet);

 public:
  intSet(); 
  intSet(const intSet& otherSet); 
  intSet(intSet &&otherSet); 
  intSet &operator=(const intSet& otherSet); 
  intSet &operator=(intSet &&otherSet); 
  ~intSet();  
  
  intSet operator|(const intSet &otherSet) const; 
  intSet operator&(const intSet &otherSet) const; 
  bool operator==(const intSet &otherSet) const;  
  bool isSubset(const intSet &s) const;  
  bool contains(int val) const;     
  void add(int val);          
  void remove(int val);       
  friend std::ostream& operator<<(std::ostream& out, const intSet& otherSet); 
};


#endif
