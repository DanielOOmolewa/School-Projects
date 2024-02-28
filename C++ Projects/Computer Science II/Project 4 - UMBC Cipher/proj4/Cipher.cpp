//Title: Cipher.cpp
//Author: Daniel Omolewa
//Date: 4/22/2020
//Description: This is part of the Cipher Project in CMSC 202 @ UMBC
#include "Cipher.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;


  Cipher::Cipher()
  {
    m_message = "";
    m_isEncrypted = 0;
  }


  Cipher::Cipher(string message, bool isEncrypted)
  {
    m_message = message;
    m_isEncrypted = isEncrypted;
  }
  
  Cipher::~Cipher()
  {

  }
  
  void Cipher::Decrypt() 
  {

  }
  
  void Cipher::Encrypt()
  {

  }


  string Cipher::GetMessage()
  {
    return m_message;
  }

  bool Cipher::GetIsEncrypted()
  {
    return m_isEncrypted;
  }

  void Cipher::SetMessage(string newMessage)
  {
    m_message = newMessage;
  }

  void Cipher::ToggleEncrypted()
  {
    if (m_isEncrypted == 0)
    {
      m_isEncrypted = 1;
    }
    else if (m_isEncrypted == 1)
    {
      m_isEncrypted = 0;
    }
  }
  
  string Cipher::ToString() 
  {

  }
  
  string Cipher::FormatOutput() 
  {

  }

  ostream &operator<<( ostream &output, Cipher &C)
  {
    output << C.GetMessage() << " " << C.ToString();
    return output;
  }