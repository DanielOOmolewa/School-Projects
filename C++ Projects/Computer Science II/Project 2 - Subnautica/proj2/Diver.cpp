#include "Diver.h"
#include <iostream>
using namespace std;

Diver::Diver()
{
  m_myName = "Dan The Man";
  m_numMaterials = 0;
}

Diver::Diver(string name)
{

  m_myName = name;
}

string Diver::GetName()
{
  return m_myName;
}

void Diver::SetName(string name)
{
  m_myName = name;
}

void Diver::DisplayMaterials()
{
  // Iterate through m_myMaterials and display the list number, name, and quantity of each material in the
  // array
  for (int i = 0; i < PROJ2_SIZE; i++)
  {
    int numOnList = i + 1; // List number
    cout << numOnList << ". "  << m_myMaterials[i].m_name << ", " << m_myMaterials[i].m_quantity << endl;
  }
  cout << "\n";
}


int Diver::CheckMaterial(Material currentStruct)
{
    bool matIsThere = 0; // Indicates whether on not there's the material is found
    int indexFound; // The index that is found

    // Iterate through m_myMaterials and if the name of the material equals the name of the 
    // material in the parameter, set matIsThere equal to 1 and indexFound equal to the i
    for (int i = 0; i <= m_numMaterials; i++)
    {
      if (m_myMaterials[i].m_name == currentStruct.m_name)
      {
        matIsThere = 1;
        indexFound = i;
      }
    }

  // If the material is found, return the index where it was found. Otherwise, return -1
  if (matIsThere == 1)
  {
    return indexFound;
  }
  else
  { 
    return -1;
  }
}

void Diver::AddMaterial(Material currentStruct)
{
  // Populate the known material list
  m_myMaterials[m_numMaterials] = currentStruct;
  m_numMaterials++;   
}

void Diver::IncrementQuantity(Material currentStruct)
{
  // Iterate through the list amd if the name of the material equals to the name of the given
  // material, increase the quantity by 1
  for (int i = 0; i <= m_numMaterials; i++)
    {
      if (m_myMaterials[i].m_name == currentStruct.m_name)
      {
        m_myMaterials[i].m_quantity++;
      }
    }
}

bool Diver::DecrementQuantity(Material currentStruct)
{
  // Iterate through the list amd if the name of the material equals to the name of the given
  // material, decrease the quantity by 1 
  // Return 1, since the function has a return type of bool 
  for (int i = 0; i <= m_numMaterials; i++)
    {
      if (m_myMaterials[i].m_name == currentStruct.m_name)
      {
        m_myMaterials[i].m_quantity--;
      }
    }
  return 1;
}

bool Diver::CheckQuantity(Material currentStruct1, Material currentStruct2)
{
  bool matsInInv = 0; // Indicates whether or not there's a least one of each given materials in the list
  bool matInInv_1 = 0; // Indicates whether or not there's a least one quantity of the first given material in the list
  bool matInInv_2 = 0; // Indicates whether or not there's a least one quantity of the second given material in the list 

  // Iterate through the list and check if there's a least one of each of the given materials in the list
  // If there's at least one quantity of the first given material, set matInInv_1 equal to 1. 
  // If there's a least one quantity of the second given material, set matInInv_2 equal to 2.
  for (int i = 0; i < PROJ2_SIZE; i++)
  {
    
    if (m_myMaterials[i].m_name == currentStruct1.m_name)
    {
      if (m_myMaterials[i].m_quantity >= 1)
      {
        matInInv_1 = 1;
      }
    }
    if (m_myMaterials[i].m_name == currentStruct2.m_name)
    {
      if (m_myMaterials[i].m_quantity >- 1)
      {
        matInInv_2 = 1;
      }
    }
  }

  // If matInInv_1 and matInInv_2 are both 1, set matsInInv = 1 and return it
  // Otherwise simply return matsInInv with the default value of 0
  if (matInInv_1 == 1 && matInInv_2 == 1)
  {
    matsInInv = 1;
  }
  return matsInInv;
}

Material Diver::GetMaterial(int index)
{
  // Iterate through m_myMaterials and once the index equals to the given index, check to see if the 
  // material at the given index is advanced or unique with a quantity of 0. If it is one or the other, 
  // return the material at the index. If the material is unique with a quantity of 1, tell the player
  // that the unique material has already been made. Return m_myMaterials at the index of 0 if the first
  // return statement has not gone through
  for (int i = 0; i < PROJ2_SIZE; i++)
  {
    if (i == index)
    {
      string matType = m_myMaterials[i].m_type; // The material type
      int matQuant = m_myMaterials[i].m_quantity; // the quantity of the material
      if ((matType == "advanced") || (matType == "unique" && matQuant == 0))
      {
        return m_myMaterials[i];
      }
      else if (matType == "unique" && matQuant == 1)
      {
        cout << "\n";
        cout << "That unique material has already been made" << endl << endl;;
      }   
    }
  }
  return m_myMaterials[0];
}

int Diver::CalcDepth()
{
  int totalDepth = 0; // The total depth the player has reached
  // Iterate through m_myMaterials and if the material is unique with a quantity of 1, add
  // it's depth to totalDepth. Then, return totalDepth
  for (int i = 0; i < PROJ2_SIZE; i++)
  {
    if (m_myMaterials[i].m_type == "unique" && m_myMaterials[i].m_quantity == 1)
    {
      totalDepth += m_myMaterials[i].m_depth;
    }
  }
  return totalDepth;
}

