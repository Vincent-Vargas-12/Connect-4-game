#include <iostream> // allows players to interact with gameboard
#include <string> //data to fill contailer
#include <vector> //container for set pieces
#include "connect4.hpp"
//#include <cstdlib> //used for clearing the terminal

void print_board (int column, int row, std::string **board);
bool check_win(int column, int row, std::string **board);
bool check_draw(int column, int row, std::string **board);

//global objects for player 1 & 2
player player1; 
player player2; 

int main() {
  player1.name = "player1";
  player2.name = "player2";

  int column = 7;
  int row = 6;
    //Self explanatory variables. decidedes how many rows and columns the board will have. 
    //allocate space for 2D array
    std::string **board = new std::string*[row];
    for (int i = 0; i < row; i++) {         
     board[i] = new std::string[column];
    }

    for(int i = 0; i < row; i++){
      for(int j = 0; j < column; j++){
        board[i][j] = "-";
      }
    }
    
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
      std::cin >> player1.game_piece;
    }

  print_board(column, row, board);

  //    std::string Token_One = " X ";  //player one token, " X " is a place holder for now
  //  std::string Token_Two = " O ";  //same as above, but for player 2 and also a place holder;


    while (swap_counter != row * column) { //when swap counter is equal to the number of rows and columns, the game is over since there are no more tokens at play
      int row_minus_one = row - 1;  //used for the zero-based arrya
      int row_counter = 0; //used to naviate through the rows
      std::cout << "Enter a valid column number \n";
      std::cin >> column_number;
        while(column_number > column || column_number < 0 || true == std::cin.fail()){  //ensure that the player can't pick a column that doesn't exist. forces them to pick a column;
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
        
        if(board[0][column_number - 1] == player1.game_piece || board[0][column_number - 1] == player2.game_piece) { //logic to make sure the player the token can be placed in a valid spot

          std::cout << "Column " << column_number << " is full. Please Select a different column \n"; //ensures player can't replace top value
          swap_counter--;
        } else {
          while(board[row_counter][column_number - 1] != player1.game_piece || board[row_counter][column_number - 1] != player1.game_piece){
          if(row_counter == row_minus_one) { //ensure the while loop does not run forever by placing the last token at the bottom of the row;
            board[row - 1][column_number - 1] = token;
            break;
          } else {
            if(board[row_counter + 1][column_number -1] == player1.game_piece || board[row_counter + 1][column_number - 1] == player2.game_piece){ //checks one space below
            board[row_counter][column_number - 1] = token; //places token on top the token below it.
            break;
            }
            row_counter++;
      }
          }
      }


  print_board(column, row, board);
  if(true == check_win(column, row, board)){
    std::cout << "Win detected\n";
    return 0;
  }
  if(true == check_draw(column, row, board)){
    std::cout << "Draw detected\n";
    return 0;
  }

  swap_counter++;
  std::cout << "There are " << (row * column) - swap_counter << " tokens left\n";
  }
  //deallocate board
  for(int i = 0; i < row; i++){
    delete[] board[i];
  }
  delete[] board;
  
  return 0;
}

void print_board (int column, int row, std::string **board){
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

bool check_draw(int column, int row, std::string **board){
  for(int i = 0; i < column; i++){
    if(board[0][i] == "-"){
    return false;
    }
  }
  
  return true;

}

bool check_win(int column, int row, std::string **board){
  int matches = 0;
  std::string winning_token = "";
  //check rows 
  for(int i = row - 1; i >= 0; i--){ //check from bottom up
    if(3 == matches){
      break;
    }
    for(int j = 0; j < column; j++){  //check row from left to right
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
  //check comulmns
  
  if(matches != 3){
    matches = 0;
    for(int i = 0; i < column; i++){
      if(3 == matches){
        break;
      }
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
    }
  }

  //check diagnol
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
          board[j + 1][i + 1] == board[j+2][j+2] && 
          board[j + 2][i + 2] == board[j+3][j+3])
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
