#include <iostream> // allows players to interact with gameboard
#include <string>   // data to fill contailer
#include <vector>   // container for set pieces
#include <cstdlib>  // used for clearing the terminal

int main() {
  system("clear"); //clears the terminal to display key info (board, text, etc.) Will need to use system("CLS") for Windows.
  int column = 7;
  int row = 6;

  //Self explanatory variables. decides how many rows and columns the board will have. For right now, they must be
  //pre-designated before starting the program, but will be changed later so the player's can make custom boards
  //standard board size for connect 4 is 7 by 6.

  std::string board[row][column]; //initalization of board

  for (int i = 0; i < row; i++) {          //fill board with "white space" or "blank spaces";
    for (int j = 0; j < column; j++) {
      board[i][j] = " - ";
    }
  }

  for (int i = 0; i < row; i++) {          //print board
        for (int j = 0; j < column; j++) { 
            std::cout << board[i][j]; 
        }
        std::cout << "\n"; 
        int column_num = 1;
      if(i == row - 1){
        for(int k = 0; k < column; k++){
          std::cout << " " << column_num << " ";
          column_num++;
        }
        std::cout << "\n";
      }
  }
  
  int swap_counter = 0; //counter that counts how many tokens have been places. currently used to end the game, but will 
  //determine ties in the future

  int column_number; //variable player uses to decide which column to pick

  std::string token;  //string that determines which token will be used

  std::string Token_One = " X ";  //player one token, " X " is a place holder for now

  std::string Token_Two = " O ";  //same as above, but for player 2 and also a place holder;


  while (swap_counter != row * column) { //when swap counter is equal to the number of rows and columns, the game is over since there are no more tokens at play
    int row_minus_one = row - 1;  //used for the zero-based matrix
    int row_counter = 0; //used to navigate through the rows when a column is decided. Is at zero due to the zero-based matrix
    
     if (swap_counter % 2 == 0){  //since there is only two players, we can use % to alternate between player 1 and player 2
        token = Token_One;         //If it's an even number, it's player 1's turn
      } else {                     //
        token = Token_Two;         //If odd, it's player 2's turn. 
      }

    std::cout << "Player " << token << " Enter a column number \n";
    std::cin >> column_number;
      while(column_number > column || column_number < 0){  //ensure that the player can't pick a column that doesn't exist. Forces them to pick a column;
        std::cout << "Invalid Number. Please enter a valid column number \n";
        std::cin >> column_number;
      }
      
      system("clear"); //clears the terminal to display key info (board, text, etc.) Will need to use system("CLS") for Windows.
      
      if(board[0][column_number - 1] == Token_One || board[0][column_number - 1] == Token_Two) { //logic to make sure the player the token can be placed in a valid spot

        std::cout << "Column " << column_number << " is full. Please Select a different column \n"; //ensures player can't replace top value
        swap_counter--; //by subtracting the swap counter here, we negate the swap counter increasing at the end, preventing invaild turns from increasing the swap counter
      } else {
        while(board[row_counter][column_number - 1] != Token_One || board[row_counter][column_number - 1] != Token_Two){
        if(row_counter == row_minus_one) { //ensure the while loop does not run forever by placing the last token at the bottom of the row. Since a fresh board will only have blank space, this ensure that the token will be placed on the last row if the column is empty
          board[row_counter][column_number - 1] = token;
          break;
        } else {
          if(board[row_counter + 1][column_number -1] == Token_One || board[row_counter + 1][column_number - 1] == Token_Two){ //checks one space below to see if a token exist
          board[row_counter][column_number - 1] = token; //places token on top the token below it.
          break;
          }
          row_counter++; //used to navigate the rows per loop;
     }
        }
      }
    system("clear"); //clears the terminal to display key info (board, text, etc.). use system "cls";



    for (int i = 0; i < row; i++) {          //prints board
        for (int j = 0; j < column; j++) { 
            std::cout << board[i][j]; 
        }
        std::cout << "\n"; 
        int column_num = 1;
      if(i == row - 1){
        for(int k = 0; k < column; k++){
          std::cout << " " << column_num << " ";
          column_num++;
        }
        std::cout << "\n";
      }
  }

  //Win's will be annoucned after the board prints out the final time, so the players can see the board once the game is over.
  
  //Vertical win check. Since the last token placed on top is required for a vertical win, we check the last token placed and the bottom three rows in the same column to check if there is a vertical win.

    if(board[row_counter][column_number - 1] == token && board[row_counter + 1][column_number - 1] == token && board[row_counter + 2][column_number - 1] == token && board[row_counter + 3][column_number - 1] == token) {
        if(token == Token_One){
        std::cout << "Player 1 wins through a vertical victory\n\n";
        } else {
          std::cout << "Player 2 wins though a vertical victory\n\n";
        }
        return 0; //No main menu yet, so we will have the program exit when a win is detected;
    }

    //Horizontal win condition. Iterate through a row and check if there is 4 in a row. At i, we check the next three tokens, and if they are the same, it's a horizontal victory.
    //The reason i starts at column_number - 3 and ends at column_number + 3 is to not waste time iterating the entire row. we only need to check roughly where the last token was placed,
    //so we use the player's column_number input and check the rows a few spaces in front and behind from where the token was placed.
    
    
    //essentially, we pick a column number a few spaces behind the last place token, and iterate a few spaces ahead of it's last location to check for a four in a row

    for(int i = column_number - 4; i < column_number + 4; ++i){
      if(board[row_counter][i] == token && board[row_counter][i + 1] == token && board[row_counter][i + 2] == token && board[row_counter][i + 3] == token){
        if(token == Token_One){
        std::cout << "Player 1 wins through a horizontal victory\n\n";
        } else {
          std::cout << "Player 2 wins though a horizontal victory\n\n";
        }
        return 0; //No main menu yet, so we will have the program exit when a win is detected;
      }
    }

  // Diagonal win condition. Top left to bottom right. We check the next three tokens in the row and the next three rows to see if there is a diagonal win.
    for(int i = 0; i < column - 3; ++i)
    {
      for(int j = 0; j < row - 3; ++j)
      {
        if (board[j][i] == token && 
        board[j + 1][i + 1] == token && 
        board[j + 2][i + 2] == token && 
        board[j + 3][i + 3] == token)
        {
          if (token == Token_One)
          {
            std::cout << "Player 1 wins through a diagonal victory\n\n";
          }
          else
          {
            std::cout << "Player 2 wins though a diagonal victory\n\n";
          }
          return 0; 
        }
      }
    }
    
    /* -  -  -  -  -  -  - 
       -  -  -  X  -  -  - 
       -  -  X  O  -  -  - 
       -  X  O  O  -  -  - 
       X  O  O  X  X  -  - 
       1  2  3  4  5  6  7
       Player 1 wins through a diagonal victory
    */

    // Diagonal win condition. bottom left to top right. We check the next three tokens in the row and the previous three rows to see if there is a diagonal win.

    for(int i = 0; i < column - 3; ++i)
    {
      for(int j = 3; j < row; ++j)
      {
        if (board[j][i] == token && 
        board[j - 1][i + 1] == token && 
        board[j - 2][i + 2] == token && 
        board[j - 3][i + 3] == token)
        {
          if (token == Token_One)
          {
            std::cout << "Player 1 wins through a diagonal victory\n\n";
          }
          else
          {
            std::cout << "Player 2 wins though a diagonal victory\n\n";
          }
          return 0;
        }
      }
    }

    /*
     -  -  -  -  -  -  - 
     O  -  -  -  -  -  - 
     X  O  -  -  -  -  - 
     O  X  O  -  -  -  - 
     X  O  X  O  -  X  X 
     1  2  3  4  5  6  7
     Player 2 wins though a diagonal victory
    */






  swap_counter++;
  std::cout << "There are " << (row * column) - swap_counter << " tokens left\n";
  }
}


//still need to add the win algorthim, and program the main menu with player selections. Once covered, the main gameplay
//of the project is completed, which needs to be done first before other features are implemented
//Thanks to the 2D array, we were able to make the 2D array scaleable and can allow the player to make them able to choose
//how many rows and columns they want. Power-ups or potentially an implementation to an actual game engine might be possible
//over thanksgiving break

