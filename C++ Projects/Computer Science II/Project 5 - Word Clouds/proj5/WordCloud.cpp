//Title: WordCloud.cpp
//Author: Daniel Omolewa
//Date: 5/6/2020
//Description: This is part of the Word Clouds Project in CMSC 202 @UMBC
#include "WordCloud.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <cmath>
#include <iterator>
using namespace std;

const char SPACE = ' ';

// Name: WordCloud (Default Constructor)
// Desc: Used to pass an essay (in input file) and generates word list and frequency
//       Dynamically allocates m_cloud. m_fileName would be hardcoded.
// Preconditions: Input file has correctly formatted input
// Postconditions: Returns list of items and their frequency (stored in LL)
WordCloud::WordCloud()
{
    m_cloud = new LL<string>;
    m_fileName = "proj5_test1.txt";

}

// Name: WordCloud (Overloaded Constructor) - Passed filename for input
// Desc: Used to pass an essay (in input file) and generates word list and frequency
//       Dynamically allocates m_cloud
// Preconditions: Input file has correctly formatted input
// Postconditions: Returns list of items and their frequency (stored in LL)
WordCloud::WordCloud(string fileName)
{
    m_cloud = new LL<string>;
    m_fileName = fileName;
}

// Name: ~WordCloud (Destructor)
// Desc: Deallocates m_cloud
// Preconditions: m_cloud has been dynamically allocated
// Postconditions: m_cloud is empty
WordCloud::~WordCloud()
{
    delete m_cloud;
    m_cloud = nullptr;
}

// Name: LoadFile()
// Desc: Loads a file (everything as a string although could be anything stringlike)
//       Each input file is an unknown length
// Preconditions: m_fileName is populated with good data
// Postconditions: m_cloud is populated
void WordCloud::LoadFile()
{
    ifstream cloud; //Object cloud, for file handler
    string word = ""; //String variable, word, that text file would be read in
    //Read in which word as the string variable, word, convert it to lower case
    //remove any beginning or ending punctuations and insert it into m_word
    cloud.open(m_fileName);
    while (cloud >> word)
    {
        for (string::iterator it = word.begin(); it != word.end(); it++)
        {
            *it = tolower(*it);
        }
        RemovePunct(word);
        m_cloud->Insert(word);
    }
    cloud.close();
}

// Name: RemovePunct (passed a string
// Desc: When passed a string, removes all non letter punctation on the beginning
//       or end of the string.
//       These are all ok: "don't" "inner-circle" but "candy," is bad
//       Is called during LoadFile
// Preconditions: Strings to be evaluated
// Postconditions: Punctuation is removed from string
void WordCloud::RemovePunct(string& word)
{
    //If the beginning or ending character in the word is a punctuation, remove it from the word
    if (ispunct(word[0]))
    {
        word.erase(0,1);
    }
    if (ispunct(word[word.length()-1]))
    {
        word.erase(word.length()-1,1);
    }    
}

// Name: RemoveCommon
// Desc: Iterates through m_cloud and removes all common words after they are read
// Preconditions: m_cloud is populated and EXCLUDE_LIST is populated
// Postconditions: m_cloud will have no words from EXCLUDE_LIST
void WordCloud::RemoveCommon()
{
    //Traverse m_cloud while also traversing EXCLUDE_LIST. If the "first" of the current node equals to an
    //element from EXCLUDE_LIST, remove the node
    for (vector<string>::const_iterator it = EXCLUDE_LIST.begin(); it != EXCLUDE_LIST.end(); it++)
    {
        for (int i = 0; i < m_cloud->GetSize(); i++)
        {
            if ((*m_cloud)[i].first == *it)
            {
                m_cloud->RemoveAt((*m_cloud)[i].first);
            }
        }
    }
}

// Name: RemoveSingles
// Desc: Asks the user if they would like to remove words with a frequency of 1
//       Should use the overloaded [] NOTE: Don't forget m_cloud is a pointer!
// Preconditions: m_cloud is populated
// Postconditions: m_cloud will have no words with a frequency of 1
void WordCloud::RemoveSingles()
{
    int wordsRemoved = 0; //Keeps track of the number of words that are removed

    //Traverse m_cloud and remove any word that has a frequency of 1. If a "single" is removed, make sure
    //to increment wordsRemoved and make sure to reset the index to 0
    for (int i = 0; i < m_cloud->GetSize(); i++)
    {   
        if ((*m_cloud)[i].second == 1)
        {
            m_cloud->RemoveAt((*m_cloud)[i].first);
            i = -1; 
            wordsRemoved++;
        }
    }
    //Display the number of words removed
    if (wordsRemoved == 1)
    {
        cout << wordsRemoved << " word removed." << endl;
    }
    else if (wordsRemoved > 1)
    {
        cout << wordsRemoved << " words removed." << endl;
    }
}

// Name: Export
// Desc: Iterates through m_cloud and exports to file "data:frequency"
// Preconditions: m_cloud is populated
// Postconditions: New export file is created with "data:frequency" one on each line
void WordCloud::Export()
{
    ofstream file; //Object, file, for file handler
    string exportName = ""; //Name of the file that the user will be exporting
    int count = 0; //Number of unique words that has been exported

    //Ask the user what they would like to call the export file. Then read in each
    //word into the file and update the count accordingly
    cout << "What would you like to call the export file?" << endl;
    cin >> exportName;
    file.open(exportName);
    for (int i = 0; i < m_cloud->GetSize(); i++)
    {
        file << (*m_cloud)[i].first << ":" << (*m_cloud)[i].second << endl;
        count++;
    }
    file.close();
    //Inform the user that the file has been exported
    cout << "Output to " << exportName << endl;
    //Display the number of unique words exported
    if (count == 1)
    {
        cout << count << " unique word exported" << endl;
    }
    else if (count > 1)
    {
        cout << count << " unique words exported" << endl;
    }
}

// Name: Start
// Desc: Calls LoadFile, RemoveCommon, Diplay, and Export 
// Preconditions: None (filename is available)
// Postconditions: None
void WordCloud::Start()
{
    //Populate m_cloud with words read in from the text file and remove
    //any common words
    LoadFile();
    RemoveCommon();
    
    string wantRemove = ""; //User's answer

    //Ask the user if they would like to remove all words with a frequency of 1
    //If the user wants to remove all "singles", run RemoveSingles(). Otherwise,
    //simply print that 0 words have been removed
    cout << "Would you like to remove all words with a frequency of 1?" << endl;
    cin >> wantRemove;
    if (wantRemove == "Yes" || wantRemove == "yes" || wantRemove == "y" || wantRemove == "Y")
    {
        RemoveSingles();
    }
    else if (wantRemove == "No" || wantRemove == "no" || wantRemove == "n" || wantRemove == "N")
    {
        cout << "0 words removed." << endl;
    }
    //Print out the list and run Export()
    m_cloud->Display();
    Export();
}
