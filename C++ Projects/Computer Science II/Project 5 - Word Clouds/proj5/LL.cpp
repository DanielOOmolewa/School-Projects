//Title: LL.cpp
//Author: Daniel Omolewa
//Date: 5/6/2020
//Description: This is part of the Word Clouds Project in CMSC 202 @UMBC
#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

// Templated Node class
// Normal node except that each node can hold a pair <T,int>
// where the first value is templated and the second value is the frequency
// (or quantity) of the first
// For example, if T was a string then it would hold string,int
template <class T>
class Node {
public:
  Node( const T& data ); //Node Constructor - Assume each quan
  pair<T,int>& GetData(); //Node Data Getter
  void SetData( const pair<T,int>& ); //Node Data Setter
  Node<T>* GetNext(); //Node m_next getter
  void SetNext( Node<T>* next ); //Node m_next setter
private:
  pair <T,int> m_data; //Holds templated data
  Node<T>* m_next; //Pointer to next node
};

template <class T>
Node<T>::Node( const T& data ) {
  m_data = make_pair(data,1);
  m_next = nullptr;
}

template <class T>
pair<T,int>& Node<T>::GetData() {
   return m_data;
}

template <class T>
void Node<T>::SetData( const pair<T,int>& data ) {
   m_data = data;
}

template <class T>
Node<T>* Node<T>::GetNext() {
   return m_next;
}

template <class T>
void Node<T>::SetNext( Node<T>* next ) {
   m_next = next;
}

//Templated Linked List class
template <class T>
class LL {
 public:
  // Name: LL() (Linked List) - Default Constructor
  // Desc: Used to build a new linked list
  // Preconditions: None
  // Postconditions: Creates a new linked list where m_head points to nullptr
  LL();

  // Name: ~LL() - Destructor
  // Desc: Used to destruct a LL
  // Preconditions: There is an existing LL with at least one node
  // Postconditions: A LL is deallocated (including dynamically allocated nodes)
  //                 to have no memory leaks!
 ~LL();

  // Name: LL (Copy Constructor)
  // Desc: Creates a copy of existing LL
  //       Requires a LL - REQUIRED to be implemented even if not used
  // Preconditions: Source LL exists
  // Postconditions: Copy of source LL
  LL(const LL&);

  // Name: operator= (Overloaded Assignment Operator)
  // Desc: Makes two LL of the same type have identical number of nodes and values
  // Preconditions: Requires two linked lists of the same templated type
  //                REQUIRED to be implemented even if not used
  // Postconditions: Two idenetical LL
  LL<T>& operator= (const LL&);

  // Name: Find
  // Desc: Iterates through LL and returns node if data found
  // Preconditions: LL Populated
  // Postconditions: Returns nullptr if not found OR Node pointer if found
  Node<T>* Find(const T& data);

  // Name: Insert
  // Desc: Either inserts a node to the linked list OR increments frequency of first
  //       Takes in data. If "first" (of pair) NOT in list, adds node
  //       If "first" (of pair) is already in list, increments quantity
  //       Inserts "first" in order with no duplicates
  // Preconditions: Requires a LL.
  // Postconditions: Node inserted in LL based on first value (or quantity incremented)
  void Insert(const T&);

  // Name: RemoveAt
  // Desc: Removes a node at a particular position based on data passed (matches first)
  // Preconditions: LL with at least one node. 
  // Postconditions: Removes first node with passed value (in first)
  void RemoveAt(const T&);

  // Name: Display
  // Desc: Display all nodes in linked list
  // Preconditions: Outputs the LL
  // Postconditions: Displays the pair in each node of LL 
  void Display();

  // Name: GetSize
  // Desc: Returns the size of the LL
  // Preconditions: Requires a LL
  // Postconditions: Returns m_size
  int GetSize();

  // Name: operator<< (Overloaded << operator)
  // Desc: Returns the ostream of the data in each node
  // Preconditions: Requires a LL
  // Postconditions: Returns an ostream with the data from each node on different line
  template <class U>
  friend ostream& operator<<(ostream& output, const LL<U>&);

