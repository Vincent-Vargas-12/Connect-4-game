#include <iostream> // allows players to interact with gameboard
#include <string>   // data to fill contailer
#include <vector>   // container for set pieces



//Almost the same code from the main file, but i removed certain checks for the token placement. this is just to check for win conditions.
void win_check(std::string board[6][7], int column_number, std::string token){
int row = 6;
int column = 7;
int row_minus_one = row - 1;  //used for the zero-based matrix
int row_counter = 0;  
    std::cout << "Final Token was placed in column " << column_number << "\n\n";
        while(board[row_counter][column_number - 1] != token || board[row_counter][column_number - 1] != " 0 " ){
        if(row_counter == row_minus_one) { //ensure the while loop does not run forever by placing the last token at the bottom of the row. Since a fresh board will only have blank space, this ensure that the token will be placed on the last row if the column is empty
          board[row_counter][column_number - 1] = token;
          break;
        } else {
          if(board[row_counter + 1][column_number -1] == token || board[row_counter + 1][column_number -1] == " 0 "){ //checks one space below to see if a token exist
          board[row_counter][column_number - 1] = token; //places token on top the token below it.
          break;
          }
          row_counter++; //used to navigate the rows per loop;
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

    if(board[row_counter][column_number - 1] == token && board[row_counter + 1][column_number - 1] == token && board[row_counter + 2][column_number - 1] == token && board[row_counter + 3][column_number - 1] == token) {
        std::cout << "Player 1 wins through a vertical victory\n\n";
        return; //No main menu yet, so we will have the program exit when a win is detected;
    }

    //Horizontal win condition. Iterate through a row and check if there is 4 in a row. At i, we check the next three tokens, and if they are the same, it's a horizontal victory.
    //The reason i starts at column_number - 3 and ends at column_number + 3 is to not waste time iterating the entire row. we only need to check roughly where the last token was placed,
    //so we use the player's column_number input and check the rows a few spaces in front and behind from where the token was placed.
    
    
    //essentially, we pick a column number a few spaces behind the last place token, and iterate a few spaces ahead of it's last location to check for a four in a row

    for(int i = column_number - 4; i < column_number + 4; ++i){
      if(board[row_counter][i] == token && board[row_counter][i + 1] == token && board[row_counter][i + 2] == token && board[row_counter][i + 3] == token){
        std::cout << "Player 1 wins through a horizontal victory\n\n";
        return; //No main menu yet, so we will have the program exit when a win is detected;
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
            std::cout << "Player 1 wins through a Negative diagonal victory\n\n";
          return; 
        }
      }
    }

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
            std::cout << "Player 1 wins through a Positive diagonal victory\n\n";
            return;
        }
      }
    }

    std::cout << "Final token placed. The game is a tie\n";
}


