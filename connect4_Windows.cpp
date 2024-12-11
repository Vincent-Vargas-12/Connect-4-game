#include <iostream> // allows players to interact with gameboard
#include <string> //data to fill contailer
#include <vector> //container for set pieces
#include "connect4.hpp"
#include <cstdlib> //used for clearing the terminal

Player player1; 
Player player2; 
Board connect_board;
State game_state;

void connect_4(int option){
  if(2 == option){
  player1.get_name();
  player2.get_name();
  while(player2.name == player1.name){
    std::cout << "\nError: Same name as player 1\n";
    player2.name = "Player 2";
    player2.get_name();
  }
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
    bool quit = false;
    //ask for player input for tokens here instead
    if(2 == option){
    player1.get_game_piece();
    player2.get_game_piece();
    while(player2.game_piece == player1.game_piece){
      std::cout << "\nERROR: Same game piece as player 1\n";
      player2.get_game_piece();
    }
    }
   
    system ("cls");
    connect_board.print_board();

    while (swap_counter != connect_board.row * connect_board.column) { //when swap counter is equal to the number of rows and columns, the game is over since there are no more tokens at play
      int row_minus_one = connect_board.row - 1;  //used for the zero-based arrya
      int row_counter = 0; //used to naviate through the rows
      while(true){
        if(swap_counter % 2 == 0){
            std::cout << player1.name;
        } else {
            std::cout << player2.name;
        }
        std::cout << "'s turn.\nEnter a valid column number, or type 'resign' to resign \n";
        std::cin >> string_column_number;
        if(string_column_number == "resign" or string_column_number == "Resign"){
          if(swap_counter % 2 == 0){
            std::cout << player1.name << " resigned\n";
            player2.wins += 1;
            player2.print_wins();
          } else {
            std::cout << player2.name << " resigned\n";
            player1.wins += 1;
            player1.print_wins();
          }
          quit = true;
          break;
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
        
        if(true == quit){
          break;
        }
        if (swap_counter % 2 == 0){  //since there is only two players,
          token = player1.game_piece;         //we can use % to alternate between
        } else {                     //player 1 and player 2 tokens
          token = player2.game_piece;
        }
        
        if(connect_board.board[0][column_number - 1] == player1.game_piece || connect_board.board[0][column_number - 1] == player2.game_piece) { //logic to make sure the player the token can be placed in a valid spot
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
    
    system ("cls"); //For windows, use " System ("cls") " in order for the terminal to properly clear
    connect_board.print_board();
  if(true == quit){
    std::cout << "Player resigned\n";
    return;
  }
  if(true == connect_board.check_win(player1, player2)){
    std::cout << "Win detected\n";
    connect_board.deallocate();
    return;
  }         
  if(true == connect_board.check_draw()){
    std::cout << "Draw detected\n";
    connect_board.deallocate();
    return;
  }

  swap_counter++;
  std::cout << "There are " << (connect_board.row * connect_board.column) - swap_counter << " tokens left\n";
  }
}

int central_menu(int cursor){
    system("cls"); 
    int selection;
  std::cout << "XOXOXOXOXOXOXOOXOXO\n";
  std::cout << "O                 X\n";
  std::cout << "X     Connect 4   O\n";
  std::cout << "O                 X\n";
  std::cout << "XOXOXOXOXOXOXOOXOXO\n\n\n";
    std::cout << "Welcome to connect 4. Type 1 to start a game, or type 2 to quit the program \n";
    std::cin >> selection;
    while(selection > 2 || selection < 1){
        std::cout << "please type either 1 or 2 \n";
        std::cin >> selection;
    }
    if(selection == 1){
        cursor = 1;
        return cursor = 1;
    }
    cursor = 2;
    return cursor = 2;
}


int main() {
//Objects for Player class and Board class  
  int option;
  int cursor;
  //Defualt names

  player1.name = "Player 1";
  player2.name = "Player 2";
  cursor = central_menu(cursor);

  if(cursor == 2){ 
    std::cout << "Qutting Connect 4\n";
    return 0;
  }
  connect_4(2);
  
  while(true){
  std::cout << "Type 1 for Rematch, Type 2 for New Match, Type 3 to go the main menu, Type 4 to End Program: ";
  std::cin >> option;
  while(option < 1 || option > 4){
    std::cout << "Invalid Input: Type 1 for Rematch, Type 2 for New Match, Type 3 to go to the main menu, or Type 4 to End Program: ";
    std::cin >> option;
  }
  if(1 == option){
    //do things for Rematch
    //like let other person go first, should be it
    std::cout << "Rematch!\n";
    connect_4(1);
  }
  else if(2 == option){
    //do things for New match
    std::cout << "New Match!\n";
    game_state.new_match(player1, player2);
    connect_4(2);
  }
  else if(3 == option){
    cursor = central_menu(cursor);
    if(cursor == 1){
        game_state.new_match(player1, player2);
        connect_4(2);
    } else {
      std::cout << "Quitting Connect 4. Thanks for Playing!\n";
      return 0;
    }
  }
  else if(4 == option){
    std::cout << "Quitting Connect 4. Thanks for Playing!\n";
    return 0;
  }
  }
  return 0;
}