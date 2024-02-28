#include <iostream>
#include <string>
#include "queue.h"

using namespace std;

int main()
{
//---------------------------------------------------
//              Default Constructor
//---------------------------------------------------
    cout << "Create a queue and check if its empty" << endl;
    Queue<char>* charQueue = new Queue<char>();
    if (charQueue->empty())
    {
        cout << "Queue is empty" << endl;
    }
    string name = "Daniel";
    cout << "Enqueue letters that make up the name " << name <<
    " and dump contents" << endl;
    for (int i = 0; i < name.length(); i++)
    {
        charQueue->enqueue(name[i]);
    }
    charQueue->dump();
    cout << "Get the head of the queue" << endl;
    cout << "Head of the queue: " << charQueue->head() << endl;
    cout << "Empty out the queue and check if it's empty" << endl;
    for (int i = 0; i < name.length(); i++)
    {
        charQueue->dequeue();
    }
    if (charQueue->empty())
    {
        cout << "Queue is empty" << endl;
    }
    cout << "Attempt to dequeue the now empty queue" << endl;
    try
    {
        charQueue->dequeue();

    }
    catch (const range_error& e)
    {
        cerr << e.what() << endl;
    }
    cout << "Attempt to get the head of the empty queue" << endl;
    try
    {
        charQueue->head();

    }
    catch (const range_error& e)
    {
        cerr << e.what() << endl;
    }
    cout << "Refill the queue and dump contents" << endl;
    for (int i = 0; i < name.length(); i++)
    {
        charQueue->enqueue(name[i]);
    }
    charQueue->dump();
//    delete charQueue;

//---------------------------------------------------
//              Copy Constructor
//---------------------------------------------------
    cout << "\nCopy Constructor" << endl;
    cout << "Create a second queue and fill it with contents of the the first queue via copy constructor" << endl;
    Queue<char>* charQueue2 = new Queue<char>(*charQueue);
    cout << "Dump contents of the first and second queues" << endl;
    cout << "First queue" << endl;
    charQueue->dump();
    cout << "Second queue" << endl;
    charQueue2->dump();
    cout << "Enqueue the character, O, in the first queue and dump contents of both first and second queues" << endl;
    charQueue->enqueue('O');
    cout << "First queue" << endl;
    charQueue->dump();
    cout << "Second queue" << endl;
    charQueue2->dump();
    cout << "Dequeue the head from the second queue and compare heads of first and second queues" << endl;
    charQueue2->dequeue();
    cout << "Head of first queue: " << charQueue->head() << endl;
    cout << "Head of second queue: " << charQueue2->head() << endl;
    cout << "Empty out the second queue and check if it's empty" << endl;
    for (int i = 0; i < name.length() - 1; i++)
    {
        charQueue2->dequeue();
    }
    if (charQueue2->empty())
    {
        cout << "Queue is empty" << endl;
    }
    cout << "Attempt to dequeue the now empty second queue" << endl;
    try
    {
        charQueue2->dequeue();

    }
    catch (const range_error& e)
    {
        cerr << e.what() << endl;
    }
    cout << "Attempt to get the head of the empty second queue" << endl;
    try
    {
        charQueue2->head();

    }
    catch (const range_error& e)
    {
        cerr << e.what() << endl;
    }
    cout << "The first queue has been emptied out and refilled with the original contents" << endl;
    for (int i = 0; i < name.length() + 1; i++)
    {
        charQueue->dequeue();
    }
    for (int i = 0; i < name.length(); i++)
    {
        charQueue->enqueue(name[i]);
    }
//    delete charQueue;
    delete charQueue2;

//---------------------------------------------------
//              Assignment Operator
//---------------------------------------------------
    cout << "\nAssignment Operator\n";
    cout << "Create a new queue and check if its empty" << endl;
    Queue<char>* charQueue3 = new Queue<char>();
    if (charQueue3->empty())
    {
        cout << "Queue is empty" << endl;
    }
    cout << "Fill the third queue with content of the first queue via assignment operator" << endl;
    *charQueue3 = *charQueue;
    cout << "Dump contents of first and third queues" << endl;
    cout << "First queue" << endl;
    charQueue->dump();
    cout << "Third queue" << endl;
    charQueue3->dump();
    cout << "Check for self assignment with the third queue" << endl;
    *charQueue3 = *charQueue3;
    cout << "Enqueue the character, O, in the first queue and dump contents of both first and third queues" << endl;
    charQueue->enqueue('O');
    cout << "First queue" << endl;
    charQueue->dump();
    cout << "Third queue" << endl;
    charQueue3->dump();
    cout << "Dequeue the head from the third queue and compare heads of first and third queues" << endl;
    charQueue3->dequeue();
    cout << "Head of first queue: " << charQueue->head() << endl;
    cout << "Head of third queue: " << charQueue3->head() << endl;
    cout << "Empty out the third queue and check if it's empty" << endl;
    for (int i = 0; i < name.length() - 1; i++)
    {
        charQueue3->dequeue();
    }
    if (charQueue3->empty())
    {
        cout << "Queue is empty" << endl;
    }
    try
    {
        charQueue3->dequeue();

    }
    catch (const range_error& e)
    {
        cerr << e.what() << endl;
    }
    cout << "Attempt to get the head of the empty third queue" << endl;
    try
    {
        charQueue3->head();

    }
    catch (const range_error& e)
    {
        cerr << e.what() << endl;
    }
    delete charQueue;
    delete charQueue3;

    cout << "\nAll the queues have been deleted\n";

    return 0;
}