  // Name: Overloaded [] operator
  // Desc: When passed an integer, returns the data at that location
  // Precondition: Existing LL
  // Postcondition: Returns pair from LL using []
  pair<T,int>& operator[] (int x);//Overloaded [] operator to pull data from LL
private:
  Node <T> *m_head; //Node pointer for the head
  int m_size; //Number of nodes in queue
};
//*****************************************************************
//Implement LL here

// Name: LL() (Linked List) - Default Constructor
// Desc: Used to build a new linked list
// Preconditions: None
// Postconditions: Creates a new linked list where m_head points to nullptr
template <class T>
LL<T>::LL()
{
  m_head = nullptr;
  m_size = 0;
}

// Name: ~LL() - Destructor
// Desc: Used to destruct a LL
// Preconditions: There is an existing LL with at least one node
// Postconditions: A LL is deallocated (including dynamically allocated nodes)
//                 to have no memory leaks!
template <class T>
LL<T>::~LL()
{
  Node<T>* prev = m_head; //Node pointer for previous node

  //Traverse the list and delete each node. After deleting all the nodes
  //set m_size to 0
  while (m_head != nullptr)
  {
    m_head = m_head->GetNext();
    delete prev;
    prev = m_head;
  }
  m_size = 0;
}

// Name: LL (Copy Constructor)
// Desc: Creates a copy of existing LL
//       Requires a LL - REQUIRED to be implemented even if not used
// Preconditions: Source LL exists
// Postconditions: Copy of source LL
template <class T>
LL<T>::LL(const LL &src)
{
  //Code from default constructor
  m_size = 0;
  m_head = nullptr;

  Node<T>* temp_src = src.m_head; //Node pointer that takes the current node from the source list

  //Traverse the source list and insert each word from the list into the list that's being copied to
  //Increase the frequency of each word if they are inserted more than once
  while (temp_src != nullptr)
  {
    for (int i = 0; i < temp_src->GetData().second; i++)
    {
      Insert(temp_src->GetData().first);
    }
    temp_src = temp_src->GetNext();
  }
}

// Name: operator= (Overloaded Assignment Operator)
// Desc: Makes two LL of the same type have identical number of nodes and values
// Preconditions: Requires two linked lists of the same templated type
//                REQUIRED to be implemented even if not used
// Postconditions: Two idenetical LL
template <class T>
LL<T> &LL<T>::operator=(const LL &src)
{
  if (this != &src)
  {
    Node<T>* prev = m_head; //Node pointer for previous node

    //Code from the destructor
    while (m_head != nullptr)
    {
      m_head = m_head->GetNext();
      delete prev;
      prev = m_head;
    }
    //Code from the destructor
    m_size = 0;
    m_head = nullptr;
    Node<T>* temp_src = src.m_head; //Node pointer that takes current node from the source list

    //Traverse the source list and insert each word from the list into the list that's being copied to
    //Increase the frequency of each word if they are inserted more than once
    while (temp_src != nullptr)
    {
      for (int i = 0; i < temp_src->GetData().second; i++)
      {
        Insert(temp_src->GetData().first);
      }
      temp_src = temp_src->GetNext();
    }
  }
  return *this;
}

//Name: Find
// Desc: Iterates through LL and returns node if data found
// Preconditions: LL Populated
// Postconditions: Returns nullptr if not found OR Node pointer if found
template <class T>
Node<T>* LL<T>::Find(const T &data)
{
  Node<T>* curr = m_head; //Node pointer for the current node
  Node<T>* foundNode = nullptr; //Node pointer to check if the passed in data exists

  //Traverse the list and check if the data exists in the list
  //If the data exists, set foundNode to the node that has the data
  //After checking if the data exists in the list, return foundNode
  while (curr != nullptr)
  {
    if (data == curr->GetData().first)
    {
      foundNode = curr;
    }
    curr = curr->GetNext();
  }
  return foundNode;
}

