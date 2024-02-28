"""
File: proj3.py
Author: Daniel Omolewa
Date: 12/4/2019
Section: 32
E-mail: o24@umbc.edu
Description: This program contains a simplified scoring system for the booard
             game Go. Go is an abstract stategy game where two players compete
             to surround as much of a board with their colored pieces as
             possible. At the end of the game, each players score is the sum of
             how many pieces they still have on the board with how much empty
             space their pieces surround.
"""
VALID_BOARDS = [1,2,3,4,5]

def make_board(filename):
    """
    Convert the file into a list of strings and print it into a board
    :parem: filename - Name of the file
    :return: board - A 2d list that represents the Go board
    """
    #Open the file and use .r to get the entire text as one whole string. Next,
    #use .split to seperate each line by the "\n" character. Print out each line
    board = []
    with open(filename, "r") as f:
        board_string = f.read()
    board_rows = board_string.split("\n")

    for row in board_rows:
        board.append(row)
        print(row)
    return board

def make_mutable_board(board):
    """
    Convert the board from a list of strings to a 2d list of individual characters
    to allow change in the elements
    :parem: board - The list of strings that represents the board
    :return: mutable_board - The 2d list that has indivdual characters that can be
             changed
    """
    #Instantiate the mutable board. As the board is being transversed row by row,
    #instantiate the variable row each time a row is being transversed. Add
    #each character to the row and after transversing the row, append the entire
    #row to mutable_board
    mutable_board = []
    for i in range(len(board)):
        row = []
        for j in range(len(board[i])):
            row.append(board[i][j])
        mutable_board.append(row)
    return mutable_board

def score(board):
    """
    Count up the total score for the black, represented as "X", and white,
    represented as "O", pieces. Print the total score for each pieces
    :parem: board - The 2d list that represents the filled out board
    :return: None
    """
    #Instantiate black and white as 0. Transverse the board and if the piece is
    #"O", add 1 to white. If the piece is "X", add 1 to black. Then, print out
    #the total number of white and black pieces found
    black = 0
    white = 0
    for row in board:
        for piece in row:
            if piece == "O":
                white += 1
            elif piece  == "X":
                black += 1

    print("Black scored:", black)
    print("White scored:", white)

def print_filled_board(filled_board):
    """
    Print out the colored board
    :parem: filled_board: The colored board
    :return: None:
    """
    #Transverse the board row by row and print out each row
    for i in range(len(filled_board)):
        for j in range(len(filled_board[i])):
            print(filled_board[i][j], end="")
        print("")
            

def fill_board(board, row):
    """
    Fill out the board accordingly
    :parem: board - The 2d list that represents the board
    :parem: row - The current row
    :return: board - The colred out board
    """
    #Instantiate the boolean flag same_piece
    same_piece = True
    #The base case. If the current row equals to the length of the board (which
    #is the total number of rows), then simply return the board
    if row == len(board):
        return board

    #Recursive case
    else:
        #Transverse through the board, row by row. Check the current index to see
        #if it's an X or O and check the indexs outside of it 
        for i in range(len(board[row])):
            #If the current index is an "X", check the indexes before and after it
            #If any of them is a "+", replace them if with an "X". Stop checking
            #if an index is a "O"
            if board[row][i]  == "X":
                for j in range(i, -1, -1):
                    if (board[row][j] == "+") and (same_piece != False):
                        board[row][j] = "X"
                    elif board[row][j] == "O":
                        same_piece = False
                same_piece = True
                
                for j in range(i, len(board[row])):
                    if (board[row][j] == "+") and (same_piece != False):
                        board[row][j] = "X"
                    elif board[row][j] == "O":
                        same_piece = False
                same_piece = True

            #If the current index is an "O", check the indexes before and after it
            #If any of them is a +, replace them if with an "O". Stop checking if
            #an index is a "X"
            elif board[row][i] == "O":
                for j in range(i, -1, -1):
                    if (board[row][j] == "+") and (same_piece != False):
                        board[row][j] = "O"
                    elif board[row][j] == "X":
                        same_piece = False
                same_piece = True
                
                for j in range(i, len(board[row])):
                    if (board[row][j] == "+") and (same_piece != False):
                        board[row][j] = "O"
                    elif board[row][j] == "X":
                        same_piece = False
                same_piece = True
                
        row += 1
        return fill_board(board, row)
                    
    

def user_choice():
    """
    The auxillary function. First, prompt the user to enter a valid board number
    and reprompt thme if they enter an invalid one. Then call the previous
    functions with parameters that is based on the user's input
    :parem: None
    :return: None
    """
    board_num = int(input("Enter a board number between 1 and 5: "))
    while board_num not in VALID_BOARDS:
        print("Invalid board number")
        board_num = int(input("Enter a board number between 1 and 5: "))
    #Instantiate row as 0
    row = 0

    #If the user enters a valid board number, print out both the unfilled and
    #filled versions of the board that they chose and give them the scores of
    #each pieces via the functions, make_board, make_mutable_board, fill_board,
    #print_filled_board, and score
    if board_num == 1:
        print("We are scoring this board:")
        board_1 = make_board("board1.txt")
        print("Here is the colored board:")
        board_1 = make_mutable_board(board_1)
        colored_board = fill_board(board_1, row)
        print_filled_board(colored_board)
        score(colored_board)
        
    elif board_num == 2:
        print("We are scoring this board:")
        board_2 = make_board("board2.txt")
        print("Here is the colored board:")
        board_2 = make_mutable_board(board_2)
        colored_board = fill_board(board_2, row)
        print_filled_board(colored_board)
        score(colored_board)

    elif board_num == 3:
        print("We are scoring this board:")
        board_3 = make_board("board3.txt")
        print("Here is the colored board:")
        board_3 = make_mutable_board(board_3)
        colored_board = fill_board(board_3, row)
        print_filled_board(colored_board)
        score(colored_board)
        
    elif board_num == 4:
        print("We are scoring this board:")
        board_4 = make_board("board4.txt")
        print("Here is the colored board:")
        board_4 = make_mutable_board(board_4)
        colored_board = fill_board(board_4, row)
        print_filled_board(colored_board)
        score(colored_board)
        
    elif board_num == 5:
        print("We are scoring this board:")
        board_5 = make_board("board5.txt")
        print("Here is the colored board:")
        board_5 = make_mutable_board(board_5)
        colored_board = fill_board(board_5, row)
        print_filled_board(colored_board)
        score(colored_board)
        
    
if __name__ == '__main__':
    user_choice()
    
