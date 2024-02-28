//Title: Pokemon.cpp
//Author: Daniel Omolewa
//Date: 3/31/2020


#include "Pokemon.h"
#include <iostream>
using namespace std;

Pokemon::Pokemon()
{
    m_index = 0;
    m_name = "";
    m_type = "";
    m_strong = "";
    m_health = MAX_HEALTH;
    m_next = nullptr;
}

Pokemon::Pokemon(int index, string name, string type, string strong)
{
    m_index = index;
    m_name = name;
    m_type = type;
    m_strong = strong;
    m_next = nullptr;
    m_health = MAX_HEALTH;
}

ostream &operator<<( ostream &output, Pokemon &P)
{
    output << P.GetName() << " (" << P.GetType() << ": " << P.GetHealth() << " health)";
    return output;
}

Pokemon* Pokemon::GetNext()
{
    return m_next;
}

string Pokemon::GetName()
{
    return m_name;
}

int Pokemon::GetIndex()
{
    return m_index;
}

string Pokemon::GetType()
{
    return m_type;
}

int Pokemon::GetHealth()
{
    return m_health;
}

string Pokemon::GetStrong()
{
    return m_strong;
}

void Pokemon::SetHealth(int health) 
{
    m_health = health;
}

void Pokemon::SetNext(Pokemon* next)
{
    m_next = next;
}


