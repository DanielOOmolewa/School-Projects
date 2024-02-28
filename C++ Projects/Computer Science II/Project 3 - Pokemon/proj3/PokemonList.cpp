//Title: PokemonList.cpp
//Author: Daniel Omolewa
//Date: 3/31/2020
//Description: This is the .cpp file for PokemonList.h

#include "PokemonList.h"
#include <iostream>
using namespace std;
const int WON_ENCOUNTER = 2; //Winning condition after Attack() where the enemy's head Pokemon has at most 0 health
const int LOST_ENCOUNTER = 1; //Losing condition after Attack() where the user's head Pokemon has at most 0 health
PokemonList::PokemonList()
{
    m_head = nullptr; //List starts of empty
    m_size = 0; //Initialize size of list as 0
}

PokemonList::~PokemonList()
{
    Pokemon* prev = m_head; //Pokemon node pointer, prev, set as head
    Pokemon* curr = m_head; //Pokemon node pointer, curr, set as head

    //Traverse the list and delete each and every Pokemon node
    while (curr != nullptr)
    {
        prev = curr;
        curr = curr->GetNext();
        delete prev;
    }

}

void PokemonList::InsertEnd(Pokemon* currPok)
{
    //If the list is empty, make the Pokemon the head and increase the size of the list by 1
    if (m_head == nullptr)
    {
        m_head = currPok;
        m_size++;
    }
    //Otherwise, traverse the list until the last node is reached and add the Pokemon there. 
    //After adding the Pokemon, increase the size of the list by one
    else
    {
        Pokemon* temp = m_head; //Pokemon node pointer set as head
        while (temp->GetNext() != nullptr)
        {
            temp = temp->GetNext();
        }
        temp->SetNext(currPok);
        currPok->SetNext(nullptr);
        m_size++;
    }
}

void PokemonList::Display()
{
    Pokemon* temp = m_head; //Pokemon node pointer set as head

    //Traverse the list and print out the attributes of each node
    while (temp != nullptr)
    {
        cout << left << "Index: " << setw(5) << temp->GetIndex() << left;
        cout << "Name: " << setw(12) << temp->GetName() << left; 
        cout << "Type: " << setw(10) << temp->GetType() << left; 
        cout << "Health: " << temp->GetHealth() << endl;
        temp = temp->GetNext();  
    }
}

void PokemonList::Transfer(int index, PokemonList* targetList)
{
    Pokemon* currPok = m_head; //Pokemon node pointer, currPok, set equal as head
    Pokemon* newPok = m_head; //Pokemon node pointer, newPok, set equal as head
    
    //Traverse the list until the node with the desired index is reached. Then add the wanted Pokemon to the target list and remove it
    while (currPok != nullptr)
    {
        if (index == currPok->GetIndex())
        {
            newPok = new Pokemon(currPok->GetIndex(), currPok->GetName(), currPok->GetType(), currPok->GetStrong()); //Desired Pokemon
            targetList->InsertEnd(newPok);
            Remove(index);
            return;
        }
        currPok = currPok->GetNext();
    }

}

void PokemonList::Remove(int index)
{
    Pokemon* curr = m_head; //Pokemon node pointer, curr, set as the head
    Pokemon* prev = m_head; //Pokemon node pointer, prev, set as the head

    //If the Pokemon with the selected index is at the head, next Pokemon to be the head, and delete the Pokemon with the selected index.
    //Then decrease the size of the list by 1
    if (index == m_head->GetIndex())
    {
        m_head = curr->GetNext();
        delete curr;
        curr = nullptr;
        m_size--;
    }
    else
    {
        //Traverse the list until the Pokemon node with the selected index or the end has been reached
        while (curr != nullptr && curr->GetIndex() != index)
        {            
            prev = curr;
            curr = curr->GetNext();
        }
        //If the end of the list has been reached, tell the user that the Pokemon selected to be remove has not been found in the list
        if (curr == nullptr)
        {
            cout << "Did not find unwanted Pokemon" << endl;
        }
        //If the Pokemon with the selected index has been reached, have the previous Pokemon point to the Pokemon after the one with the 
        //selected index. Then delete the Pokemon with the selcted index and decrease the size of the list by 1
        else
        {
            prev->SetNext(curr->GetNext());
            delete curr;
            m_size--;
        }
        
    }
}

