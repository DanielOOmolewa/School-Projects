//Title: Caesar.cpp
//Author: Daniel Omolewa
//Date: 4/22/2020
//Description:  This is part of the Cipher Project in CMSC 202 @ UMBC
#include "Caesar.h"
#include <istream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

const int UPPER_A = 'A'; //ASCII decimal value for character A
const int UPPER_Z = 'Z'; //ASCII decimal value for character Z
const int LOWER_A = 'a'; //ASCII decimal value for character a
const int LOWER_Z = 'z'; //ASCII decimal value for character z
const int BUFFER = 1; //Number to correct the offset

  Caesar::Caesar()
  {
    m_shift = 3;
  }

 
  Caesar::Caesar(string meoutputage, bool isEncrypted, int key): Cipher(meoutputage, isEncrypted)
  {
    m_shift = key;
  }


  Caesar::~Caesar()
  {
    
  }


  void Caesar::Encrypt()
  {
    string c_message = GetMessage(); //The cipher message
    int messSize = c_message.length(); //The length of the cipher message
    int extraShift = 0; //The offset in case the character change goes out of the bounds of the ASCII decimal value of the alphabet

    //Traverse the cipher message and shift each character to the right
    for (int i = 0; i < messSize; i++)
    {
      char currChar = c_message[i]; //The current character in the cipher message

      //If currChar is a capital and the character change exceeds UPPER_Z, assign currChar to UPPER_A + the offset
      if (int(currChar) >= UPPER_A && int(currChar) <= UPPER_Z)
      {
        if ((int(currChar) + m_shift) > UPPER_Z)
        {
          extraShift = (int(currChar) + m_shift) - UPPER_Z - BUFFER;
          c_message[i] = UPPER_A + extraShift; 
        }
        //If the character change does not exceed UPPER_Z, simply do the character change
        else if ((int(currChar) + m_shift) <= UPPER_Z)
        {
          c_message[i] = c_message[i] + m_shift;
        }        
      }

      //If currChar is lower and the character change exceeds LOWER_z, assign currChar to LOWER_a + the offset
      else if (int(currChar) >= LOWER_A && int(currChar) <= LOWER_Z)
      {
        if((int(currChar) + m_shift) > LOWER_Z)
        {
          extraShift = (int(currChar) + m_shift) - LOWER_Z - BUFFER;
          c_message[i] = LOWER_A + extraShift;
        }
        //If the character change does not exceed LOWER_Z, simply do the character change
        else if ((int(currChar) + m_shift) <= LOWER_Z)
        {
          c_message[i] = c_message[i] + m_shift;
        }
      }
    //If the current character is one of these characters, leave them alone
    else if(c_message[i] == ' ' || c_message[i] == '\"' || c_message[i] == ',' 
    || c_message[i] == '.' || c_message[i] == '(' || c_message[i] == ')' || c_message[i] == '\'')
    {
      c_message[i] = c_message[i];
    }   
    }
    SetMessage(c_message);
  }


  void Caesar::Decrypt()
  { 
    string c_message = GetMessage(); //The cipher message
    int messSize = c_message.length(); //The length of the cipher message
    int extraShift = 0; //The offset in case the character change goes out of the bounds of the ASCII decimal value of the alphabet

    //Traverse the cipher message and shift each character to the left
    for (int i = 0; i < messSize; i++)
    {
      char currChar = c_message[i]; //The current character in the cipher message

      //If currChar is a capital and the character change falls behind UPPER_A, assign currChar to UPPER_Z - the offset
      if (int(currChar) >= UPPER_A && int(currChar) <= UPPER_Z)
      {
        if ((int(c_message[i]) - m_shift) < UPPER_A)
        {
          extraShift = UPPER_A - (int(c_message[i]) - m_shift) - BUFFER;
          c_message[i] = UPPER_Z - extraShift; 
        }
        //If the character change does not fall behind UPPER_A, simply do the character change
        else if ((int(c_message[i]) - m_shift) >= UPPER_A)
        {
          c_message[i] = c_message[i] - m_shift;
        }
      }

      //If currChar is a capital and the character change falls behind LOWER_A, assign currChar to LOWER_Z - the offset
      else if (int(currChar) >= LOWER_A && int(currChar) <= LOWER_Z)
      {
        if((int(c_message[i]) - m_shift) < LOWER_A)
        {
          extraShift = LOWER_A - (int(c_message[i]) - m_shift) - BUFFER;
          c_message[i] = LOWER_Z - extraShift;
        }
        //If the character change does not fall behind LOWER_A, simply do the character change
        else if((int(c_message[i]) - m_shift) >= LOWER_A)
        {
          c_message[i] = c_message[i] - m_shift;
        }
      }
      //If the current character is any of these characters, leave them alone
      else if (c_message[i] == ' ' || c_message[i] == '\"' || c_message[i] == ',' 
      || c_message[i] == '.' || c_message[i] == '(' || c_message[i] == ')' || c_message[i] == '\'')
      {
        c_message[i] = c_message[i];
      }
  
    }
    SetMessage(c_message);
  }


  string Caesar::ToString()
  {
    //Return the subtype
    return "(Caesar)";
  }
  

  string Caesar::FormatOutput()
  {
    stringstream output;
    output << 'c' << DELIMITER << GetIsEncrypted()
    << DELIMITER << GetMessage() 
    << DELIMITER << m_shift << endl;
  
    return output.str();
  }