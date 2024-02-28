//Title: Game.cpp
//Author: Daniel Omolewa
//Date: 3/31/2020
//Description: This is the .cpp file for Game.h


#include "Game.h"
#include "Pokemon.h"
#include <iostream>
#include <iomanip>
using namespace std;
const int TOTAL_POK = 151; //Total number of Pokemon
const int VICTORY = 1; //Winning condition where the enemy's pocket is empty after Battle()
const int LOST = 2; //Losing condition where the user's pocket is empty after Battle()
const int WON_FIGHT = 2; //Winning condition where enemy's head Pokemon has fainted after attack of the user's head Pokemon
const int LOST_FIGHT = 1; //Losing condition where user's head Pokemon has fainted aftter attack of the user's head Pokemon

Game::Game(string file)
{
    m_filename = file; //Name of the file that is passes throught
    m_list = new PokemonList; //Create new PokemonList m_list
    m_userPocket = new PokemonList; //Create new PokemonList for the user's pocket
    m_enemyPocket = new PokemonList; //Create new PokemonList for the enemy's pocket
};

Game::~Game()
{
    delete m_list; 
    delete m_userPocket;
    delete m_enemyPocket;
};

void Game::LoadFile()
{
    ifstream pok; //Object pok, for file handler
    int index = 0; //Int variable, index, for Pokemon.m_index
    string name = ""; //String variable, name, for Pokemon.m_name
    string type = ""; //String variable, type, for Pokemon.m_type
    string strong = ""; //String variable, strong, for Pokemon.m_strong

    //Read the content of the file in m_list. Make each line in the file into
    //a new Pokemon node that is then added to m_list.
    pok.open(m_filename);
    for (int i = 1; i <= TOTAL_POK; i++)
    {
        pok >> index;
        pok.ignore(256,',');
        getline(pok, name,',');
        getline(pok, type, ',');
        getline(pok, strong);
        Pokemon* temp = new Pokemon(index, name, type, strong);
        m_list->InsertEnd(temp);
    }
    pok.close();
}

void Game::ChooseTeam()
{
    int indPicked = 0; //Index of Pokemon the user would like to add to user's pocket

    //Prompt the user to select 5 valid Pokemon indexes from m_list that they would like to add to their pocket
    for (int pokLeft = NUM_TEAM; pokLeft > 0; pokLeft--)
    {
        cout << "Pick a pokemon by entering the index " << "(" << pokLeft << " left):" << endl; 
        cin >> indPicked;
        bool isThere = m_list->Exist(indPicked); //Check if the Pokemon the user wants is in m_list
        while (isThere == 0)
        {
            cout << "Invalid index. Pick again" << endl;
            cin >> indPicked;
            isThere = m_list->Exist(indPicked);
        } 

        m_list->Transfer(indPicked, m_userPocket);
        cout << "Here is a list of Pokemon you can choose from" << endl;
        cout << "------------------------------" << endl;
        m_list->Display();
        cout << "------------------------------" << endl;
    }
}

int Game::Menu()
{
    //Show the list of choices that they user can make. Make sure that they've selected a valid choice
    //Once the user makes a valid choice. Return it.
    int choice = 0; //Choice that they user makes
    cout << "------------------------------" << endl;
    cout << "Menu:" << endl;
    cout << "1. Attack" << endl;
    cout << "2. Swap" << endl;
    cout << "3. Forfeit" << endl;
    cout << "------------------------------" << endl;
    cin >> choice;
    while (choice < 1 || choice > 5)
    {
        cout << "Please enter a valid choice: " << endl;
        cin >> choice;
    }
    return choice;
}

