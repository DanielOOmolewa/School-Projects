#include "bookTree.h"
BookTree::BookTree(){_root=nullptr;}

BookTree::~BookTree(){
	clear(_root);
}

BNode* BookTree::makeSplay(BNode* root, string key){
    //If the root is empty or the key is at the root, then
    //return the root
	if (root == nullptr || key == root->_key)
    {
	    return root;
    }
    //If either child of the root is empty, then return the root
	if (root->_left == nullptr || root->_right == nullptr)
    {
	    return root;
    }
    //Check the left subtree if the key is less than the root key
	else if (key < root->_key)
    {
	    //Zig Zig Case
        if (key < root->_left->_key)
        {
            root->_left->_left = makeSplay(root->_left->_left, key);
            root = rightRotate(root);
        }

        else if (key > root->_left->_key)
        {
            //Zig Zag Case
            root->_left->_right = makeSplay(root->_left->_right, key);
            if (root->_left->_right != nullptr)
            {
                root->_left = leftRotate(root->_left);
            }
        }
        return rightRotate(root);
    }
	//Check the right subtree if the key is greater than the root key
	else if (key > root->_key)
    {
	    //Zag Zag Case
        if (key > root->_right->_key)
        {
            root->_right->_right = makeSplay(root->_right->_right, key);
            root = leftRotate(root);
        }
        //Zag Zig Case
        else if (key < root->_right->_key)
        {
            root->_right->_left = makeSplay(root->_right->_left, key);
            if (root->_right->_left != nullptr)
            {
                root->_right = rightRotate(root->_right);
            }
        }
        return leftRotate(root);
    }
    return root;
}
BNode* BookTree::rightRotate(BNode* x){
    BNode* parent = x; //The original root
    BNode* lChild = parent->_left; //The left child node of the original root
    BNode* rGrandchild = lChild->_right; //The right child node of the left child of the original root

    //Set the right child node of the left child to the parent
    lChild->_right = parent;
    //Set the left child node of the parent to the right grandchild
    parent->_left = rGrandchild;
    //Return the right child as the new root
    return lChild;
}
BNode* BookTree::leftRotate(BNode* x){
    BNode* parent = x; //The original root
    BNode* rChild = parent->_right; //The right child node of the original root
    BNode* lGrandchild = rChild->_left; //The left child node of the right child of the original root

    //Set the left child node of the right child to the parent
    rChild->_left = parent;
    //Set the right child node of the parent to the left grandchild
    parent->_right = lGrandchild;
    //Return the right child as the new root
    return rChild;

}

bool BookTree::insert(string key, string author, string text){
    insertHelper(key, author, text, _root);
    return true;
}

bool BookTree::insertHelper(string key, string author, string text, BNode* node)
{
    //If the root is empty, then insert the new node at the root
    if (_root == nullptr)
    {
        BNode* newNode = new BNode(key, author, text);
        _root = newNode;
    }
    //If the element is less than the value of the root,
    //recursively traverse through its left subtree until
    //an empty child is found and insert the new node there.
    //After the new node is inserted, call the splay function
    else if (key < node->_key)
    {
        if (node->_left != nullptr)
        {
            insertHelper(key, author, text, node->_left);
        }
        else
        {
            BNode* newNode = new BNode(key, author, text);
            node->_left = newNode;
            _root = makeSplay(_root, key);
        }
    }
    //If the element is less than the value of the root,
    //recursively traverse through its right subtree until
    //an empty child is found and insert the new node there.
    //After the new node is inserted, call the splay function
    else if (key > node->_key)
    {
        if (node->_right != nullptr)
        {
            insertHelper(key, author, text, node->_right);
        }
        else
        {
            BNode* newNode = new BNode(key, author, text);
            node->_right = newNode;
            _root = makeSplay(_root, key);
        }
    }
    //If there's a duplicate, return false
    else
    {
        return false;
    }
}

void BookTree::clear(BNode* root){
    //Base case: if an empty child is found, go back to the parent node
    if (root == nullptr)
    {
        return;
    }
    //Check and delete the left subtree of the node
    clear(root->_left);
    //Check and delete the right subtree of the node
    clear(root->_right);
    //Once both subtrees have been checked and deleted, delete the node
    delete root;
}

