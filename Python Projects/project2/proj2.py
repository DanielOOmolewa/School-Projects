"""
0;136;0cFile: proj2.py
Author: Daniel Omolewa
Date: 11/6/2019
Section: 42
E-mail: o24@umbc.edu
Description:
"""
from proj2_ui import print_board

VALID_LINES = [[1,2],[1,3],[1,4],[1,5],[1,6],
               [2,3],[2,4],[2,5],[2,6],[2,1],
               [3,4],[3,5],[3,6],[3,1],[3,2],
               [4,5],[4,6],[4,1],[4,2],[4,3],
               [5,6],[5,1],[5,2],[5,3],[5,4],
               [6,1],[6,2],[6,3],[6,4],[6,5]]

               
def check_line_legal(player_move,lines1,lines2):
    player_line = player_move.strip().split()
    for i in range(len(player_line)):
        player_line[i] = int(player_line[i])
    reverse1 = reverse_move_list(lines1)
    reverse2 = reverse_move_list(lines2)
    
    if player_line not in VALID_LINES:
        print("Hey, that's illegal!")
        return False
    if player_line in lines1 or player_line in reverse1:
        print("Hey, that's illegal!")
        return False
    if player_line in lines2 or player_line in reverse2:
        print("Hey, that's illegal!")
        return False
    return True

def make_line_list(move):
    line = move.strip().split()
    for i in range(len(line)):
        line[i] = int(line[i])
    return line

def reverse_move_list(moves):
    reverse_list = []
    for i in range(len(moves)-1,-1,-1):
        line = moves[i]
        corners = []
        for j in range(len(line)-1,-1,-1):
            corners.append(line[j])
        reverse_list.append(corners)
    return reverse_list

def check_triangle(moves):
    if len(moves) > 0:
        common1 = 0
        common_corner_1 = moves[0][0]
        common_corner_2 = moves[0][1]
        while common1 <= 2: #and common2 < 2:
            for i in range(len(moves)):
                #common_corner_1 = moves[i][0]
                #common_corner_2 = moves[i][1]
                if common_corner_1 in moves[i] or common_corner_2 in moves[i]:
                    print("._.")
                    if common_corner_1 in moves[i]:
                        print(".")
                        common1 += 1
                        if common_corner_2 in moves[i]:
                            print("..")
                            common1 += 1
        if common1 > 2:
            print("...")
            return True
    


if __name__ == '__main__':
    char1 = input("Hello, what character would player 1 like to use? ")
    char2 = input("Hello, what character would player 2 like to use? ")
    p1_lines = []
    p2_lines = []
    someone_lost = False
    print_board(p1_lines,char1,p2_lines,char2)
    while someone_lost == False:
        p1_move = input("Enter a line for player 1: ")
        check = check_line_legal(p1_move,p1_lines,p2_lines)
        while check == False:
            p1_move = input("Enter a line for player 1: ")
            check = check_line_legal(p1_move,p1_lines,p2_lines)
        p1_lines.append(make_line_list(p1_move))
        print_board(p1_lines,char1,p2_lines,char2)
        someone_lost = check_triangle(p1_lines)
        p2_move = input("Enter a line for player 2: ")
        check = check_line_legal(p2_move,p1_lines,p2_lines)
        while check == False:
            p2_move = input("Enter a line for player 2: ")
            check = check_line_legal(p2_move,p1_lines,p2_lines)
        p2_lines.append(make_line_list(p2_move))
        print_board(p1_lines,char1,p2_lines,char2)
        someone_lost = check_triangle(p2_lines)

        
