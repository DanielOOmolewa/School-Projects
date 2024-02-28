//Title: CipherTool.cpp
//Author: Daniel Omolewa
//Date: 4/22/2020
//Description: This is part of the Cipher Project in CMSC 202 @ UMBC 
#include "CipherTool.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;


  CipherTool::CipherTool(string filename)
  {
    m_filename = filename; //Name of the file that is pass through
  }


  CipherTool::~CipherTool()
  {
    //Delete each cipher pointer in m_ciphers and set them to nullptr
    for (int i = 0; i < int(m_ciphers.size()); i++)
    {
      delete m_ciphers[i];
      m_ciphers[i] = nullptr;
    }
  }


  void CipherTool::LoadFile()
  {
    ifstream ciph; //Object ciph, for file handler
    string message = ""; //String variable, message, to be read in 
    bool isEncrypted = 0; //Bool variable, isEncrypted, to indicate whether message has been encrypted or decrypted
    char ciphType; //Char variable, ciphType, indicate the type of cypher
    int keyInt = 0; //Int variable, keyInt, indicate the shift for Caesar ciphers
    string keyString = ""; //String variable, keyString, indicate the keyword for Vigenere ciphers

    //Go through each line of the text file and read in specifc parts to make
    //a pointer object that is then added to m_cipher
    ciph.open(m_filename);
    //Read the first character of each line as ciphType
    while (ciph >> ciphType)
    {
      //Ignore DELEMITER while reading in the second and third part of the line as 
      //isEncrypted and message respectively 
      ciph.ignore(256, DELIMITER);
      ciph >> isEncrypted;
      ciph.ignore(256, DELIMITER);
      getline(ciph, message, DELIMITER);
      //If ciphType is 'o', assign a cipher pointer to a new Ong object 
      if (ciphType == 'o')
      {
        Cipher* ongCiph = new Ong(message, isEncrypted);
        m_ciphers.push_back(ongCiph);
      }
      //If ciphType is 'v', assign a cipher pointer to a new Vignere object
      else if (ciphType == 'v')
      {
        getline(ciph, keyString, '\n');
        Cipher* vigCiph = new Vigenere(message, isEncrypted, keyString);
        m_ciphers.push_back(vigCiph);
      }
      //if ciphType is 'c', assign a cipher pointer to new Caesar object
      else if (ciphType == 'c')
      { 
        ciph >> keyInt;
        ciph.ignore(256, '\n');
        Cipher* caeCiph = new Caesar(message, isEncrypted, keyInt);
        m_ciphers.push_back(caeCiph);
      }
    }
    ciph.close();
  }


  void CipherTool::DisplayCiphers()
  {
    int count = 1; //Int variable, count, to indicate the number of each cipher in the list

    //Traverse m_ciphers to display each cipher and update count
    cout << '\n';
    for (long unsigned i = 0; i < m_ciphers.size(); i++)
    {
      cout << count << ". " << *m_ciphers.at(i) << endl << endl;
      count++;
    }
  }


  void CipherTool::EncryptDecrypt(bool altered)
  {
    //Traverse m_ciphers to either encrypt or decrypt each cipher depending
    //on what altered is
    for (long unsigned i = 0; i < m_ciphers.size(); i++)
    {
      //If altered is 0, look for any cipher that has been decrypted or has not been
      //encrypted, then encrypt them. Indicate that each cipher has been encrypted
      if (altered == 0)
      {
        if (m_ciphers.at(i)->GetIsEncrypted() == altered)
        {
          m_ciphers.at(i)->Encrypt();
          m_ciphers.at(i)->ToggleEncrypted();
        }
      }
      //If altered is 1, look for any cipher that has been encrypted or has not been
      //decrypted, then decrypt them. Indicate that each cipher has been decrypted 
      else if (altered == 1)
      {
        if (m_ciphers.at(i)->GetIsEncrypted() == altered)
        {
          m_ciphers.at(i)->Decrypt();
          m_ciphers.at(i)->ToggleEncrypted();
        }
      }
    }
  }


  void CipherTool::Export()
  {
    ofstream file; //Object, file, for file handler
    string exportName = ""; //Name of the file that the user will be exporting
    int count = 0; //Number of ciphers that has been exported

    //Ask the user what they would like to call the export file. Then read in each
    //cipher into the file and update the count accordingly
    cout << "What would you like to call the export file" << endl;
    cin >> exportName;
    file.open(exportName);
    for (int i = 0; i < int(m_ciphers.size()); i++)
    {
      file << m_ciphers[i]->FormatOutput();
      count++;
    }
    file.close();
    //Dislay the number of ciphers exported
    if (count == 1)
    {
      cout << '\n';
      cout << count << " cipher exported" << endl << endl;
    }
    else if (count > 1)
    {
      cout << '\n';
      cout << count << " ciphers exported" << endl << endl;
    }
    
  }


  int CipherTool::Menu()
  {
    int choice = 0; //Indicate the user's choice
    //Keep displaying the menu until the user inputs a valid choice
    do
    {
      cout << "What would you like to do?" << endl;
      cout << "1. Display All Ciphers" << endl;
      cout << "2. Encrypt All Ciphers" << endl;
      cout << "3. Decrypt All Ciphers" << endl;
      cout << "4. Export All Ciphers" << endl;
      cout << "5. Quit" << endl;
      cin >> choice;
    } while (choice < 1 || choice > 5);
    return choice;
  }


  char CipherTool::GetType(Cipher* cipher)
  {
    char type = 0; //Indicate the cipher subtype
    //Set type to 'c', 'v', or 'o' according to what cipher->ToString() is and return it
    if (cipher->ToString() == "(Caesar)")
    {
      type = 'c';
    }
    if (cipher->ToString() == "(Vigenere)")
    {
      type = 'v';
    }
    if (cipher->ToString() == "(Ong)")
    {
      type = 'o';
    }
    return type;
  }


  void CipherTool::Start()
  {
    LoadFile();
    int menuChoice = Menu(); //Indicate the user choice

    //Until the user inputs 5, keep prompting them to either encrypt, decrypt, or export the ciphers
    while (menuChoice != 5)
    {
      //If the user enters 1, display all the ciphers
      if (menuChoice == 1)
      {
        DisplayCiphers();
      }
      //If the user enters 2, encrypt all the ciphers
      else if (menuChoice == 2)
      {
        bool altered = 0; //Indicate that the file has been decrypted or has not been encrypted
        EncryptDecrypt(altered);
        cout << '\n';
        cout << "All ciphers have been encrypted" << endl << endl;
      }
      //If the user enters 3, decrypt all the ciphers
      else if (menuChoice == 3)
      {
        bool altered = 1; //Indicate that the file has been encrypted or has not been decrypted
        EncryptDecrypt(altered);
        cout << '\n';
        cout << "All ciphers have been decrypted" << endl << endl;
      }
      //If the user enters 4, export all the ciphers
      else if (menuChoice == 4)
      {
        Export();
      }
      menuChoice = Menu();
    }
    //Once the user enters 5, thank them for using UMBC Encryption
    if (menuChoice == 5)
    {
      cout << '\n';
      cout << "Thanks for using UMBC Encryption" << endl << endl;
    }
  }