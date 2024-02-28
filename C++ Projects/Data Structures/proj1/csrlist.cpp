// CMSC 341 - Fall 2020 - Project 1
#include "csrlist.h"

CSRList::CSRList(){
    m_head = nullptr;
    m_size = 0;
}

CSRList::CSRList(const CSRList & rhs){
    m_head = nullptr;
    //If the source list is not empty, copy the size of the source list
    if (!rhs.empty())
    {
        m_size = rhs.m_size;
        //If the head of the source list is not a nullptr, copy it into the head of the copied list
        CSR* curr = rhs.m_head;
        if (curr) {
            CSR *temp = new CSR(*curr);
            m_head = temp;
            curr = curr->m_next;
        }
        CSR *last = m_head;
        //Traverse the source list and call each matrix into the copy list
        while (curr != nullptr) {
            CSR *temp = new CSR(*curr);
            last->m_next = temp;
            last = last->m_next;
            curr = curr->m_next;
        }
    }
}


CSRList::~CSRList(){
    CSR* curr = m_head; //The current matrix
    CSR* del; //The matrix that is to be deleted

    //Traverse the list and delete each matrix
    while (curr != nullptr)
    {
        del = curr;
        curr = curr->m_next;
        delete del;
    }
}

bool CSRList::empty() const{
    CSR* curr = m_head; //The current matrix
    //Traverse the list and see if each matrix is empty.
    //If any of the matrix is not empty, return false.
    //Otherwise return true
    while (curr != nullptr)
    {
        if (!curr->empty())
        {
            return false;
        }
        curr = curr->m_next;
    }
    return true;
}

void CSRList::insertAtHead(const CSR & matrix){
    CSR* temp = new CSR(matrix); //Copy of the source matrix

    //If the list is empty set the head to temp
    if (m_head == nullptr)
    {
        m_head = temp;
        m_head->m_next = nullptr;
    }
    //Otherwise make temp the new head while making sure the previous head as the next node;
    else
    {
        temp->m_next = m_head;
        m_head = temp;
    }
    m_size++;
}

void CSRList::clear(){
    CSR* curr = m_head; //The current matrix
    CSR* del; //That matrix that is to be deleted

    //Traverse the list and delete each matrix. After which, deallocate the head and set the size to 0
    while (curr != nullptr)
    {
        del = curr;
        curr = curr->m_next;
        delete del;
    }
    m_head = nullptr;
    m_size = 0;
}

int CSRList::getAt(int CSRIndex, int row, int col) const{
    CSR* curr = m_head; //The current matrix
    int value = 0; //That value that is to be returned

    //Traverse the list and if i equals to CSRIndex, call getAt() on the matrix at that index
    //and assign value to the result of getAt(). Then return the value
    for (int i = 0; i < m_size; i++)
    {
        if (i == CSRIndex)
        {
            value = curr->getAt(row, col);
            curr = curr->m_next;
        }
    }

    return value;
}

void CSRList::dump(){
    if (!empty()){
        CSR* temp = m_head;
        while (temp != nullptr){
            temp->dump();
            temp = temp->m_next;
        }
    }
    else
        throw runtime_error("Error: List is empty!");
}

bool CSRList::operator== (const CSRList & rhs) const{
    CSR* curr = m_head; //The current matrix
    CSR* other = rhs.m_head; //The current matrix from the source list

    //If the sizes aren't equal, return false
    if (m_size != rhs.m_size)
    {
        return false;
    }
    //If both of the lists are empty, return true
    else if (m_size == 0 && rhs.m_size == 0)
    {
       return true;
    }
    //Otherwise, traverse both lists and return false if there's any discrepencies found between
    //the matrices of the lists
    else
    {
        while (curr != nullptr && other != nullptr) {
            if (!(*curr == *other)) {
                return false;
            }
            curr = curr->m_next;
            other = other->m_next;
        }
    }
    //If there's no discrepency found, return true
    return true;
}

const CSRList& CSRList::operator=(const CSRList & rhs){
    if (this != &rhs) {
        CSR *curr = m_head; //The current matrix
        CSR *del; //The matrix that is to be deleted
        //Traverse the list and delete each matrix. Then, set the head to nullptr
        while (curr != nullptr) {
            del = curr;
            curr = curr->m_next;
            delete del;
        }
        m_head = nullptr;

        //Set the size of the copied list to the size of the source list
        m_size = rhs.m_size;
        //If the source list is not empty, check the head is not nullptr
        if (!rhs.empty())
        {
            curr = rhs.m_head;
            //If the head of the copied list is not nullptr, copy it into temp and set the head
            //of the copied list to temp, then move on to the next matrix
            if (curr != nullptr) {
                CSR *temp = new CSR(*curr);
                m_head = temp;
                curr = curr->m_next;
            }

            CSR *last = m_head;
            //Traverse the source list and call each matrix into the copy list
            while (curr != nullptr)
            {
                CSR *temp = new CSR(*curr);
                last->m_next = temp;
                last = last->m_next;
                curr = curr->m_next;
            }
        }
    }
    return *this;
}

int CSRList::averageSparseRatio(){
    CSR* curr = m_head; //The current matrix
    float averageSparRat = 0; //The value of the average sparse ratio
    float sum = 0; //The total sum of the sparse ratios of each matrix

    //Traverse the list and add up the sparse ratios of each non-empty matriz
    while (curr != nullptr)
    {
        if (!curr->empty())
        {
            sum += curr->sparseRatio();
        }
        curr = curr->m_next;
    }
    //Find and return the average sparse ratio
    averageSparRat = sum/m_size;
    return averageSparRat;
}

