#include <iostream> // allows players to interact with gameboard
#include <string>   // data to fill container
#include <cstdlib>  // used for clearing the terminal

int main() {
    system("clear"); //use 'cls' for windows, clear for mac and linux;
    std::cout << "Welcome to Connect 4 \n\n";
    
    int column = 7;
    int row = 6;

    // Get player names
    std::string playerOneName, playerTwoName;
    std::cout << "Enter Player 1's name: ";
    std::getline(std::cin, playerOneName); // Get Player 1's name

    std::cout << "Enter Player 2's name: ";
    std::getline(std::cin, playerTwoName); // Get Player 2's name

    std::string Token_One = " X ";  // Player 1's token
    std::string Token_Two = " O ";  // Player 2's token

    // Start the game loop for rematch functionality
    while (true) {
        std::string board[row][column]; // Initialize the board

        // Fill the board with blank spaces
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++) {
                board[i][j] = " - ";
            }
        }

        int swap_counter = 0; // counter for how many tokens have been placed
        int column_number; // column number for the player's move
        std::string token; // token to be placed (X or O)

        // Start each turn with row_counter at 0
        while (swap_counter != row * column) { // Main game loop
            int row_counter = 0; // Reset row_counter at the start of each player's turn
            int row_minus_one = row - 1; // used for zero-based indexing

            // Determine which player's turn it is
            if (swap_counter % 2 == 0) { // Player 1's turn
                token = Token_One;
                std::cout << playerOneName << "'s turn\n"; // Print Player 1's name
            } else { // Player 2's turn
                token = Token_Two;
                std::cout << playerTwoName << "'s turn\n"; // Print Player 2's name
            }

            // Prompt for column number until valid input is given
            std::cout << "Enter a column number: ";
            while (!(std::cin >> column_number) || column_number < 1 || column_number > column) {
                std::cout << "Invalid input. Please enter a valid column number between 1 and " << column << ": ";
                std::cin.clear();  // clear the error flag
                std::cin.ignore(10000, '\n');  // ignore invalid input
            }

            system("clear"); // Clears the terminal. "cls" for windows, "clear" for Mac and Linux;

            // Check if the column is full
            if (board[0][column_number - 1] == Token_One || board[0][column_number - 1] == Token_Two) {
                std::cout << "Column " << column_number << " is full. Please select a different column.\n";
                swap_counter--; // Do not count this turn
            } else {
                // Place the token in the correct row of the selected column
                while (board[row_counter][column_number - 1] != Token_One && board[row_counter][column_number - 1] != Token_Two) {
                    if (row_counter == row_minus_one) {
                        board[row_counter][column_number - 1] = token;
                        break;
                    } else {
                        if (board[row_counter + 1][column_number - 1] == Token_One || board[row_counter + 1][column_number - 1] == Token_Two) {
                            board[row_counter][column_number - 1] = token;
                            break;
                        }
                        row_counter++; // Move down the rows
                    }
                }
            }

            // Print the board after each move
            for (int i = 0; i < row; i++) {
                for (int j = 0; j < column; j++) {
                    std::cout << board[i][j]; // Print the board
                }
                std::cout << "\n"; 
                if (i == row - 1) {
                    int column_num = 1;
                    for (int k = 0; k < column; k++) {
                        std::cout << " " << column_num << " "; // Print column numbers at the bottom
                        column_num++;
                    }
                    std::cout << "\n";
                }
            }

            // Win check
            bool win = false;
            // Vertical win check
            if (row_counter <= row - 4 && board[row_counter][column_number - 1] == token &&
                board[row_counter + 1][column_number - 1] == token &&
                board[row_counter + 2][column_number - 1] == token &&
                board[row_counter + 3][column_number - 1] == token) {
                win = true;
            }

            // Horizontal win check
            for (int i = column_number - 4; i < column_number + 4; ++i) {
                if (i >= 0 && i + 3 < column && board[row_counter][i] == token &&
                    board[row_counter][i + 1] == token &&
                    board[row_counter][i + 2] == token &&
                    board[row_counter][i + 3] == token) {
                    win = true;
                }
            }

            // Diagonal win (top-left to bottom-right) check
            for (int i = 0; i < column - 3; ++i) {
                for (int j = 0; j < row - 3; ++j) {
                    if (board[j][i] == token && 
                        board[j + 1][i + 1] == token && 
                        board[j + 2][i + 2] == token && 
                        board[j + 3][i + 3] == token) {
                        win = true;
                    }
                }
            }

            // Diagonal win (bottom-left to top-right) check
            for (int i = 0; i < column - 3; ++i) {
                for (int j = 3; j < row; ++j) {
                    if (board[j][i] == token && 
                        board[j - 1][i + 1] == token && 
                        board[j - 2][i + 2] == token && 
                        board[j - 3][i + 3] == token) {
                        win = true;
                    }
                }
            }

            // Announce winner
            if (win) {
                if (token == Token_One) {
                    std::cout << playerOneName << " wins!\n"; // Player 1 wins
                } else {
                    std::cout << playerTwoName << " wins!\n"; // Player 2 wins
                }
                break; // Exit the loop if there's a winner
            }

            swap_counter++; // Increase the counter after each move
            std::cout << "There are " << (row * column) - swap_counter << " tokens left\n";
            
            if(swap_counter == row * column) {
                std::cout << "It's a tie!\n";
            }
        }

        // Ask for rematch or quit
        char rematch;
        while (true) {
            std::cout << "Do you want to rematch? (y/n): ";
            std::cin >> rematch;

            // Check if input is valid
            if (rematch == 'y' || rematch == 'Y') {
                break; // Exit the loop and rematch
            } else if (rematch == 'n' || rematch == 'N') {
                std::cout << "Thanks for playing!\n";
                return 0; // Exit the game
            } else {
                std::cout << "Invalid input. Please enter 'y' for a rematch or 'n' to quit.\n";
            }
        }
    }
    return 0;
}