int Game::Battle()
{
    //Reprompt the user to either attack the enemy's head Pokemon with their own head Pokemon and switch head Pokemon until
    //the user's Pocket is empty, the enemy's Pocket is empty, or if the user chooses to forfeit.  If the enemy's Pocket is empty,
    //the user wins. Otherwise, if the user's Pocket is empty or the user chooses to forfeit, the CPU wins
    int end = 0; //Condition if user or CPU wins the game
    int encResult = 0; //Result of the user's head Pokemon attack the enemy's head Pokemon
    int numRounds = 1; //Number of rounds
    int playerChoice = 0; //The user's choice

    while (m_userPocket->GetSize() != 0 && m_enemyPocket->GetSize() != 0 && playerChoice != 3)
    {
        encResult = 0; //Resetting to result of attack
        Pokemon user = Pokemon(m_userPocket->GetHead()->GetIndex(), m_userPocket->GetHead()->GetName(), m_userPocket->GetHead()->GetType(), m_userPocket->GetHead()->GetStrong()); //Pokemon object for user's head Pokemon
        user.SetHealth(m_userPocket->GetHead()->GetHealth()); //Update health of user's head Pokemon

        Pokemon rival = Pokemon(m_enemyPocket->GetHead()->GetIndex(), m_enemyPocket->GetHead()->GetName(), m_enemyPocket->GetHead()->GetType(), m_enemyPocket->GetHead()->GetStrong()); //Pokemon object for enemy's head Pokemon
        rival.SetHealth(m_enemyPocket->GetHead()->GetHealth()); //Update health of enemy's head Pokemon
            
        cout << "------------------------------" << endl;
        cout << "Round " << numRounds << ":" << endl;
        cout << "CPU's Pokemon: " << rival << endl;    
        cout << "Your Pokemon: " << user << endl;
    
        playerChoice = Menu();
        
        //If the user chooses 1, their head Pokemon will attack the enemy's head Pokemon. 
        if (playerChoice == 1)
        {
            encResult = m_userPocket->Attack(m_enemyPocket);
            //After the attack, if the user's head Pokemon wins, the enemy's head Pokemon is removed from the enemy pocket and is then replaced by the next Pokemon
            if (encResult == WON_FIGHT)
            {
                m_enemyPocket->Remove(m_enemyPocket->GetHead()->GetIndex());
                if (m_enemyPocket->GetHead() != nullptr)
                {
                    Pokemon rival = Pokemon(m_enemyPocket->GetHead()->GetIndex(), m_enemyPocket->GetHead()->GetName(), m_enemyPocket->GetHead()->GetType(), m_enemyPocket->GetHead()->GetStrong()); //Pokemon object for enemy's head Pokemon
                    rival.SetHealth(m_enemyPocket->GetHead()->GetHealth()); //Update health of enemey's head Pokemon
                    cout << "CPU changed its Pokemon to: " << rival << endl;
                }
            }
            //Otherwise, if the user's head Pokemon loses, it's removed from the user's Pocket and is replaced by another Pokemon in the user's Pocket chosen by the user
            else if (encResult == LOST_FIGHT)
            {
                m_userPocket->Remove(m_userPocket->GetHead()->GetIndex());
                m_userPocket->SwapPokemon();
                if (m_userPocket->GetHead() != nullptr)
                {
                    Pokemon user = Pokemon(m_userPocket->GetHead()->GetIndex(), m_userPocket->GetHead()->GetName(), m_userPocket->GetHead()->GetType(), m_userPocket->GetHead()->GetStrong()); //Pokemon object for user's head Pokemon
                    user.SetHealth(m_userPocket->GetHead()->GetHealth()); //Update health of user's head Pokemon
                }
            }
        }
        //If the user chooses 2, they selected a Pokemon they would like to be at the head
        else if (playerChoice == 2)
        {
            m_userPocket->SwapPokemon();
            Pokemon user = Pokemon(m_userPocket->GetHead()->GetIndex(), m_userPocket->GetHead()->GetName(), m_userPocket->GetHead()->GetType(), m_userPocket->GetHead()->GetStrong());
            user.SetHealth(m_userPocket->GetHead()->GetHealth());
        }
        numRounds++;
    }

    //Update end depending on condition and return it
    if (m_userPocket->GetSize() == 0 || playerChoice == 3)
    {
        end = LOST;
    }
    else if (m_enemyPocket->GetSize() == 0)
    {
        end = VICTORY;
    }

    return end;
}

int Game::Start()
{
    int endGame = 0; //Result of Battle()

    LoadFile();
    int pokNotPicked = TOTAL_POK; //Number of remaining Pokemon that can be selected to populate enemy's pocket
    int randInd = 0; //Random index of Pokemon to be chosen to populate enemy's pocket

    cout << "Here is a list of Pokemon you can choose from" << endl;
    cout << "------------------------------" << endl;
    m_list->Display();
    cout << "------------------------------" << endl;
    
    ChooseTeam();
    cout << "Print player pocket:" << endl;
    m_userPocket->Display();
    
    //Select 5 random Pokemon that remain in the list after the user has chosen their 5 Pokemon.
    for (int pokLeft = NUM_TEAM; pokLeft > 0; pokLeft--)
    {
        bool isThere = 0;
        do
        {
            randInd = rand() % pokNotPicked;
            isThere = m_list->Exist(randInd);
        } while (isThere == 0);
        m_list->Transfer(randInd, m_enemyPocket);
        pokNotPicked--;
    }   

    
    cout << "------------------------------" << endl;
    
    cout << "Print enemy pocket:" << endl;
    m_enemyPocket->Display();

    //Update and return result of Battle()
    endGame = Battle();
    while (endGame == 0)
    {
        endGame = Battle();
    }
    return endGame;
}