// Name: Insert
// Desc: Either inserts a node to the linked list OR increments frequency of first
//       Takes in data. If "first" (of pair) NOT in list, adds node
//       If "first" (of pair) is already in list, increments quantity
//       Inserts "first" in order with no duplicates
// Preconditions: Requires a LL.
// Postconditions: Node inserted in LL based on first value (or quantity incremented)
template <class T>
void LL<T>::Insert(const T& data)
{
  Node<T>* curr = m_head; //Node pointer for current node
  Node<T>* prev = m_head; //Node pointer for previous node
  Node<T>* foundNode = Find(data); //Indicates if data exists in the list

  //If the data already exists in the list, increment the frequency of the node with the data
  if (foundNode != nullptr)
  {
    foundNode->GetData().second++;
    return;
  }

  //If the word doesn't exist in the list, check to see where to add it in the list
  Node<T>* newNode = new Node<T>(data); //New node that takes in data
  //If the list is empty set m_head to newNode, set the node after it to nullptr, and increase the size 
  if (m_size == 0)
  {
    m_head = newNode;
    m_head->SetNext(nullptr);
    m_size++;
    return;
  }

  //If there's only one word in the list, check to see if the word comes before or after the word. After
  //the word has been included in the list increase the size
  if (m_size == 1)
  {
    //If the new word comes before the word alphabetically, make it the first word
    if (newNode->GetData().first < m_head->GetData().first)
    {
      m_head = newNode;
      m_head->SetNext(curr);
      curr->SetNext(nullptr);
      m_size++;
    }
    //Otherwise, in the case that it comes after the word, make it the second word 
    else if (newNode->GetData().first > m_head->GetData().first)
    {
      m_head->SetNext(newNode);
      newNode->SetNext(nullptr);
      m_size++;
    }
  }

  //In the case that there are more than one words in the list, check where the new word fits in
  else
  {
    //Traverse the list
    while (curr != nullptr)
    {
      //In the case that the last word of the list has been reached, check if the new word comes
      //before or after it alphabetically
      if (curr->GetNext() == nullptr)
      {
        //If the new word comes after the last word in the list alphabetically, set it at
        //the bottom of the list
        if (newNode->GetData().first > curr->GetData().first)
        {
          curr->SetNext(newNode);
          newNode->SetNext(nullptr);
          m_size++;
          return;
        }
        //Else, if the new word comes before the last word, set it as the second to the last word in the list
        else if (newNode->GetData().first < curr->GetData().first)
        {
          prev->SetNext(newNode);
          newNode->SetNext(curr);
          m_size++;
          return;
        }
      }
      //If the new word comes before the first word of the list alphabetically, set it on top of the list
      else if (newNode->GetData().first < m_head->GetData().first)
      {
        curr = m_head;
        m_head = newNode;
        newNode->SetNext(curr);
        m_size++;
        return;
      }
      //If the new word exists in between two words alphabetically, set in the middle of those words in the list
      else if (newNode->GetData().first > prev->GetData().first && newNode->GetData().first < curr->GetData().first)
      {
        prev->SetNext(newNode);
        newNode->SetNext(curr);
        m_size++;
        return;
      }
      prev = curr;
      curr = curr->GetNext();
    }
  }
}

// Name: RemoveAt
// Desc: Removes a node at a particular position based on data passed (matches first)
// Preconditions: LL with at least one node. 
// Postconditions: Removes first node with passed value (in first)
template <class T>
void LL<T>::RemoveAt(const T& data)
{
  Node<T>* curr = m_head; //Node pointer for current node
  Node<T>* prev = m_head; //Node pointer for previous node

  //If m_head has the data, set it to the next node after curr (which is set to m_head), delete curr,
  //and decrement m_size
  if (m_head->GetData().first == data)
  {
    m_head = curr->GetNext();
    delete curr;
    m_size--;
    return;
  }

  //Traverse the list and check if a node contains the data. If a node contains the data,
  //set the node after prev to the node after curr, delete curr, and decrement m_size 
  while (curr != nullptr)
  {
    if (curr->GetData().first == data)
    {
      prev->SetNext(curr->GetNext());
      delete curr;
      m_size--;
      return;
    }
    prev = curr;
    curr = curr->GetNext();
  }
}

// Name: Display
// Desc: Display all nodes in linked list
// Preconditions: Outputs the LL
// Postconditions: Displays the pair in each node of LL
template <class T>
void LL<T>::Display()
{
  Node<T>* curr = m_head; //Node pointer for current node

  //Traverse the list and print the word and its frequency. Once all the words have 
  //been printed, print "END" to indicate that the end of the list has been reached
  while (curr != nullptr)
  {
    cout << curr->GetData().first << ":" << curr->GetData().second << endl;
    curr = curr->GetNext();
  }
  cout << "END" << endl;
}


