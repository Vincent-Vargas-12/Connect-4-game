#pragma once

#include <iostream>
#include <string>

class Player{
    public:
    std::string name;
    std::string game_piece;
    int wins = 0;
    
    void print_won(){
        std::cout << "Player: " << name << " won!\n";
    }
    void print_wins(){
        std::cout << "Player: " << name << " has " << wins << " wins\n";
    }

    void get_name(){
        std::cout << name << " enter name: ";
        std::cin >> name;
        while(name.length() > 20){
            std::cout << "\nInvalid name: Please enter name with 20 characters or less: ";
            std::cin >> name;
        }
    }
   
    void get_game_piece(){
    std::cout << "Player **" << name << "** enter game piece: ";
    std::cin >> game_piece;
    while(game_piece.length() > 1){
      std::cout << "\nInvalid game piece: **" << name << "** Please enter 1 keyboard character for game piece: ";
      std::cin >> game_piece;
    }
    }

};

class Board{
    public:
    std::string **board;
    int column;
    int row;

    void allocate_and_fill(){
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

    void deallocate(){
        for(int i =0; i < row; i++){
        delete[] board[i];
        }
        delete[] board;
    }

    void print_board(){
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

    bool check_draw(){
        for(int i = 0; i < column; i++){
            if(board[0][i] == "-"){
            return false;
            }
        }
        return true;
        }

    bool check_win(Player& player1, Player& player2){
        int matches = 0;
        std::string winning_token = "";
        //check rows 
        for(int i = row - 1; i >= 0; i--){ //check from bottom up
            if(3 == matches){
            break;
            }
            for(int j = 0; j < column - 1; j++){  //check row from left to right
            if(board[i][j] == board[i][j+1] && board[i][j] != "-"){  //checking pairs adjecent
                matches += 1;
                if(matches == 3){  // need to match 3 pairs to see four in a row
                winning_token = board[i][j+1]; //assign winning_token to last token checked
                break; 
            }
            }
            else{
                matches = 0; //reset matches if one doesnt match
            }
            }
        }
        //check columns

        if(winning_token.empty()){
            for(int i = 0; i < column; i++){
            matches = 0;
            for(int j = row - 1; j > 0; j--){
                if(board[j][i] == board[j-1][i] && board[j][i] != "-"){
                matches += 1;
                if(matches == 3){
                    winning_token = board[j-1][i];
                    break;
                }
                }
                else{
                matches = 0;
                }
            }
            if(3 == matches){
                break;
            }
            }
        }

        //check diagonals
        // Diagonal win condition. Top left to bottom right. We check the next three tokens in the row and the next three rows to see if there is a diagonal win.
            if(matches != 3){
            matches = 0;
            for(int i = 0; i < column - 3; ++i)
            {
                if(matches == 3){
                break;
                }
                for(int j = 0; j < row - 3; ++j)
                {
                if (board[j][i] != "-" &&
                board[j][i] == board[j+1][i+1] && 
                board[j + 1][i + 1] == board[j+2][i+2] && 
                board[j + 2][i + 2] == board[j+3][i+3])
                {
                    matches = 3;
                    winning_token = board[j][i];
                    break;
                }
                }
            }
            }

            // Diagonal win condition. bottom left to top right. We check the next three tokens in the row and the previous three rows to see if there is a diagonal win.
            if(matches != 3){
            matches = 0;
            for(int i = 0; i < column - 3; ++i)
            {
                if(matches == 3){
                break;
                }
                for(int j = 3; j < row; ++j)
                {
                if (board[j][i] != "-" &&
                board[j][i] == board[j-1][i+1] && 
                board[j - 1][i + 1] == board[j-2][i+2] && 
                board[j - 2][i + 2] == board[j-3][i+3])
                {
                    matches = 3;
                    winning_token = board[j][i];
                    break;
                }
                }
            }
            }
            

        //if after row, column and diagnol checks if token winning token still empty return false
        if(winning_token == ""){
            return false;  
        }
        else{ // check which player won and print winning statement
            if(winning_token == player1.game_piece){
            player1.print_won();
            player1.wins += 1;
            player1.print_wins();
            return true;
            }
            else{
            player2.print_won();
            player2.wins += 1;
            player2.print_wins();
            return true;
            }
        }
        }
  
    };

/*
methods can be 
---new_match---
clears 
1 player names
2 tokens
4 wins
---rematch---
lets winner go first 
*/
class State{
    public:
    void new_match(Player& player1, Player& player2){
        player1.name = "Player 1";
        player2.name = "Player 2";

        player1.game_piece = "";
        player2.game_piece = "";

        player1.wins = 0;
        player2.wins = 0;
    }




};