int PokemonList::GetSize()
{
    return m_size;
}

Pokemon* PokemonList::GetHead()
{
    return m_head;
}

int PokemonList::Attack(PokemonList* rivalList)
{
    int pokFainted = 0; //Result of the user's head Pokemon attacking the enemy's head Pokemon

    //If the user's head Pokemon (UHP) is strong against the enemy's head Pokemon (EHP), then the EHP receives 5 damage. If the
    //EHP's health is at most 0, then the UHP wins the encounter. If the EHP survives, then the UHP receives 3 damage and loses if its
    //health is at least 0. If both the UHP and EHP survive, pokFainted remains as 0.
    if (m_head->GetStrong() == rivalList->GetHead()->GetType())
    {
        cout << "CPU's Pokemon took " << STRONG_DAMAGE << " damage" << endl;
        rivalList->GetHead()->SetHealth(rivalList->GetHead()->GetHealth() - STRONG_DAMAGE);
        if (rivalList->GetHead()->GetHealth() > 0)
        {
            cout << "Your Pokemon took " << DAMAGE2USER << " damage" << endl;
            m_head->SetHealth(m_head->GetHealth() - DAMAGE2USER);
            if (m_head->GetHealth() <= 0)
            {
                cout << "Your Pokemon has been defeated" << endl;
                pokFainted = LOST_ENCOUNTER;
                return pokFainted;
            }
        }
        else if (rivalList->GetHead()->GetHealth() <= 0)
        {
            cout << "CPU's Pokemon has been taken out" << endl;
            pokFainted = WON_ENCOUNTER;
            return pokFainted;
        }    
    }
    //If the EHP is strong against the UHP, then the EHP receives 2 damage. If the EHP's health is at most 0,
    //then the UHP wins the encounter. If the EHP survives, then the UHP receives 5 damage and loses if its health is at least 0. 
    //If both the UHP and EHP survive, pokFainted remains as 0.
    else if (m_head->GetType() == rivalList->GetHead()->GetStrong())
    {
        cout << "CPU's Pokemon took " << DAMAGE2ENEMY << " damage" << endl;
        rivalList->GetHead()->SetHealth(rivalList->GetHead()->GetHealth() - DAMAGE2ENEMY);
        if (rivalList->GetHead()->GetHealth() > 0)
        {
            cout << "Your Pokemon took " << STRONG_DAMAGE << " damage" << endl;
            m_head->SetHealth(m_head->GetHealth() - STRONG_DAMAGE);
            if (m_head->GetHealth() <= 0)
            {
                cout << "Your Pokemon has been defeated" << endl;
                pokFainted = LOST_ENCOUNTER;
                return pokFainted;
            }
        }
        else if (rivalList->GetHead()->GetHealth() <= 0)
        {
            cout << "CPU's Pokemon has been taken out" << endl;
            pokFainted = WON_ENCOUNTER;
            return pokFainted;
        }
    }
    //If the UHP and EHP have the same time and are strong against each other, then the EHP receives 5 damage. If the
    //EHP's health is at most 0, then the UHP wins the encounter. If the EHP survives, then the UHP receives 5 damage and loses if its
    //health is at least 0. If both the UHP and EHP survive, pokFainted remains as 0.
    else if ((m_head->GetType() == rivalList->GetHead()->GetStrong()) && (m_head->GetStrong() == rivalList->GetHead()->GetStrong()))
    {

        cout << "CPU's Pokemon took " << STRONG_DAMAGE << " damage" << endl;
        rivalList->GetHead()->SetHealth(rivalList->GetHead()->GetHealth() - STRONG_DAMAGE);
        if (rivalList->GetHead()->GetHealth() > 0)
        {
            cout << "Your Pokemon took " << STRONG_DAMAGE << " damage" << endl;
            m_head->SetHealth(m_head->GetHealth() - STRONG_DAMAGE);
            if (m_head->GetHealth() <= 0)
            {
                
                cout << "Your Pokemon has been defeated" << endl;
                pokFainted = LOST_ENCOUNTER;
                return pokFainted;
            }
        }
        else if (rivalList->GetHead()->GetHealth() <= 0)
        {   
            cout << "CPU's Pokemon has been taken out" << endl;
            pokFainted = WON_ENCOUNTER;
            return pokFainted;
        }
    }
    else
    {
        //In all other encounters between the UHP and EHP, the EHP receives 2 damage. If the EHP's health is at most 0,
        //then the UHP wins the encounter. If the EHP survives, then the UHP receives 3 damage and loses if its health is at least 0. 
        //If both the UHP and EHP survive, pokFainted remains as 0.
        cout << "CPU's Pokemon took " << DAMAGE2ENEMY << " damage" << endl;
        rivalList->GetHead()->SetHealth(rivalList->GetHead()->GetHealth() - DAMAGE2ENEMY);
        if (rivalList->GetHead()->GetHealth() > 0)
        {

            cout << "Your Pokemon took " << DAMAGE2USER << " damage" << endl;
            m_head->SetHealth(m_head->GetHealth() - DAMAGE2USER);
            if (m_head->GetHealth() <= 0)
            {  
                cout << "Your Pokemon has been defeated" << endl;
                pokFainted = LOST_ENCOUNTER;
                return pokFainted;
            }
        }
        else if (rivalList->GetHead()->GetHealth() <= 0)
        {
            cout << "CPU's Pokemon has been taken out" << endl;
            pokFainted = WON_ENCOUNTER;
            return pokFainted;
        }
    }
    
    
    return pokFainted;
}

