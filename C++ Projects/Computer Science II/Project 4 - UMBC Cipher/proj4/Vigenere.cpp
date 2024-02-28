#include "Vigenere.h"
#include <istream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

const int UPPER_A = 'A';
const int UPPER_Z = 'Z';
const int LOWER_A = 'a';
const int LOWER_Z = 'z';
const int CASE_CHANGE = 32;
const int NUM_LETTERS = 26;

  Vigenere::Vigenere()
  {
    m_key = "test";
  }


  Vigenere::Vigenere(string message, bool isEncrypted, string key):Cipher(message, isEncrypted)
  {    
    m_key = key;
  }


  Vigenere::~Vigenere()
  {

  }


  void Vigenere::Encrypt()
  {
    string c_message = GetMessage();
    string keyword = "";
    string encryptedMess = "";
    int messSize = c_message.length();
    int keySize = m_key.length();
    int j = 0;

    for (int i = 0; i < messSize; i++)
    {
      if (j == keySize)
      {
        j = 0;
      }

      if(c_message[i] == ' ' || c_message[i] == '\"' || c_message[i] == ',' || c_message[i] == '.' || 
      c_message[i] == '(' || c_message[i] == ')' || c_message[i] == '\'')
      {
        keyword = keyword + c_message[i];
      }
      else
      {
        keyword = keyword + m_key[j];
        j++;
      }
    }

    for (int i = 0; i < messSize; i++)
    {
      if(c_message[i] == ' ' || c_message[i] == '\"' || c_message[i] == ',' || c_message[i] == '.' || 
      c_message[i] == '(' || c_message[i] == ')' || c_message[i] == '\'')
      {
        encryptedMess = encryptedMess + c_message[i];
      }
      else
      {
        char currChar = c_message[i];
        char currKeyChar = keyword[i];

        if (int(currChar) >= UPPER_A && int(currChar) <= UPPER_Z && 
        int(currKeyChar) >= LOWER_A && int(currKeyChar) <= LOWER_Z)
        {
          currChar = tolower(currChar);
          char encryptedChar = ((int(currChar) - LOWER_A) + (int(currKeyChar) - LOWER_A)) % NUM_LETTERS;
          encryptedChar += LOWER_A;
          encryptedChar = toupper(encryptedChar);
          encryptedMess = encryptedMess + encryptedChar;
        }
        else if (int(currChar) >= LOWER_A && int(currChar) <= LOWER_Z)
        {
          char encryptedChar = ((int(currChar) - LOWER_A) + (int(currKeyChar) - LOWER_A)) % NUM_LETTERS;
          encryptedChar += LOWER_A;
          encryptedMess = encryptedMess + encryptedChar;
        }   
      }
    }
    SetMessage(encryptedMess);
  }


  void Vigenere::Decrypt()
  {
    string c_message = GetMessage();
    string keyword = "";
    string decryptedMess = "";
    int messSize = c_message.length();
    int keySize = m_key.length();
    int j = 0;

    for (int i = 0; i < messSize; i++)
    {
      if (j == keySize)
      {
        j = 0;
      }

      if(c_message[i] == ' ' || c_message[i] == '\"' || c_message[i] == ',' || c_message[i] == '.' || 
      c_message[i] == '(' || c_message[i] == ')' || c_message[i] == '\'')
      {
        keyword = keyword + c_message[i];
      }
      else
      {
        keyword = keyword + m_key[j];
        j++;
      }
    }

    for (int i = 0; i < messSize; i++)
    {
      if(c_message[i] == ' ' || c_message[i] == '\"' || c_message[i] == ',' || c_message[i] == '.' || 
      c_message[i] == '(' || c_message[i] == ')' || c_message[i] == '\'')
      {
        decryptedMess = decryptedMess + c_message[i];
      }
      else
      {
        char currChar = c_message[i];
        char currKeyChar = keyword[i];

        if (int(currChar) >= UPPER_A && int(currChar) <= UPPER_Z && 
        int(currKeyChar) >= LOWER_A && int(currKeyChar) <= LOWER_Z)
        {
          currChar = tolower(currChar);
          char decryptedChar = ((int(currChar) - LOWER_A) - (int(currKeyChar) - LOWER_A) + NUM_LETTERS) % NUM_LETTERS;
          decryptedChar += LOWER_A;
          decryptedChar = toupper(decryptedChar);
          decryptedMess = decryptedMess + decryptedChar;
        }
        else if (int(currChar) >= LOWER_A && int(currChar) <= LOWER_Z)
        {
          currChar = tolower(currChar);
          currKeyChar = tolower(currKeyChar);
          char decryptedChar = ((int(currChar) - LOWER_A) - (int(currKeyChar) - LOWER_A) + NUM_LETTERS) % NUM_LETTERS;
          decryptedChar += LOWER_A;
          decryptedMess = decryptedMess + decryptedChar;
        }   
      }
    }
    SetMessage(decryptedMess);    

  }


  string Vigenere::ToString()
  {
    return "(Vigenere)";
  }
  

  string Vigenere::FormatOutput()
  {
    stringstream output;
    output << 'v' << DELIMITER << GetIsEncrypted()
    << DELIMITER << GetMessage()
    << m_key << endl;

    return output.str();
  }