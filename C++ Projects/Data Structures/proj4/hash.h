// CMSC 341 - Fall 2020 - Project 4
// hash.h

// Templated, hash table implementation.  Each buckets is a heap.  A
// bucket contains objects with the same key values stored as a
// max-heap based on priority.  Collisions are resolved by linear
// probing.

// To work with Heap and HashTable, the template class T must provide
// the following:
//  (a) Default constructor
//  (b) priority function (unsigned priority())
//  (c) key function (string key())
//  (d) overloaded insertion operator

#ifndef _HASH_H
#define _HASH_H

#include <string>
#include "heap.h"

using std::string;

// Hash function typedef.  The hash function must return an 'unsigned
// int' value.  Reduction mod N is the responsiblity of the caller,
// not the hash function.
typedef unsigned (*hash_fn)(string);

class Grader;

template <class T>
class HashTable {

  friend Grader;
  
 public:
  // Constructor.  Requires table size and hash function.
  HashTable(unsigned size, hash_fn hash);

  // Destructor, copy, and assignment
  ~HashTable();
  HashTable(const HashTable<T>& ht);
  const HashTable<T>& operator=(const HashTable<T>& ht);

  // In-line functions
  
  // Table size; set by constructor
  unsigned tableSize() const { return _N; }
  // Number of entries in the table
  unsigned numEntries() const { return _n; }
  // Load factor
  float lambda() const { return ((float) _n) / _N; }

  // Main hash table functions
  
  // insert returns 'true' if successful; 'false' otherwise
  bool insert(const T& object);
  // getNext retrieves **and removes** the highest priority order of
  // type indicated by key.  It returns 'true' if successful; 'false'
  // otherwise.
  bool getNext(string key, T& obj);

  // Dump the entire hash table
  void dump() const;
  
 private:
  unsigned _N;       // hash table size
  unsigned _n;       // current number of entries
  hash_fn _hash;     // hash function
  Heap<T> *_table;   // array of heaps

  // ***********************************************
  // Private helper function declarations go here! *
  // ***********************************************
  
};

// *****************************************
// Templated function definitions go here! *
// *****************************************

template<class T>
HashTable<T>::HashTable(unsigned int size, hash_fn hash) {
    _N = size;
    _n = 0;
    _hash = hash;
    _table = new Heap<T>[_N]{Heap<T>()};
}

template<class T>
HashTable<T>::~HashTable() {
    delete[] _table;
}

template<class T>
HashTable<T>::HashTable(const HashTable<T> &ht) {
    //Set each member variable to those of the source hash table
    _N = ht._N;
    _n = ht._n;
    _hash = ht._hash;
    _table = new Heap<T>[_N]{Heap<T>()};
    Heap<T> *src_table = ht._table;
    //Traverse the size of the source hash table and copy each of its heap into the new hash table
    for (unsigned i = 0; i < _N; i++)
    {
        _table[i] = src_table[i];
    }

}

template<class T>
const HashTable<T> &HashTable<T>::operator=(const HashTable<T> &ht) {
    if (this != &ht)
    {
        //Delete the contents of the old hash table and set each member variable
        //to those of the source hash table
        delete[] _table;

        _N = ht._N;
        _n = ht._n;
        _hash = ht._hash;
        _table = new Heap<T>[_N]{Heap<T>()};
        Heap<T> *src_table = ht._table;
        //Traverse the size of the source hash table and copy each of its heap into the new hash table
        for (unsigned i = 0; i < _N; i++)
        {
            _table[i] = src_table[i];
        }
    }
    return *this;
}

template<class T>
bool HashTable<T>::insert(const T &object) {
    unsigned index = _hash(object.key()) % _N; //The hash index

    //If the heap at the index is not used and it's empty, simply insert the object and increment the
    //number of entries. Then, return true
    if (!_table[index].used() && _table[index].empty())
    {
        _table[index].insert(object);
        _n++;
        return true;
    }
    //If the heap at the index is used and not empty, do linear probing
    if (_table[index].used() && !_table[index].empty())
    {
        //Find the next available index to insert
        for (unsigned i = 0; i < _N; i++)
        {
            unsigned newIndex = (_hash(object.key()) + i) % _N; //The next available hash index

            //If the heap at the new index is not used and is empty, simply insert the object and increment
            //the number of entries. Then, return true
            if (!_table[newIndex].used() && _table[newIndex].empty())
            {
                _table[newIndex].insert(object);
                _n++;
                return true;
            }
            //If the heap at the new index is not empty and the key of the ROOT matches with the key
            //of the object, insert the object and increment the number of entries. Then, return true
            if (!_table[newIndex].empty() && _table[newIndex].readTop().key() == object.key())
            {
                _table[newIndex].insert(object);
                _n++;
                return true;
            }
        }
    }
    //If none of the above conditions are met, return false
    return false;
}

template<class T>
bool HashTable<T>::getNext(string key, T &obj) {
    unsigned index = _hash(key) % _N; //The hash index

    //If the heap at the index is used, not empty, and the key of the ROOT matches with the key,
    //read the top of the heap and remove it. Then, return true
    if (_table[index].used() && !_table[index].empty() && _table[index].readTop().key() == key)
    {
        obj = _table[index].readTop();
        _table[index].removeTop();
        return true;
    }
    //Otherwise, do linear probing
    for (unsigned i = 0; i < _N; i++)
    {
        unsigned newIndex = (_hash(key) + i) % _N; //The next available hash index

        //If the heap at the new index is used, not empty, and the key of the ROOT matches with the key,
        //read the top of the heap and remove it. Then, return true
        if (_table[newIndex].used() && !_table[newIndex].empty() && _table[newIndex].readTop().key() == key)
        {
            obj = _table[newIndex].readTop();
            _table[newIndex].removeTop();
            return true;
        }
    }
    //If none of the above conditions are met, return false
    return false;
}

template<class T>
void HashTable<T>::dump() const {
    //Traverse the hash table and print out each non-empty heap
    for (unsigned i = 0; i < _N; i++)
    {
        cout << "[" << i << "]" << endl;
        if (!_table[i].empty())
        {
            _table[i].dump();
        }
    }
}

#endif