void BookTree::inorderHelp(BNode* root, bool verbose) const{
     /***********************************
     *      Do not modify
     * ********************************/
    if (root != nullptr){
        if (verbose){
            cout << "(";
            inorderHelp( root->_left, verbose );
            cout << root->_key << ":" << root->_author;
			root->_tree.dump();
            inorderHelp( root->_right, verbose );
            cout << ")";
        }
        else{
            inorderHelp( root->_left, verbose );
            cout << root->_key;
            inorderHelp( root->_right, verbose );
        }
    }
}

void BookTree::dump(bool verbose) const{
     /***********************************
     *      Do not modify
     * ********************************/
    inorderHelp(_root, verbose);
}

int BookTree::findFrequency(string title, string word){
	_root = makeSplay(_root, title); //The new root
	//If the new foot is not empty, check the number of occurrences
	//of the word
	if (_root != nullptr)
    {
	    return _root->findFrequency(word);
    }
	//Otherwise, return 0
    return 0;
}

void BookTree::dumpTitle(string title){
	_root = makeSplay(_root, title); //The new root
	if (title == getRootKey())
    {
	    _root->_tree.dump();
    }
	else
    {
	    cout << "Title does not exist in the tree" << endl;
    }
}

int BookTree::searchCount(string title, string word){
	_root = makeSplay(_root, title); //The new root
	//If the title is found in the tree, then return
	// the search count of the word
	if (title == getRootKey())
    {
	    return _root->searchCount(word);
    }
	//Otherwise, return 0
    return 0;
}

int BookTree::getTextTreeHeight(string title){
    _root = makeSplay(_root, title); //The new root
    //If the title is found in the tree, return the height
    //of the AVL tree
    if (title == getRootKey())
    {
        return _root->getTextTreeHeight();
    }
    //Otherwise, return -1
    return -1;
}
int BookTree::getWordHeight(string title, string word){
    _root = makeSplay(_root, title); //The new root
    //If the title is found in the tree, then return
    //the height of the node that contains the word
    if (title == getRootKey())
    {
        return _root->getNodeHeight(word);
    }
    //Otherwise, return -1
    return -1;
}

string BookTree::getRootKey(){
     /***********************************
     *      Do not modify
     * ********************************/
	return _root->_key;
}

void BookTree::loadData(string dataFile){
     /***********************************
     *      This function is implemented
     *      to help you. You should't need
     *      to modify it.
     * ********************************/
	//read the entire file at once
	std::ifstream t(dataFile);
	std::stringstream buffer;
	buffer << t.rdbuf();

	//time to parse the information
	string titleDelimiter = "<==>";
	string itemsDeleimiter = "<=>";
	string s = buffer.str();
	size_t pos = 0;
	string token;
	while ((pos = s.find(titleDelimiter)) != string::npos) {
		token = s.substr(0, pos);//token is complete data for one title
		//get the title
		int tempPos = token.find(itemsDeleimiter);
		string title = token.substr(0,tempPos);
		//convert title to lower case
		std::transform (title.begin(), title.end(), title.begin(), ::tolower);
		token.erase(0, tempPos + itemsDeleimiter.length()+1);
		//get the author
		tempPos = token.find(itemsDeleimiter);
		string author = token.substr(0,tempPos);
		//convert author to lower case
		std::transform (author.begin(), author.end(), author.begin(), ::tolower);
		token.erase(0, tempPos + itemsDeleimiter.length()+1);
		//get the text
		string text = token.substr(0,token.length() - 1);//remove last newline
		//clean up the text, remove all non-alphanumeric characters
          for( std::string::iterator iter = text.begin() ; iter != text.end() ; ){
               if( !std::isalnum(*iter) && *iter != ' ') 
                    iter = text.erase(iter) ;
               else 
                    ++iter ; // not erased, increment iterator
          }
		//convert text to lower case
		std::transform (text.begin(), text.end(), text.begin(), ::tolower);
		
		insert(title,author,text);

		//move to info for the next title
		s.erase(0, pos + titleDelimiter.length()+1);
	}
}

