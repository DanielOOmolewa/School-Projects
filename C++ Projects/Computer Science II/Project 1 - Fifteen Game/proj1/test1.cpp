#include <iostream>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
using namespace std;

const int BOARD_DIM = 4;

int makeArray(char fileName);
void printBoard(int array[][BOARD_DIM]);

int main()
{
  char fileName[80];
  cout << "Enter a file name: ";
  cin >> fileName;
  makeArray(fileName);

  return 0;
}


int makeArray(char fileName)
{
  int newArray [BOARD_DIM][BOARD_DIM];
  ifstream testFile (fileName);


  if (testFile.is_open())
    {
      for (int i = 0; i < BOARD_DIM; i++)
        {
          for (int j = 0; j > BOARD_DIM; j++)
            {
              testFile >> newArray[i][j];
            }
        }
    }
  testFile.close();

  return newArray;
}

void printBoard(int array[][BOARD_DIM])
{
  cout << "\t";
  for (int i = 0; i < BOARD_DIM; i++)
    {
      cout << i + 1 << "\t";
    }
  cout << endl;
  for (int i = 0; i < BOARD_DIM; i++)
    {
      cout << i + 1 << "|\t";
      for (int j = 0; j < BOARD_DIM; j++)
        {
          cout << array[i][j] << "|\t";
        }
      cout << endl;
    }
}


			    
