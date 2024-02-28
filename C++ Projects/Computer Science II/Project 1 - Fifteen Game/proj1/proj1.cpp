//File: proj1.cpp
//Author: Daniel Omolewa
//Date: 2/25/2020
//Section: 04
//E-mail: o24@umbc.edu
//Description: The program creates a game board that the user can manipulate in order
//to get a board that is out of order into a correct order. Additionally,
//the game will indicate when the game is “solved” by putting the tiles into the correct location.
#include <iostream>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
using namespace std;
 
const int BOARD_DIM = 4; // default dimension of the board

void startGame(int choice, int newArray[BOARD_DIM][BOARD_DIM]);
void makeArray(char fileName[80], int newArray[BOARD_DIM][BOARD_DIM]);
void printBoard(int newArray[BOARD_DIM][BOARD_DIM]);
void boardUpdates(int newArray[BOARD_DIM][BOARD_DIM]);
void validateMove(int row, int col, int newArray[BOARD_DIM][BOARD_DIM]);
bool checkBoard(int newArray[BOARD_DIM][BOARD_DIM]);


int main()
{
  int newArray [BOARD_DIM][BOARD_DIM]; //declaration of the default board
  int userChoice = 0; //user's input on whether they want to load a board or not
  cout << "Welcome to the Fifteen Game" << endl;
  cout << "Would you like to load a board?" << endl;
  cout << "1. Yes" << endl << "2. No" << endl;
  cin >> userChoice;
  while (userChoice != 1 and userChoice != 2)
    {
      cout << "Invalid choice" << endl;
      cout << "Would you like to load a board?" << endl;
      cout << "1. Yes" << endl << "2. No" << endl;
      cin >> userChoice;
    }
  startGame(userChoice, newArray);
  bool checkWin = false;
  while (checkWin != true)
    {
      boardUpdates(newArray);
      checkWin = checkBoard(newArray);
      boardUpdates(newArray);
    }
  return 0;
}

void startGame(int choice, int newArray[BOARD_DIM][BOARD_DIM])
//PreCondition: Choice is an integer and newArray has been declared
//PostCondition: makeArray amd printBoard has been called depending on the user's choice
{
  int defaultBoard[BOARD_DIM][BOARD_DIM] = {{1,2,3,4}, {5,6,7,8}, {9,10,11,12}, {13,14,0,15}};
  switch(choice)
    {
    case 1:
      char fileName[80];
      cout << "What is the file name?" << endl;
      cin >> fileName;
      makeArray(fileName, newArray);
      printBoard(newArray);
      break;
    default:
      cout << "Loading default" << endl;
      printBoard(defaultBoard);
      
    }
}

void makeArray(char fileName[80], int newArray[BOARD_DIM][BOARD_DIM])
//PreCondition: fileName has been entered and newArray has been declared
//PostCondition: An array has been filled with integers from a file
{
  ifstream testFile (fileName);  
 
  if (testFile.is_open())
    {
      for (int i = 0; i < BOARD_DIM; i++)
	{
	  for (int j = 0; j < BOARD_DIM; j++)
	    {
	      testFile >> newArray[i][j];
	    }
	}
    }
  testFile.close();

}

void printBoard(int newArray[BOARD_DIM][BOARD_DIM])
//PreCondition: newArray has been declared
//PostCondition: Board has been printed out
{
  cout << "\t";
  for (int c = 0; c < BOARD_DIM; c++)
    {
      cout << c + 1 << "\t";
    }
  cout << endl;
  for (int i = 0; i < BOARD_DIM; i++)
    {
      cout << i + 1 << "|\t";
      for (int j = 0; j < BOARD_DIM; j++)
	{
	  cout << newArray[i][j] << "|\t";
	}
      cout << endl;
    }
}

bool checkBoard(int newArray[BOARD_DIM][BOARD_DIM])
//PreCondition: newArray has been ceclared
//PostCondition: Board has been checked if winning condition has been met
{
  bool haveWon = false;
  int tile = 0;
  int count = 0;
  for (int i = 0; i < BOARD_DIM; i++)
    {
      for (int j = 0; j < BOARD_DIM; j++)
	{
	  tile = newArray[i][j];
	  if (tile == count + 1)
	    {
	      haveWon = true;
	      count++;
	    }
	  else if (tile != count + 1)
	    {
	      haveWon = false;
	      count++;
	    }
	}
    }
  return haveWon;
}


void boardUpdates(int newArray[BOARD_DIM][BOARD_DIM])
//PreCondition: newArray has been declared
//PostCondition: Board has been updated 
{
  int row = 0;
  int column = 0;
  cout << "What is the row (left) and column (top) to slide?" << endl;
  cin >> row;
  cin >> column;
  int trueRow = row - 1;
  int trueCol = column - 1;
  validateMove(trueRow, trueCol, newArray);
  printBoard(newArray);
  
}

void validateMove(int row, int col, int newArray[BOARD_DIM][BOARD_DIM])
//PreCondition: Interger values for row and int has row and int has been assigned. newArray
//has been declared
//PostCondition: Tile has been checked if it's adjacent to empty slot (0)
{
  int tile = newArray[row][col]; //Tile the user has selected
  int upTile = newArray[row-1][col]; //Tile that's above the selected tile
  int downTile = newArray[row+1][col]; //Tile that's below the slected tile
  int leftTile = newArray[row][col-1]; //Tile to the left of the selected tile
  int rightTile = newArray[row][col+1]; //Tile to the right of the slected tile
  int swap = 0; //Swapped tile

  //Checks if the tile adjacent to the selected tile is empty (0)
  //If the tile is adjacent swap the pieces accordingly
  while (upTile != 0 and downTile != 0 and leftTile != 0 and rightTile != 0)
   {
     cout << "Tile is not adjacent to empty slot, try again" << endl;
     cout << "What is the row (left) and column (top) to slide?" << endl;
     cin >> row;
     cin >> col;
     row -= 1;
     col -= 1;
     tile = newArray[row][col];
     upTile = newArray[row-1][col];
     downTile = newArray[row+1][col];
     leftTile = newArray[row][col-1];
     rightTile = newArray[row][col+1];
   }

  if (upTile == 0)
    {
      swap = tile;

      newArray[row][col] = upTile;
      newArray[row-1][col] = swap;


      cout << "The tile slid up" << endl;
    }
  else if (downTile == 0)
    {
      swap = tile;
      
      newArray[row][col] = downTile;
      newArray[row+1][col] = swap;

      cout << "The tile slid down" << endl;
    }
  else if (leftTile == 0)
    {
      swap = tile;

      newArray[row][col] = leftTile;
      newArray[row][col-1] = swap;


      cout << "The tile slid left" << endl;
    }
  else if (rightTile == 0)
    {
      swap = tile;

      newArray[row][col] = rightTile;
      newArray[row][col+1] = swap;


      cout << "The tile slid right" << endl;
    }
}
