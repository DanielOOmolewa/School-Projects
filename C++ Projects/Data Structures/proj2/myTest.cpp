#include "bookTree.h"
using namespace std;

int main()
{
    cout << "***********************************\n"
            "*       WordTree Test!             *\n"
            "***********************************\n";
    auto wt = WordTree();
    cout << "Inserting 'a'" << endl;
    wt.insert("a");
    cout << "Inserting 'c'" << endl;
    wt.insert("c");
    cout << "Inserting 'c' again" << endl;
    wt.insert("c");
    cout << "Inserting 'b'" << endl;
    wt.insert("b");
    cout << "Dumping word tree" << endl;
    wt.dump();
    cout << endl;
    cout << "Finding the number of visited nodes to get to 'c'" << endl;
    int searchCount = wt.searchCount("c");
    cout << "Number of visited nodes: " << searchCount << endl;
    cout << "Finding the number of visited nodes to get to nonexistant 'd'" << endl;
    searchCount = wt.searchCount("d");
    cout << "Number of visited nodes: " << searchCount << endl;
    cout << "Checking if 'd' exists in the tree" << endl;
    Node* foundNode = wt.find("d");
    if (foundNode == nullptr)
    {
        cout << "Word does not exist" << endl;
    }
    else
    {
        string word = foundNode->getValue();
        cout << "Word found: " << word << endl;
    }
    cout << "Checking if 'c' exists in the tree" << endl;
    foundNode = wt.find("c");
    if (foundNode == nullptr)
    {
        cout << "Word does not exist" << endl;
    }
    else
    {
        string word = foundNode->getValue();
        cout << "Word found: " << word << endl;
    }
    cout << "Getting the root height" << endl;
    cout << "Root height: " << wt.getRootHeight() << endl;
    cout << "Getting the node height of 'b'" << endl;
    int nodeHeight = wt.getNodeHeight("b");
    cout << "Node height: " << nodeHeight << endl;


//    auto wt = WordTree();
//    string element;
//    cout << "Enter a new element: ";
//    cin >> element;
//    while (element != "STOP")
//    {
//        wt.insert(element);
//        wt.dump();
//        cout << endl << "Enter a new element: ";
//        cin >> element;
//    }
//    cout << "Root height: " << wt.getRootHeight() << endl;

    cout << "***********************************\n"
            "*       BookTree Test!             *\n"
            "***********************************\n";
    BookTree aTree;
    aTree.loadData("data.txt");
    cout << "Frequency of tinsmith in The Wonderful Wizard of Oz: " << endl;
    cout << "\t" << aTree.findFrequency("the wonderful wizard of oz","tinsmith") << endl << endl;
    cout << "Count of search operation for tinsmith in The Wonderful Wizard of Oz: " << endl;
    cout << "\t" << aTree.searchCount("the wonderful wizard of oz","tinsmith") << endl << endl;
    cout << "Height of the node containing tinsmith in The Wonderful Wizard of Oz: " << endl;
    cout << "\t" << aTree.getWordHeight("the wonderful wizard of oz","tinsmith") << endl << endl;
    cout << "Height of word tree for The Wonderful Wizard of Oz: " << endl;
    cout << "\t" << aTree.getTextTreeHeight("the wonderful wizard of oz") << endl << endl;
    cout << "Dumping the word tree for The Wonderful Wizard of Oz:" << endl << endl;
    aTree.dumpTitle("the wonderful wizard of oz");
    cout << endl;

    cout << "Frequency of non-existing word 'Daniel' in The Adventures of Tom Sawyer: " << endl;
    cout << "\t" << aTree.findFrequency("the adventures of tom sawyer", "Daniel") << endl;
    cout << "Count of search operation for non-existing word 'Daniel' in The Adventures of Tom Sawyer: " << endl;
    cout << "\t" << aTree.searchCount("the adventures of tom sawyer", "Daniel") << endl;
    cout << "Height of the node containing non-existing word 'Daniel' in The Adventures of Tom Sawyer: " << endl;
    cout << "\t" << aTree.getWordHeight("the adventures of tom sawyer", "Daniel") << endl;
    cout << "Frequency of he in The Adventures of Tom Sawyer: " << endl;
    cout << "\t" << aTree.findFrequency("the adventures of tom sawyer", "he") << endl;
    cout << "Count of search operation for he in The Adventures of Tom Sawyer: " << endl;
    cout << "\t" << aTree.searchCount("the adventures of tom sawyer", "he") << endl;
    cout << "Height of the node containing he in The Adventures of Tom Sawyer: " << endl;
    cout << "\t" << aTree.getWordHeight("the adventures of tom sawyer", "he") << endl;
    cout << "Height of word tree for The Adventures of Tom Sawyer: " << endl;
    cout << "\t" << aTree.getTextTreeHeight("the adventures of tom sawyer") << endl;
    cout << "Dumping the word tree for The Adventures of Tom Sawyer: " << endl;
    aTree.dumpTitle("the adventures of tom sawyer");
    cout << endl;

    cout << "Dumping each word tree of book tree" << endl;
    aTree.dump(true);
    return 0;
}