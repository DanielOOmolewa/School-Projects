//Title: Ong.cpp
//Author: Daniel Omolewa
//Date: 4/22/2020
//Description: This is part of the Cipher Project in CMSC 202 @ UMBC
#include "Ong.h"
#include <istream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

const char VOWELS[10] = {'A', 'E', 'I', 'O', 'U', 'a', 'e', 'i', 'o', 'u'}; //List of vowels in the alphabet including capital and lower case
const int NUM_VOWELS = 10; //Number of total vowels in the alphabet
  Ong::Ong()
  {

  }


  Ong::Ong(string message, bool isEncrypted): Cipher(message, isEncrypted)
  {
    
  }


  Ong::~Ong()
  {

  }


  bool Ong::IsVowel(char suspect)
  {
    bool isVowel = 0; //Indicate if character is a vowel or not
    //Traverse through VOWELS to see if the suspected character matches any of the vowels. If the suspect matches to any
    //of the vowel set isVowel to 1. If not, let isVowel remain as 0. Return isVowel after interrogating the suspect 
    for (int i = 0; i < NUM_VOWELS; i++)
    {
      if (suspect == VOWELS[i])
      {
        isVowel = 1;
      }
    }
    return isVowel;
  }


  void Ong::Encrypt()
  { 
    string c_message = GetMessage(); //The cipher message
    int messSize = c_message.length(); //The length of the cipher message
    string encryptedMess = ""; //The encrypted message
    bool checkVowel = 0; //Indicate whether character is a vowel or not

    for (int i = 0; i < messSize; i++)
    {
      char currChar = c_message[i]; //The current character in the cipher message
      checkVowel = IsVowel(currChar);

      //If currChar is any of these characters, simply add currChar to encryptedMess
      if(c_message[i] == ' ' || c_message[i] == '\"' || c_message[i] == ',' 
      || c_message[i] == '.' || c_message[i] == '(' || c_message[i] == ')' || c_message[i] == '\'')
      {
        encryptedMess = encryptedMess + c_message[i];
      }
      //Otherwise check if currChar is a vowel
      //If currChar is not a vowel add "ongify" and add a hyphen to it before adding it to encryptedMess      
      else if (checkVowel == 0)
      {
        encryptedMess = encryptedMess + c_message[i] + "ong-";        
      }
      //If currChar is a vowel simply add a hyphen before adding it to encryptedMess
      else
      {
        encryptedMess = encryptedMess + c_message[i] + "-";
      }
      
    }
    SetMessage(encryptedMess);
  }


  void Ong::Decrypt()
  {
    string c_message = GetMessage(); //The cipher message
    int messSize = c_message.length(); //The length of the cipher message
    string decryptedMess = ""; //The decrypted message
    bool checkVowel = 0; //Indicate whether character is a vowel or not

    //Traverse the cipher message to remove all "ong"s and hyphens
    for (int i = 0; i < messSize; i++)
    {
      char currChar = c_message[i]; //The current character in the cipher message

      //If the current cipher character is any of these characters, simply add to decryptedMessage
      if (c_message[i] == ' ' || c_message[i] == '\"' || c_message[i] == ',' || c_message[i] == '.' 
      || c_message[i] == '(' || c_message[i] == ')' || c_message[i] == '\'')
      {
        decryptedMess = decryptedMess + c_message[i];
      }
      //If the current cipher character is a hyphen, set it to null
      else if (c_message[i] == '-')
      {
        c_message[i] = 0;
      } 
      //Otherwise, check if currChar is a vowel or not. If currChar is not a vowel add it to decryptedMess and skip 4 characters ahead
      //If currChar is a vowel, simply add it to decryptedMess
      else
      { 
          checkVowel = IsVowel(currChar);
          if (checkVowel == 0)
          {
            decryptedMess = decryptedMess + c_message[i];
            //Skip 3 indexes ahead. One more will be skipped when code is looped around
            i = i + 3; 
          }
          else if (checkVowel == 1)
          {
            decryptedMess = decryptedMess + c_message[i];
          }
      } 
    }
    SetMessage(decryptedMess);
  }


  string Ong::ToString()
  {
    //Return subtype
    return "(Ong)";
  }
  

  string Ong::FormatOutput()
  {
    stringstream output;
    output << 'o' << DELIMITER << GetIsEncrypted()
    << DELIMITER << GetMessage()
    << DELIMITER << endl;

    return output.str();
  }