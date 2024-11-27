#pragma once

#include <iostream>
#include <string>

class player{
    public:
    std::string name;
    std::string game_piece;
    int wins = 0;
    
    void print_won(){
        std::cout << "Player: " << name << " won!" << std::endl;
    }
    void print_wins(){
        std::cout << "Player: " << name << " has " << wins << " wins" << std::endl;
    }
};

/*
methods can be
---printing_board---
---check_win---
---check_draw---
??
class board{
    public:
    std::string **board;

     void allocate_and_fill(board){
        board = new std::string*[row];
    
    for(int i = 0; i < row; i++){
        board[i] = new std::string[column];
    }

    for(int i = 0; i < row; i++){
        for(int j = 0; j < column; j++){
        board[i][j] = "-";
        }
    }
    }
    void print_board(int column, int row, std::string **board){
         for (int i = 0; i < row; i++) {          //print board
        for (int j = 0; j < column; j++) { 
            std::cout << " " << board[i][j] << " "; 
        }
        std::cout << "\n"; 
        int column_num = 1;
      if(i == row - 1){
        for(int k = 0; k < column; k++){
          std::cout << " " << column_num << " ";
          column_num++;
        }
        std::cout << " : Column"<< "\n";
      }
     }
     return;
    }



    
};


methods can be 
---rematch---
clears 
1 player names
2 tokens
3 board
4 wins
---new match---
clears board
lets winner go first 

class gamestate{
};
*/
