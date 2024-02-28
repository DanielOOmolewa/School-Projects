#include "wordTree.h"

WordTree::~WordTree(){
    clearTree(_root);
}

void WordTree::updateHeight(Node *aNode) {
    //If the node is a nullptr, then just return
    if (aNode == nullptr)
    {
        return;
    }

    //If both of the children are null then set the height of the node to 0
    if (aNode->_left == nullptr && aNode->_right == nullptr)
    {
        aNode->_height = 0;
    }
    //If one of the children is null then set the node height to the
    //height of the other child + 1
    else if (aNode->_left == nullptr)
    {
        aNode->_height = aNode->_right->getHeight() + 1;
    }
    else if (aNode->_right == nullptr)
    {
        aNode->_height = aNode->_left->getHeight() + 1;
    }
    //Otherwise, if both are the children are not null then set the height to the max height
    //between the children + 1
    else
    {
        aNode->_height = maxHeight(aNode->_left->getHeight(), aNode->_right->getHeight()) + 1;
    }
}

int WordTree::maxHeight(int height1, int height2)
{
    return (height1 > height2) ? height1 : height2; //Returns the bigger number or one of them if they are the same
}

void WordTree::clearTree(Node* aNode){
    //Base case: if an empty child is found, go back to the parent node
    if (aNode == nullptr)
    {
        return;
    }
    //Check and delete the left subtree of the node
    clearTree(aNode->_left);
    //Check and delete the right subtree of the node
    clearTree(aNode->_right);
    //Once both subtrees have been checked and deleted, delete the node
    delete aNode;
}

void WordTree::inOrder(Node* aNode, std::ostream& ostr){
    /***********************************
     *      Do not modify
     * ********************************/
    if (aNode != nullptr){
        ostr << "[";
        inOrder(aNode->_left, ostr);
        ostr << aNode->_value << ":" << aNode->_count << ":" << aNode->_height;
        inOrder(aNode->_right, ostr);
        ostr << "]";
    }
}

Node* WordTree::find(Node* aNode, const string& element){
    //If element is found in the root, return the root
    if (element == _root->_value)
    {
        return _root;
    }
    //If the element is less than the value of the root,
    //recursively traverse through its left subtree. If
    //a null child is found return nullptr
    else if (element < aNode->_value)
    {
        if (aNode->_left != nullptr)
        {
            aNode = find(aNode->_left, element);
        }
        else
        {
            return nullptr;
        }
    }
    //If the element is greater than the value of the root,
    //recursively traverse through its right subtree. If
    //a null child is found return nullptr
    else if (element > aNode->_value)
    {
        if (aNode->_right != nullptr)
        {
            aNode = find(aNode->_right, element);
        }
        else
        {
            return nullptr;
        }
    }
    //If the node that contains the element is found return it
    return aNode;
}
Node* WordTree::find(const string& element){
    Node* foundNode = find(_root, element);
    return foundNode;
}

Node* WordTree::leftRotation(Node* aNode){
    Node* parent = aNode; //The original root
    Node* rChild = parent->_right; //The right child node of the original root
    Node* lGrandchild = rChild->_left; //The left child node of the right child of the original root

    //Set the left child node of the right child to the parent
    rChild->_left = parent;
    //Set the right child node of the parent to the left grandchild
    parent->_right = lGrandchild;
    //Update the heights of the parent and the right child
    updateHeight(parent);
    updateHeight(rChild);
    //Return the right child as the new root
    return rChild;
}

Node* WordTree::rightRotation(Node* aNode){
    Node* parent = aNode; //The original root
    Node* lChild = parent->_left; //The left child node of the original root
    Node* rGrandchild = lChild->_right; //The right child node of the the left child node of the original root

    //Set the right child node of the left child to the parent
    lChild->_right = parent;
    //Set the left child node of the parent to the right grandchild
    parent->_left = rGrandchild;
    //Update the heights of the parent and left child
    updateHeight(parent);
    updateHeight(lChild);
    //Return the left child as the new root
    return lChild;
}

int WordTree::checkBalance(Node* aNode){
    int heightDiff = 0; //The height difference between the children of the node

    //If the node is a nullptr, return 0
    if (aNode == nullptr)
    {
        return 0;
    }
    //If the node has no children, then the height difference will be 0
    else if (aNode->_left == nullptr && aNode->_right == nullptr)
    {
        heightDiff = 0;
    }
    //If the left child is a null child, plug in -1 for its height and subtract
    //the height of the right child from it to get the height difference
    else if (aNode->_left == nullptr)
    {
        heightDiff = -1 - aNode->_right->getHeight();
    }
    //If the right child is a null child, plug in -1 for its height and subtract
    //it from the height of the left child to get the height difference
    else if (aNode->_right == nullptr)
    {
        heightDiff = aNode->_left->getHeight() - -1;
    }
    //Otherwise, the height difference will be the difference between the heights
    //of the left and right children
    else
    {
        heightDiff = aNode->_left->getHeight() - aNode->_right->getHeight();
    }

    return heightDiff;
}