int main() {
  system("clear"); //clears the terminal to display key info (board, text, etc.) Will need to use system("CLS") for Windows.
  int column = 7;
  int row = 6;

  //Self explanatory variables. decides how many rows and columns the board will have. For right now, they must be
  //pre-designated before starting the program, but will be changed later so the player's can make custom boards
  //standard board size for connect 4 is 7 by 6.


  std::string token;  //string that determines which token will be used

  //I shuffled the code for the testing purposes. The way the tests work is by simulating the game. The follwing boards
  // are the standard 6 by 7 board, and the win check takes three inputs: the board, the column number, and the token. the boards
  //are designed to be before the last token is placed for a win. Then, the function simulates the token placement, and 
  //checks for the win condition and prints out the results as if it was like the actual game. 

  std::cout << " Board 1 \n";

  std::string board_1[6][7] = {
    {" - ", " - ", " - ", " - ", " - ", " - ", " - "},
    {" - ", " - ", " - ", " - ", " - ", " - ", " - "},
    {" - ", " - ", " - ", " - ", " - ", " - ", " - "},
    {" - ", " - ", " - ", " - ", " - ", " 0 ", " X "},
    {" - ", " - ", " - ", " - ", " - ", " 0 ", " X "},
    {" - ", " - ", " - ", " - ", " - ", " 0 ", " X "},
  };

  win_check(board_1, 7, " X ");
  std::cout <<" ------------This ends the vertical win condition portion \n\n";

  std::cout << " Board 2 \n";

  std::string board_2[6][7] = {
    {" - ", " - ", " - ", " - ", " - ", " - ", " - "},
    {" - ", " - ", " - ", " - ", " - ", " - ", " - "},
    {" - ", " - ", " - ", " - ", " - ", " - ", " - "},
    {" - ", " - ", " - ", " - ", " - ", " 0 ", " X "},
    {" - ", " 0 ", " 0 ", " 0 ", " - ", " 0 ", " X "},
    {" - ", " X ", " X ", " X ", " - ", " 0 ", " X "},
  };

  win_check(board_2, 5, " X ");
 
  std::cout << " Board 3 \n"; 
  std::string board_3[6][7] = {
    {" - ", " - ", " - ", " - ", " - ", " - ", " - "},
    {" - ", " - ", " - ", " - ", " - ", " - ", " - "},
    {" - ", " - ", " - ", " - ", " - ", " - ", " - "},
    {" - ", " - ", " - ", " - ", " - ", " 0 ", " X "},
    {" - ", " 0 ", " 0 ", " - ", " 0 ", " 0 ", " X "},
    {" - ", " X ", " X ", " - ", " X ", " 0 ", " X "},
  };

  win_check(board_3, 4, " X ");

    std::cout << " Board 4 \n";
    std::string board_4[6][7] = {
    {" - ", " - ", " - ", " - ", " - ", " - ", " - "},
    {" - ", " - ", " - ", " - ", " - ", " - ", " - "},
    {" - ", " - ", " - ", " - ", " - ", " - ", " - "},
    {" - ", " - ", " - ", " - ", " - ", " 0 ", " X "},
    {" - ", " 0 ", " - ", " 0 ", " 0 ", " 0 ", " X "},
    {" - ", " X ", " - ", " X ", " X ", " 0 ", " X "},
  };

  win_check(board_4, 3, " X ");

    std::cout << " Board 5 \n";
    std::string board_5[6][7] = {
    {" - ", " - ", " - ", " - ", " - ", " - ", " - "},
    {" - ", " - ", " - ", " - ", " - ", " - ", " - "},
    {" - ", " - ", " - ", " - ", " 0 ", " - ", " - "},
    {" - ", " - ", " X ", " X ", " X ", " 0 ", " X "},
    {" - ", " 0 ", " 0 ", " 0 ", " X ", " 0 ", " X "},
    {" - ", " X ", " X ", " X ", " 0 ", " 0 ", " X "},
  };

  win_check(board_5, 2, " X ");

    std::cout << " Board 6 \n";
    std::string board_6[6][7] = {
    {" - ", " - ", " - ", " - ", " - ", " - ", " - "},
    {" - ", " - ", " - ", " - ", " - ", " - ", " - "},
    {" - ", " X ", " X ", " 0 ", " - ", " - ", " - "},
    {" - ", " 0 ", " 0 ", " X ", " - ", " 0 ", " X "},
    {" - ", " 0 ", " 0 ", " 0 ", " X ", " 0 ", " X "},
    {" - ", " X ", " X ", " X ", " 0 ", " 0 ", " X "},
  };

    std::cout << " Board 16 \n"; 
  std::string board_16[6][7] = {
    {" - ", " - ", " - ", " - ", " - ", " - ", " - "},
    {" - ", " - ", " - ", " - ", " - ", " - ", " - "},
    {" - ", " - ", " - ", " - ", " - ", " - ", " - "},
    {" - ", " - ", " - ", " - ", " - ", " 0 ", " X "},
    {" - ", " 0 ", " 0 ", " - ", " 0 ", " 0 ", " X "},
    {" - ", " X ", " X ", " 0 ", " X ", " 0 ", " X "},
  };
  win_check(board_16, 1, " X ");
    std::cout <<" ------------This ends the Horizontal win condition portion \n\n";
    
    std::cout << " Board 7 \n";
    std::string board_7[6][7] = {
    {" - ", " - ", " - ", " - ", " - ", " - ", " - "},
    {" - ", " X ", " - ", " - ", " - ", " - ", " - "},
    {" - ", " X ", " - ", " 0 ", " - ", " - ", " - "},
    {" - ", " 0 ", " 0 ", " X ", " - ", " 0 ", " X "},
    {" - ", " 0 ", " 0 ", " 0 ", " X ", " 0 ", " X "},
    {" - ", " X ", " X ", " X ", " 0 ", " 0 ", " X "},
  };
 win_check(board_7, 3, " X ");

    std::cout << " Board 8 \n";
    std::string board_8[6][7] = {
    {" - ", " - ", " - ", " - ", " - ", " - ", " - "},
    {" - ", " X ", " - ", " - ", " - ", " - ", " - "},
    {" - ", " X ", " X ", " - ", " - ", " - ", " - "},
    {" - ", " 0 ", " 0 ", " - ", " 0 ", " 0 ", " X "},
    {" - ", " 0 ", " 0 ", " 0 ", " X ", " 0 ", " X "},
    {" - ", " X ", " X ", " X ", " 0 ", " 0 ", " X "},
  };

  win_check(board_8, 4, " X ");
    std::cout << " Board 9 \n";
    std::string board_9[6][7] = {
    {" - ", " - ", " - ", " - ", " - ", " - ", " - "},
    {" - ", " X ", " - ", " - ", " - ", " - ", " - "},
    {" - ", " X ", " X ", " - ", " - ", " 0 ", " 0 "},
    {" - ", " 0 ", " 0 ", " X ", " - ", " X ", " X "},
    {" - ", " 0 ", " 0 ", " 0 ", " - ", " 0 ", " X "},
    {" - ", " X ", " X ", " X ", " 0 ", " 0 ", " X "},
  };

  win_check(board_9, 5, " X ");
  std::cout <<" ------------This ends the negative diagonal win condition portion \n\n";

    std::cout << " Board 10 \n";
    std::string board_10[6][7] = {
    {" - ", " - ", " - ", " - ", " X ", " - ", " - "},
    {" - ", " - ", " - ", " - ", " 0 ", " - ", " - "},
    {" - ", " - ", " X ", " X ", " 0 ", " - ", " 0 "},
    {" - ", " X ", " 0 ", " X ", " 0 ", " 0 ", " X "},
    {" - ", " 0 ", " 0 ", " 0 ", " X ", " 0 ", " X "},
    {" - ", " X ", " X ", " X ", " 0 ", " 0 ", " X "},
  };

  win_check(board_10, 4, " X ");
    
    std::cout << " Board 11 \n";
    std::string board_11[6][7] = {
    {" - ", " - ", " - ", " - ", " - ", " - ", " - "},
    {" - ", " - ", " - ", " X ", " 0 ", " - ", " 0 "},
    {" - ", " - ", " X ", " X ", " 0 ", " - ", " 0 "},
    {" - ", " X ", " 0 ", " X ", " 0 ", " 0 ", " X "},
    {" - ", " 0 ", " 0 ", " 0 ", " X ", " 0 ", " X "},
    {" - ", " X ", " X ", " X ", " 0 ", " 0 ", " X "},
  };
  
  win_check(board_11, 5, " X ");
    
    std::cout << " Board 12 \n";
    std::string board_12[6][7] = {
    {" - ", " - ", " - ", " - ", " X ", " - ", " - "},
    {" - ", " - ", " - ", " X ", " 0 ", " - ", " 0 "},
    {" - ", " - ", " - ", " X ", " 0 ", " - ", " 0 "},
    {" - ", " X ", " 0 ", " X ", " 0 ", " 0 ", " X "},
    {" - ", " 0 ", " 0 ", " 0 ", " X ", " 0 ", " X "},
    {" - ", " X ", " X ", " X ", " 0 ", " 0 ", " X "},
  };

   win_check(board_12, 3, " X ");

    std::cout << " Board 13 \n";
    std::string board_13[6][7] = {
    {" - ", " - ", " - ", " - ", " X ", " - ", " - "},
    {" - ", " - ", " - ", " X ", " 0 ", " - ", " 0 "},
    {" - ", " - ", " X ", " X ", " 0 ", " - ", " 0 "},
    {" - ", " - ", " 0 ", " X ", " 0 ", " 0 ", " X "},
    {" - ", " 0 ", " 0 ", " 0 ", " X ", " 0 ", " X "},
    {" - ", " X ", " X ", " X ", " 0 ", " 0 ", " X "},
  };

  win_check(board_13, 2, " X ");
  
  std::cout <<" ------------This ends the Positive diagonal win condition portion \n\n";

  std::cout << " Board 14 \n";
    std::string board_14[6][7] = {
    {" - ", " 0 ", " 0 ", " X ", " 0 ", " X ", " 0 "},
    {" 0 ", " X ", " X ", " X ", " 0 ", " X ", " 0 "},
    {" X ", " 0 ", " 0 ", " X ", " 0 ", " X ", " 0 "},
    {" 0 ", " X ", " X ", " 0 ", " X ", " 0 ", " X "},
    {" X ", " 0 ", " 0 ", " 0 ", " X ", " 0 ", " X "},
    {" 0 ", " X ", " X ", " 0 ", " X ", " 0 ", " X "},
  };
  
  win_check(board_14, 1, " X ");

    std::cout << " Board 15 \n";
    std::string board_15[6][7] = {
    {" 0 ", " 0 ", " 0 ", " - ", " 0 ", " 0 ", " 0 "},
    {" X ", " X ", " X ", " 0 ", " X ", " X ", " X "},
    {" 0 ", " 0 ", " 0 ", " X ", " 0 ", " 0 ", " 0 "},
    {" X ", " X ", " X ", " 0 ", " X ", " X ", " X "},
    {" X ", " 0 ", " 0 ", " X ", " 0 ", " 0 ", " 0 "},
    {" X ", " X ", " X ", " 0 ", " X ", " X ", " X "},
  };
  
  win_check(board_15, 4, " X ");

  std::cout <<" ------------This ends the Tie condition portion \n\n";
}