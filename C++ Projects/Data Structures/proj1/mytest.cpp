#include "csrlist.h"

bool testEquality(CSR& a, CSR& b);
bool testEquality(CSRList& a, CSRList& b);

int main()
{
    cout << "***********************************\n"
            "*          CSR Tests!             *\n"
            "***********************************\n";
    cout << "Create a CSR object and check if it's empty" << endl;
    CSR aCSR;
    if (aCSR.empty())
    {
        cout << "The matrix is empty" << endl;
    }
    cout << "Attempt to dump content from the empty matrix";
    try {
        aCSR.dump();
    }
    catch(runtime_error &e) {
        cerr << e.what() << endl;
    }
    cout << "Populate the matrix and dump content" << endl;
    int array1[] = {10,20,0,0,0,0,0,30,0,40,0,0,0,0,50,60,70,0,0,0,0,0,0,80};
    aCSR.compress(4,6,array1,24);
    try {
        aCSR.dump();
    }
    catch(runtime_error &e) {
        cerr << e.what() << endl;
    }
    cout << "Make another matrix and fill it with content from the first one" << endl;
    CSR bCSR(aCSR);
    cout << "Compare the two matrices and dump content from both" << endl;
    if (testEquality(aCSR, bCSR)) cout << "The matrices are identical" << endl;
    else cout << "The matrices are different" << endl;
    cout << "Dumping Matrix 1" << endl;
    try {
        aCSR.dump();
    }
    catch(runtime_error &e) {
        cerr << e.what() << endl;
    }
    cout << "Dumping Matrix 2" << endl;
    try {
        bCSR.dump();
    }
    catch(runtime_error &e) {
        cerr << e.what() << endl;
    }
    cout << "Change the content of the first matrix then check if it's equal with the second matrix" << endl;
    int array2[] = {0,0,0,0,0,0,0,0,2,0,3,0,0,6,0,0};
    aCSR.compress(2, 8, array2, 16);
    if (testEquality(aCSR, bCSR)) cout << "The matrices are identical" << endl;
    else cout << "The matrices are different" << endl;
    cout << "Dump content of both matrices" << endl;
    cout << "Dumping Matrix 1" << endl;
    try {
        aCSR.dump();
    }
    catch(runtime_error &e) {
        cerr << e.what() << endl;
    }
    cout << "Dumping Matrix 2" << endl;
    try {
        bCSR.dump();
    }
    catch(runtime_error &e) {
        cerr << e.what() << endl;
    }
    int array3[] = {0,1,2,4,0,0,0,0,8};
    bCSR.compress(3, 3, array3, 9);
    cout << "Compare the matrices and dump content from both" << endl;
    if (testEquality(aCSR, bCSR)) cout << "The matrices are identical" << endl;
    else cout << "The matrices are different" << endl;
    cout << "Dumping Matrix 1" << endl;
    aCSR.dump();
    cout << "Dumping Matrix 2" << endl;
    bCSR.dump();
    cout << "Calculate the sparse ratios of each matrix" << endl;
    cout << "Matrix 1: " << aCSR.sparseRatio() << endl;
    cout << "Matrix 2: " << bCSR.sparseRatio() << endl << endl;


    cout << "***********************************\n"
            "*          CSRList Tests!         *\n"
            "***********************************\n";
    cout << "Create a list and check if it's empty" << endl;
    CSRList aCSRlist;
    if (aCSRlist.empty()) cout << "The list is empty" << endl;
    else cout << "The list is not empty" << endl;
    cout << "Insert two matrices in the list and dump it" << endl;
    aCSRlist.insertAtHead(bCSR);
    aCSRlist.insertAtHead(aCSR);
    cout << "Dumping List 1" << endl;
    try {
        aCSRlist.dump();
    }
    catch(runtime_error &e) {
        cerr << e.what() << endl;
    }
    cout << "Clear the list and check if it's empty" << endl;
    aCSRlist.clear();
    if (aCSRlist.empty()) cout << "The list is empty" << endl;
    else cout << "The list is not empty" << endl;
    cout << "Refill the list and check if it's empty" << endl;
    aCSRlist.insertAtHead(bCSR);
    aCSRlist.insertAtHead(aCSR);
    if (aCSRlist.empty()) cout << "The list is empty" << endl;
    else cout << "The list is not empty" << endl;
    cout << "Dump the list" << endl;
    cout << "Dumping List 1" << endl;
    try {
        aCSRlist.dump();
    }
    catch(runtime_error &e) {
        cerr << e.what() << endl;
    }
    cout << "Make a new list and copy content from the first list via assignment operator."
            " Then check if they are equal" << endl;
    CSRList bCSRlist;
    bCSRlist = aCSRlist;
    if (testEquality(aCSRlist, bCSRlist)) cout << "The lists are identical" << endl;
    else cout << "The lists are different" << endl;
    cout << "Make a new list and copy content from the second list via copy constructor. "
            "Then check if they are equal" << endl;
    CSRList cCSRlist(bCSRlist);
    if (testEquality(bCSRlist, cCSRlist))
    {
        cout << "The lists are identical" << endl;
    }
    else
    {
        cout << "The lists are different" << endl;
    }
    cout << "Dump all three lists" << endl;
    cout << "Dumping List 1" << endl;
    try {
        aCSRlist.dump();
    }
    catch (runtime_error &e) {
        cerr << e.what() << endl;
    }
    cout << "Dumping List 2" << endl;
    try {
        bCSRlist.dump();
    }
    catch (runtime_error &e) {
        cerr << e.what() << endl;
    }
    cout << "Dumping List 3" << endl;
    try {
        cCSRlist.dump();
    }
    catch (runtime_error &e) {
        cerr << e.what() << endl;
    }
    cout << "Print out a value from the first matrix" << endl;
    cout << aCSRlist.getAt(0, 1, 3) << endl;
    cout << "Calculate the average sparse ratio of the lists" << endl;
    cout << "List 1: " << aCSRlist.averageSparseRatio() << endl;
    cout << "List 2: " << bCSRlist.averageSparseRatio() << endl;
    return 0;
}

bool testEquality(CSR& a, CSR& b){
    return (a == b);
}
bool testEquality(CSRList& a, CSRList& b){
    return (a == b);
}