#include <iostream> // allows players to interact with gameboard
#include <string> //data to fill contailer
#include <vector> //container for set pieces
#include "connect4.hpp"
//#include <cstdlib> //used for clearing the terminal



int main() {
//Objects for Player class and Board class  
Player player1; 
Player player2; 
Board connect_board;
  //Defualt names
  player1.name = "Player 1";
  player2.name = "Player 2";
  
  player1.get_name();
  player2.get_name();
  while(player2.name == player1.name){
    std::cout << "\nError: Same name as player 1\n";
    player2.name = "Player 2";
    player2.get_name();
  }
  connect_board.column = 7;
  connect_board.row = 6;  
  
    //Self explanatory variables. decidedes how many rows and columns the board will have. 
    
    //allocate space for 2D array
    connect_board.allocate_and_fill();
    
    int swap_counter = 0; //counter that counts how many tokens have been places. currently used to end the game, but will 
    //determine ties in the future
    int column_number; //variable player uses to decide which column to pick
    std::string string_column_number;
    std::string token;  //string that determines which token will be used
    
    //ask for player input for tokens here instead
    player1.get_game_peice();
    player2.get_game_peice();
    while(player2.game_piece == player1.game_piece){
      std::cout << "\nERROR: Same game piece as player 1\n";
      player2.get_game_peice();
    }

    connect_board.print_board();



    while (swap_counter != connect_board.row * connect_board.column) { //when swap counter is equal to the number of rows and columns, the game is over since there are no more tokens at play
      int row_minus_one = connect_board.row - 1;  //used for the zero-based arrya
      int row_counter = 0; //used to naviate through the rows
      while(true){
        std::cout << "Enter a valid column number \n";
        std::cin >> string_column_number;
        if(string_column_number == "quit" or string_column_number == "Quit"){
          std::cout << "say which player quit give other player point\n";
          return 0;
        }
        bool invalid = false;
        for(char c : string_column_number){
          if(false == isdigit(c)){
            std::cout << "Invalid Input. Please "; // next iteration of while loop finishes sentence
            invalid = true;
            break;
          }
        }
        if(invalid){
          continue;
        }
          column_number = stoi(string_column_number);
          if(column_number > connect_board.column || column_number < 1){  //ensure that the player can't pick a column that doesn't exist. forces them to pick a column;
            std::cout << "Invalid number. Please "; // next iteration of while loop finishes sentence
            continue;
          }
        break;
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
  }         
  if(true == connect_board.check_draw()){
    std::cout << "Draw detected\n";
    connect_board.deallocate();
    return 0;
  }
  //after game ends either from a win or draw
  //prompt users for rematch, new mathch or to end program

  swap_counter++;
  std::cout << "There are " << (connect_board.row * connect_board.column) - swap_counter << " tokens left\n";
  }

  return 0;
}