Node* WordTree::reBalance(Node* aNode){
    int heightDiff = checkBalance(aNode); //The height difference on the root
    Node* lChild = aNode->_left; //The left child of the root
    Node* rChild = aNode->_right; //The right child of the root


    //Left Left Case: There's a height difference of at least 2
    //and checkBalance on the left child returns 0 or a positive number (left-heavy).
    //Do a right rotation on the root
    if (heightDiff >= 2 && checkBalance(lChild) >= 0)
    {
        aNode = rightRotation(aNode);
    }
    //Left Right Case: There's a height difference of at least 2
    //and checkBalance on the left child returns a negative number (right-heavy).
    //Do a left rotation on the left child and then a right rotation
    //on the root
    else if (heightDiff >= 2 && checkBalance(lChild) < 0)
    {
        aNode->_left = leftRotation(aNode->_left);
        aNode = rightRotation(aNode);
    }
    //Right Right Case: There's a height difference of at most -2
    //and checkBalance on the right child returns 0 or a negative number (left-heavy).
    //Do a left rotation on the root
    else if (heightDiff <= -2 && checkBalance(rChild) <= 0)
    {
        aNode = leftRotation(aNode);
    }
    //Right Left Case: There's a height difference of at most -2
    //and checkBalance on the right child returns a positive number (right-heavy).
    //Do a right rotation on the right child and then a left rotation
    //on the root
    else if (heightDiff <= -2 && checkBalance(rChild) > 0)
    {
        aNode->_right = rightRotation(aNode->_right);
        aNode = leftRotation(aNode);
    }
    //Return either the new or old root
    return aNode;
}

void WordTree::insert(const string& element){
    insert(element, _root);
}
Node* WordTree::insert(const string& element, Node*& aNode){
    //If the root is empty, then insert the new node at the root.
    if (_root == nullptr)
    {
        Node* newNode = new Node(element);
        _root = newNode;
        _root->_count++;
        return aNode;

    }
    //If the element is less than the value of the root,
    //recursively traverse through its left subtree until
    //an empty child is found and insert the new node there.
    //Then update the height of the node and rebalance it
    else if (element < aNode->_value)
    {
        if (aNode->_left != nullptr)
        {
            insert(element, aNode->_left);
            updateHeight(aNode);
            aNode = reBalance(aNode);
            updateHeight(aNode);
        }
        else
        {
            Node* newNode = new Node(element);
            aNode->_left = newNode;
            aNode->_left->_count++;
            updateHeight(aNode);
            aNode = reBalance(aNode);
            updateHeight(aNode);
            return aNode;
        }
    }
    //If the element is less than the value of the root,
    //recursively traverse through its right subtree until
    //an empty child is found and insert the new node there.
    //Then update the height of the node and rebalance it
    else if (element > aNode->_value)
    {
        if (aNode->_right != nullptr)
        {
            insert(element, aNode->_right);
            updateHeight(aNode);
            aNode = reBalance(aNode);
            updateHeight(aNode);
        }
        else
        {
            Node* newNode = new Node(element);
            aNode->_right = newNode;
            aNode->_right->_count++;
            updateHeight(aNode);
            aNode = reBalance(aNode);
            updateHeight(aNode);
            return aNode;
        }
    }
    //If a child that contains the same element is found, simply increment
    //its count by 1 and update its height
    else
    {
        aNode->_count++;
        updateHeight(aNode);
    }
    return aNode;
}

void WordTree::dump(std::ostream& ostr){
    /***********************************
     *      Do not modify
     * ********************************/
    inOrder(_root, ostr);
}

int WordTree::searchCount(string word){
    int numNodes = 0; //Number of nodes visited to get to desired node
    numNodes = searchCountHelp(_root, word, numNodes);
    return numNodes;
}

int WordTree::searchCountHelp(Node* aNode, string word, int counter){
    //If the word is in the root, return the initialized counter
    if (word == _root->_value)
    {
        return counter;
    }
    //If the node that contains the word is located elsewhere in the tree,
    //each time you go deeper, do a recursive call with the counter added
    //by 1
    else if (word < aNode->_value)
    {
        if (aNode->_left != nullptr)
        {

            counter = searchCountHelp(aNode->_left, word, counter + 1);
        }
        else
        {
            return counter;
        }
    }
    else if (word > aNode->_value)
    {
        if (aNode->_right != nullptr)
        {

            counter = searchCountHelp(aNode->_right, word, counter + 1);
        }
        else
        {
            return counter;
        }
    }

    return counter;
}

int WordTree::getRootHeight(){
    //If the root is empty return -1
    if (_root == nullptr)
    {
        return -1;
    }
    //Otherwise return its height
    return _root->getHeight();
}

int WordTree::getNodeHeight(string word){
    return getNodeHeightHelp(_root, word);
}

int WordTree::getNodeHeightHelp(Node* aNode, string word){
    Node* wantedNode = find(aNode, word); //The node that contains the word
    //If the node doesn't exist, return -1
    if (wantedNode == nullptr)
    {
        return -1;
    }
    //If the node is found, return its height
    else
    {
        return wantedNode->_height;
    }
}

