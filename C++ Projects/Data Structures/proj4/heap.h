// CMSC 341 - Fall 2020 - Project 4
// heap.h
// Templated, vector-based heap implementation

// To work with Heap, the template class T must provide the following:
//  (a) Default constructor
//  (b) priority function (unsigned priority())
//  (c) overloaded insertion operator
// To work with Heap *and* HashTable, it also needs:
//  (d) key function (string key())

#ifndef _HEAP_H
#define _HEAP_H

#include <iostream>
#include <vector>
#include <exception>
#include <utility>   // swap

using std::vector;
using std::endl;
using std::cout;
using std::swap;
using std::range_error;

// To work with Heap and HashTable, class T must provide the
// following:
//  (a) Default constructor
//  (b) priority function (unsigned priority())
//  (c) key function (string key())
//  (d) overloaded insertion operator

class Grader;

template <class T>
class Heap {

  friend Grader;
  
 public:
  // Constructor
  Heap();

  // Inline functions: size, empty, used 
  unsigned size() const { return _heap.size() - 1 ; }
  bool empty() const { return _heap.size() <= 1 ; }
  bool used() const { return _used ; }

  // Main heap operations: insert, read, remove
  void insert(const T& object);
  T readTop() const;
  void removeTop();

  // Dump the entire heap
  void dump() const;

  // Root node always has index 1
  static const unsigned ROOT = 1;
  
 private:
  vector<T> _heap;   // Vector-based heap
  bool _used;        // Has the heap ever been used?  Needed for
		     // linear probing.

  // *********************************************
  // Private helper function declarations go here!
  // *********************************************
  void heapifyUp(unsigned child, unsigned parent); //Helper for insert
  void heapifyDown(unsigned parent, unsigned lChild, unsigned rChild); //Helper for removeTop
};

// ***************************************
// Templated function definitions go here!
// ***************************************
template <class T>
Heap<T>::Heap(){
    _used = false;
    _heap.push_back(T("whatever", 0, "some dealer"));
}

template<class T>
void Heap<T>::insert(const T &object) {
    //If the heap is considered empty, simply push the object into the vector
    //and set _used to true
    if (empty())
    {
        _heap.push_back(object);
        _used = true;
    }
    //Otherwise, push the object into the vector and heapify it
    else
    {
        _heap.push_back(object);
        heapifyUp(size(), size()/2);
    }
}

template<class T>
void Heap<T>::heapifyUp(unsigned child, unsigned parent) {
    //If the size is two, swap out the objects in the if one has higher priority than the other
    if (size() == 2)
    {
        if (_heap.at(child).priority() > _heap.at(parent).priority())
        {
            swap(_heap.at(child), _heap.at(parent));
        }
    }
    //Otherwise,
    else
    {
        //Base case: If the parent has reached or exceeded past the ROOT,
        //return
        if (parent <= ROOT)
        {
            return;
        }
        //If the priority of the child is greater than that of the parent, then swap the objects of the parent
        //and the child. Then, set the child to the parent and call the recursive function on the new child
        //and its parent
        if (_heap.at(child).priority() > _heap.at(parent).priority())
        {
            swap(_heap.at(child), _heap.at(parent));
            child = parent;
            heapifyUp(child, parent / 2);
        }
        //Otherwise, just call the recursive function on the child and the next parent up
        else
        {
            heapifyUp(child, parent / 2);
        }
    }
}


template<class T>
T Heap<T>::readTop() const {
    //If heap is considered empty, throw an exception error
    if (_heap.size() <= 1)
    {
        throw range_error("Cannot read top of an empty heap");
    }
    //Otherwise, return the ROOT element
    else
    {
        return _heap.at(ROOT);
    }
}

template<class T>
void Heap<T>::removeTop() {
    //If heap is considered empty, throw an exception error
    if (_heap.size() <= 1)
    {
        throw range_error("Cannot remove top of an empty heap");
    }
    //Otherwise, set the ROOT to the last element of the heap and pop the heap. Then call heapifyDown()
    //on the new ROOT and its children
    else
    {
        _heap.at(ROOT) = _heap.at(size());
        _heap.pop_back();
        heapifyDown(ROOT, 2 * ROOT, 2 * ROOT + 1);
    }
}

template<class T>
void Heap<T>::heapifyDown(unsigned parent, unsigned lChild, unsigned rChild) {
    //Base case: If the index of the left child or the right child exceeds the size,
    //return
    if (lChild > size() || rChild > size())
    {
        return;
    }

    //If the index of the left child is within the bounds of the heap and its object's priority
    //is greater than the parent's priority, compare it to the priority of the right child.
    //If the priority of the right child is the biggest, swap its object with the parent's object,
    //set the parent to the right child, and call the recursive function on the new parent and its children.
    //Otherwise, swap the parent's object with the left child's object, set the parent to the left child
    //and call the recursive function on the new parent and its children
    if (lChild <= size() && _heap.at(parent).priority() < _heap.at(lChild).priority())
    {
        if (_heap.at(rChild).priority() < _heap.at(lChild).priority())
        {
            swap(_heap.at(parent), _heap.at(rChild));
            parent = rChild;
            heapifyDown(parent, 2 * parent, 2 * parent + 1);
        }
        swap(_heap.at(parent), _heap.at(lChild));
        parent = lChild;
        heapifyDown(parent, 2 * parent, 2 * parent + 1);
    }
    //If the index of the right child is within the bounds of the heap and its object's priority
    //is greater than the parent's priority, compare it to the priority of the left child.
    //If the priority of the left child is the biggest, swap its object with the parent's object,
    //set the parent to the left child, and call the recursive function on the new parent and its children.
    //Otherwise, swap the parent's object with the right child's object, set the parent to the right child
    //and call the recursive function on the new parent and its children
    if (rChild <= size() && _heap.at(parent).priority() < _heap.at(rChild).priority())
    {
        if (_heap.at(lChild).priority() < _heap.at(rChild).priority())
        {
            swap(_heap.at(parent), _heap.at(lChild));
            parent = lChild;
            heapifyDown(parent, 2 * parent, 2 * parent + 1);
        }
        swap(_heap.at(parent), _heap.at(rChild));
        parent = rChild;
        heapifyDown(parent, 2 * parent, 2 * parent + 1);
    }
}


template<class T>
void Heap<T>::dump() const {
    //Traverse through the heap and print out each object
    for (unsigned i = ROOT; i < _heap.size(); i++)
    {
        cout << _heap.at(i) << endl;
    }
}

#endif