void PokemonList::SwapPokemon()
{
    int indToSwap = 0; //Index of the Pokemon the user would like to make head
    Pokemon* curr = m_head; //Pokemon node pointer, curr, set as the head
    Pokemon* prev = m_head; //Pokemon node pointer, prev, set as the head

    bool doesExist = 0; //Check if the selected Pokemon exists in the list

    //If the size of the list is 0, return to have none of the rest of the code run
    if (m_size == 0)
    {
        return;
    }
    
    cout << "Which Pokemon would you like to choose? (Enter the index #)" << endl;
    Display();
    cin >> indToSwap;
    doesExist = Exist(indToSwap);

    //Make sure that the Pokemon with the selected index is actually in the list
    while (doesExist == 0)
    {
        cout << "You don't have that Pokemon" << endl;
        cin >> indToSwap;
        doesExist = Exist(indToSwap);        
    }
    
    //If the Pokemon with the selected index, let the user know that their choice is the head
    if (indToSwap == curr->GetIndex())
    {
        cout << "Choice is head" << endl;
        //If the size of the list is 1, let the user know that their chosen Pokemon is their last one
        if (m_size == 1)
        {
            cout << "This is your last Pokemon!!!" << endl;
        }
        return;
    }

    //Otherwise, traverse through the list and move the head to the next node over and make the Pokemon 
    //with the selected index be the new head
    else 
    {   
        while (curr != nullptr)
        {
            if (indToSwap == curr->GetIndex())
            {
               prev->SetNext(curr->GetNext());
               curr->SetNext(m_head);
               m_head = curr;

            }
            prev = curr;
            curr = curr->GetNext();
        }

    }
}

bool PokemonList::Exist(int index)
{
    bool isThere = 0; //Indicate that the Pokemon with the selected index has been found in the list
    Pokemon* temp = m_head; //Pokemon node pointer, temp, set as head

    //If the list is empty set isThere equal to 0 and return it
    if (m_size == 0)
    {
        isThere = 0;
        return isThere;
    }
    //Otherwise, traverse the list either until the Pokemon with the selected index has been found or the end has been reached
    else
    {
        while (temp != nullptr)
        {
            //If the Pokemon with the selected index has been found set isThere equal to 1 and return i
            if (temp->GetIndex() == index)
            {
                isThere = 1;
                return isThere;
            }
            temp = temp->GetNext();
        }
    }
    //Returns isThere as 0 if the list has been fully traversed
    return isThere;
}