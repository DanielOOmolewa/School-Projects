// CMSC 341 - Fall 2020 - Project 3
// PQueue: an ER triage queue using a skew heap and function pointers

#include "pqueue.h"
using namespace std;
using std::cout;
using std::endl;
using std::domain_error;

PQueue::PQueue(prifn_t priFn) {
    priority = priFn;
    _size = 0;
    _heap = nullptr;
}

PQueue::~PQueue() {
    if (_size != 0)
    {
        clear();
    }
}


PQueue::PQueue(const PQueue& rhs) {
    //If the root of the source is not a nullptr, proceed with
    //copying over the priority and size. Then call the
    //copy helper function
    if (rhs._heap != nullptr)
    {
        clear();
        priority = rhs.priority;
        _size = rhs._size;
        copyHelper(rhs._heap);
    }
    //Otherwise, state that an empty queue cannot be copied
    else
    {
        cout << "Cannot copy an empty queue" << endl;
        return;
    }
}

void PQueue::copyHelper(Node *aNode) {
    //While doing a preorder traversal of the source queue,
    //get the patient of each node and insert it into the copy
    //queue
    if (aNode != nullptr)
    {
        insertPatient(aNode->getPatient());
        copyHelper(aNode->_left);
        copyHelper(aNode->_right);
    }
}

PQueue& PQueue::operator=(const PQueue& rhs) {

    if (this != &rhs)
    {
        if (rhs._heap != nullptr)
        {
            clear();
            priority = rhs.priority;
            _size = rhs._size;
            copyHelper(rhs._heap);
        }
        else
        {
            cout << "Cannot copy an empty queue" << endl;
        }
    }
    //Protection against self-assignment
    else
    {
        cout << "Cannot assign a queue to itself" << endl;
    }
    return *this;
}

void PQueue::insertPatient(const Patient& input) {

    //If the queue is empty, assign the heap to a newly
    //created node object made with input. Then, increment the size
    if (_heap == nullptr)
    {
        Node* newPatient = new Node(input);
        _heap = newPatient;
        _size++;
        return;
    }
    //Otherwise, create a new queue based on the priority,
    //call its insert function with the patient passed it,
    // and merge it with the current queue.
    // After that, increment the size
    else
    {
        PQueue singleQueue = PQueue(getPriorityFn());
        singleQueue.insertPatient(input);
        mergeWithQueue(singleQueue);
        _size++;
        return;
    }
}

Patient PQueue::getNextPatient() {
    if (_heap != nullptr)
    {
        Node* oldHeap = _heap; //The old heap
        //Set a Patient object to the patient of the old heap, then delete the old heap
        Patient topPatient = oldHeap->getPatient();
        delete oldHeap;
        //Then decrement the size and set the heap to the result
        //of the merger of the subtrees of the old heap
        //After that, return the patient of the old heap
        _heap = mergeWithQueueHelper(_heap->_left, _heap->_right);
        _size = _size - 1;
        return topPatient;

    }
    //If the root is empty, throw an exception
    else
    {
        throw domain_error("The heap is empty");
    }
}


void PQueue::mergeWithQueue(PQueue& rhs) {

  //If the priorities of the queues are different, throw an exception
  if (this->getPriorityFn() != rhs.getPriorityFn())
    {
        throw domain_error("Can't merge queues with different priorities");
    }
  //If the queues are the same, then print out a warning
  else if (this == &rhs)
  {
    cout << "You can't merge a queue with itself" << endl;
    return;
  }
  //Otherwise, pass the roots into the helper function to merge the queues
  else
  {
      _heap = mergeWithQueueHelper(_heap, rhs._heap);
  }
  //After merging the queues, empty out the rhs queue
    _size = _size + rhs._size;
    rhs._heap = nullptr;

}

Node* PQueue::mergeWithQueueHelper(Node* pt1, Node* pt2) {
    Node* temp; //Place holder for a node when swapping

    //Base case: If either node is a nullptr, return the other
    if (pt1 == nullptr)
    {
        return pt2;
    }
    else if (pt2 == nullptr)
    {
        return pt1;
    }
    else
    {
        //If the priority of the second node is greater than the priority
        //of the first, swap the nodes
         if (priority(pt2->getPatient()) < priority(pt1->getPatient()))
         {
             temp = pt1;
             pt1 = pt2;
             pt2 = temp;
         }
         //Swap the child nodes of pt1 then set the right child of pt1
         //to the result of the merger of the second node and the
         //right child of pt1
            temp = pt1->_left;
            pt1->_left = pt1->_right;
            pt1->_right = temp;
            pt1->_left = mergeWithQueueHelper(pt2, pt1->_left);
        }
    return pt1;
}

void PQueue::clear() {
    clearHelper(_heap);
    _size = 0;
}

void PQueue::clearHelper(Node* aNode) {
//    Node* temp = aNode;
    //Base case: if an empty child is found, go back to the parent node
    if (aNode == nullptr)
    {
        return;
    }
    //Check and delete the left subtree of the node
    clearHelper(aNode->_left);
    //Check and delete the right subtree of the node
    clearHelper(aNode->_right);
    //Once both subtrees have been checked and deleted, delete the node
    delete aNode;
}

int PQueue::numPatients() const {
  return _size;
}

void PQueue::printPatientQueue() const {
    this->printPatientQueueHelper(_heap);
}

void PQueue::printPatientQueueHelper(Node *aNode) const{
    //Do a preorder traversal of the heap at print out
    //the information of each patient
    if (aNode != nullptr)
    {
        cout << aNode->getPatient() << endl;
        printPatientQueueHelper(aNode->_left);
        printPatientQueueHelper(aNode->_right);
    }
}

prifn_t PQueue::getPriorityFn() const {
  return priority;
}

void PQueue::setPriorityFn(prifn_t priFn) {
  priority = priFn; //The new priority
  PQueue newQueue (priority); // The new queue based on the new priority

  //Insert each patient into the new queue and merge it with the old queue
  for (int i = 0; i < _size; i++)
  {
      newQueue.insertPatient(this->getNextPatient());
  }
  int tempSize = _size;
  this->mergeWithQueue(newQueue);
  _size = tempSize;

}

void PQueue::dump() const
{
    dumpHelper(_heap);
}

void PQueue::dumpHelper(Node *aNode) const{
    //Do an inorder traversal of the heap and print out the priority and the patient's name
    //of each node
    if (aNode != nullptr)
    {
        cout << "(";
        dumpHelper(aNode->_left);
        cout << priority(aNode->getPatient()) << ":" << aNode->getPatient().getPatient();
        dumpHelper(aNode->_right);
        cout << ")";
    }
}

ostream& operator<<(ostream& sout, const Patient& patient) {
  sout << "Patient: " << patient.getPatient() << ", triage: " << patient.getTriage()
       << ", temperature: " << patient.getTemperature() << ", oxygen: " << patient.getOxygen() << ", RR: "
       << patient.getRR() << ", HR: " << patient.getHR() << ", BP: " << patient.getBP();
  return sout;
}

ostream& operator<<(ostream& sout, const Node& node) {
  sout << node.getPatient();
  return sout;
}


