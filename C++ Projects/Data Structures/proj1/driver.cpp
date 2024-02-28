// CMSC 341 - Fall 2020 - Project 1
#include "csrlist.h"

bool testEquality(CSR& a, CSR& b);
bool testEquality(CSRList& a, CSRList& b);

int main()
{
    try{
        CSR aCSR;
        int array1[] = {10,20,0,0,0,0,0,30,0,40,0,0,0,0,50,60,70,0,0,0,0,0,0,80};
        aCSR.compress(4,6,array1,24);//initialize object aCSR
        CSR bCSR(aCSR);//create bCSR using copy constructor
        CSR cCSR;
        int array2[] = {0,0,0,0,100,200,0,0,300};
        cCSR.compress(3,3,array2,9);//initialize object cCSR
        CSR dCSR(cCSR);//create dCSR using copy constructor

        CSRList aCSRList;//create aCSRList
        aCSRList.insertAtHead(aCSR);
        aCSRList.insertAtHead(cCSR);
        CSRList bCSRList;//create bCSRList
        bCSRList.insertAtHead(dCSR);
        bCSRList.insertAtHead(bCSR);

        cout << endl << "Dumping aCSRList:" << endl;
        aCSRList.dump();
        cout << endl << "Dumping bCSRList:" << endl;
        bCSRList.dump();
        
        if (testEquality(cCSR,dCSR)) cout << endl << "testEquality(cCSR,dCSR) passed!" << endl;
        else cout << endl << "testEquality(cCSR,dCSR) failed!" << endl;
        if (testEquality(aCSR,dCSR)) cout << endl << "testEquality(aCSR,dCSR) passed!" << endl;
        else cout << endl << "testEquality(aCSR,dCSR) failed!" << endl;

        if (testEquality(aCSRList,bCSRList)) cout << "testEquality(aCSRList,bCSRList)) passed!" << endl;
        else cout << endl << "testEquality(aCSRList,bCSRList) failed!" << endl;
        
        cout << endl << aCSRList.getAt(1,2,4) << endl;//returns the value 70

        cout << endl << aCSRList.getAt(5,2,2) << endl;//throws an exception
    }
    catch (exception &e){
        cout << e.what() << endl;
    }
    return 0;
}

bool testEquality(CSR& a, CSR& b){
    return (a == b);
}
bool testEquality(CSRList& a, CSRList& b){
    return (a == b);
}