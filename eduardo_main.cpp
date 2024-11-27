#include <iostream> // allows players to interact with gameboard
#include <string> //data to fill contailer
#include <vector> //container for set pieces
#include "connect4.hpp"
//#include <cstdlib> //used for clearing the terminal


//global objects for player 1 & 2 
// and game Board
Player player1; 
Player player2; 
Board connect_board;

int main() {
  player1.name = "player1";
  player2.name = "player2";

  connect_board.column = 7;
  connect_board.row = 6;  
  
    //Self explanatory variables. decidedes how many rows and columns the board will have. 
    //allocate space for 2D array
    connect_board.allocate_and_fill();
    
    int swap_counter = 0; //counter that counts how many tokens have been places. currently used to end the game, but will 
    //determine ties in the future
    int column_number; //variable player uses to decide which column to pick
    std::string token;  //string that determines which token will be used

    //ask for player input for tokens here instead
    std::cout << "Player (player1.name) enter game piece: ";
    std::cin >> player1.game_piece;
    while(player1.game_piece.length() > 1){
      std::cout << "Invalid game piece. Please enter valid game piece: ";
      std::cin >> player1.game_piece;
    }
    std::cout << "Player (player2.name) enter game piece: ";
    std::cin >> player2.game_piece;
    while(player2.game_piece.length() > 1 || (player2.game_piece == player1.game_piece)){
      std::cout << "Invalid game piece Or same game piece as player 1. Please enter valid game piece: ";
      std::cin >> player2.game_piece;
    }

    connect_board.print_board();



    while (swap_counter != connect_board.row * connect_board.column) { //when swap counter is equal to the number of rows and columns, the game is over since there are no more tokens at play
      int row_minus_one = connect_board.row - 1;  //used for the zero-based arrya
      int row_counter = 0; //used to naviate through the rows
      std::cout << "Enter a valid column number \n";
      std::cin >> column_number;
        while(column_number > connect_board.column || column_number < 1 || true == std::cin.fail()){  //ensure that the player can't pick a column that doesn't exist. forces them to pick a column;
          std::cin.clear();
          std::cin.ignore(256,'\n');
          std::cout << "Invalid Number. Please enter a valid column number \n";
          std::cin >> column_number;
        }
        
        //system("cls"); //clears the terminal to display key info (board, text, etc.)

        if (swap_counter % 2 == 0){  //since there is only two players,
          token = player1.game_piece;         //we can use % to alternate between
        } else {                     //player 1 and player 2 tokens
          token = player2.game_piece;
        }
        
        if(connect_board.board[0][column_number - 1] == player1.game_piece || connect_board.board[0][column_number - 1] == player2.game_piece) { //logic to make sure the player the token can be placed in a valid spot
          std::cout << "Column " << column_number << " is full. Please Select a different column \n"; //ensures player can't replace top value
          swap_counter--;
        } 
        else {
          while(connect_board.board[row_counter][column_number - 1] != player1.game_piece || connect_board.board[row_counter][column_number - 1] != player1.game_piece){
          if(row_counter == row_minus_one) { //ensure the while loop does not run forever by placing the last token at the bottom of the row;
            connect_board.board[connect_board.row - 1][column_number - 1] = token;
            break;
          } 
          else {
            if(connect_board.board[row_counter + 1][column_number -1] == player1.game_piece || connect_board.board[row_counter + 1][column_number - 1] == player2.game_piece){ //checks one space below
            connect_board.board[row_counter][column_number - 1] = token; //places token on top the token below it.
            break;
            }
            row_counter++;
      }
          }
      }
    
    
    connect_board.print_board();
    
  if(true == connect_board.check_win(player1, player2)){
    std::cout << "Win detected\n";
    connect_board.deallocate();
    return 0;
  }         //board.check_win
  if(true == connect_board.check_draw()){
    connect_board.deallocate();
    std::cout << "Draw detected\n";
    return 0;
  }

  swap_counter++;
  std::cout << "There are " << (connect_board.row * connect_board.column) - swap_counter << " tokens left\n";
  }

  return 0;
}