// Name: GetSize
// Desc: Returns the size of the LL
// Preconditions: Requires a LL
// Postconditions: Returns m_size
template <class T>
int LL<T>::GetSize()
{
  return m_size;
}

// Name: operator<< (Overloaded << operator)
// Desc: Returns the ostream of the data in each node
// Preconditions: Requires a LL
// Postconditions: Returns an ostream with the data from each node on different line
template <class U>
ostream& operator<<(ostream &output, const LL<U> &L)
{
  Node<U>* curr = L.m_head; //Node pointer for current node
  
  //Traverse the list and print the word and its frequency. Once all the words have 
  //been printed, print "END" to indicate that the end of the list has been reached
  while (curr != nullptr)
  {
    output << curr->GetData().first << ":" << curr->GetData().second << endl;
    curr = curr->GetNext();
  }
  return output;
}

// Name: Overloaded [] operator
// Desc: When passed an integer, returns the data at that location
// Precondition: Existing LL
// Postcondition: Returns pair from LL using []
template <class T>
pair<T,int> &LL<T>::operator[](int index)
{
  Node<T>* curr = m_head; //Node pointer for current node
  int count = 0; //Indicate the offset from the beginning element of the list

  //Traverse the list while incrementing count. If count equals the index, return
  //the pair of the node at the index
  while (curr != nullptr)
  {
    if (count == index)
    {
      return curr->GetData();
    }
    curr = curr->GetNext();
    count++;
  }
  
  //In the case where count doesn't equal index, return the pair of the first word 
  return m_head->GetData();
}

//****************************************************************
// To test just LL follow these instructions:
//   1.  Uncomment out int main below
//   2.  make LL
//   3.  ./LL (try valgrind too!)

/*
int main () {
  
  //Test 1 - Default Constructor and Push
  cout << "Test 1 - Default Constructor and Push Running" << endl;
  //Test Default Constructor
  LL <string>* newLL1 = new LL<string>();
  cout << "Testing" << endl;
  //Push 4 nodes into LL
  newLL1->Insert("candy");
 
  newLL1->Insert("cookies");
  newLL1->Insert("candy");
  
  newLL1->Insert("bananas");
  newLL1->Insert("dogs");
  newLL1->Insert("apples");
  newLL1->Insert("elephants");
  newLL1->Insert("barf");
  newLL1->Insert("candy");
 
  newLL1->Insert("cookies");
  newLL1->Insert("candy");
  newLL1->Insert("bananas");
  newLL1->Insert("dogs");
  newLL1->Insert("apples");
  newLL1->Insert("elephants");
  newLL1->Insert("barf");
  
  newLL1->Display();
  
  
  //delete newLL1;
   
  //Test 2 - Copy Constructor and Assignment Operator
  cout << "Test 2 - Copy Constructor and Assignment Operator Running" << endl;
  //Test Copy constructor
  LL <string>* newLL2 = new LL<string>(*newLL1);
  cout << "*******Original*********" << endl;
  newLL1->Display();
  cout << "newLL1 size: " << newLL1->GetSize() << endl;
  cout << "*******Copy*********" << endl;
  newLL2->Display();
  cout << "newLL2 size: " << newLL2->GetSize() << endl;
  //delete newLL1;
  delete newLL2;

  
  //Test Overloaded Assignment Operator
  LL <string>* newLL3 = new LL<string>();
  *newLL3 = *newLL1;
  cout << "*******Assignment*********" << endl;
  newLL3->Display();
  cout << "newLL3 size: " << newLL3->GetSize() << endl;
  cout << endl;
  
  
  //Test 3 - Test Display and Overloaded <<
  cout << "Test 3 - Display and Overloaded << Running" << endl;
  cout << "newLL1 Display Function" << endl;
  newLL1->Display();
  cout << "newLL1 size: " << newLL1->GetSize() << endl;
  cout << "newLL1 Overloaded" << endl;
  cout << *newLL1;
  cout << "RemoveAt(candy)" << endl;
  newLL1->RemoveAt("candy");
  cout << "newLL1 Display Function" << endl;
  newLL1->Display();
  cout << "newLL1 size: " << newLL1->GetSize() << endl;
  delete newLL1;
  delete newLL3;
  
  return 0;
  
}
*/

