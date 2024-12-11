How to Compile and run Connect 4

If on Windows:
	1. Find the folder that contains the connect 4 files in the terminal
	2. Copy, paste, and run this line: clang++ connect4_Windows -o Connect4
	3. Run this line: ./Connect4

If on Mac:

	1. Find the folder that contains the connect 4 files in the terminal
	2. Copy, paste, and run this line: clang++ -std=c++11 connect4_Mac:Linux.cpp -o Connect4
* this removes the warning on how c++11 uses for-range loops
	3. Run this line: ./Connect4

If on Ubuntu Linux:

	1. Find the folder that contains the connect 4 files in the terminal
	2. Copy, paste, and run this line: clang++ connect4_Mac:Linux.cpp -o Connect4
	3. Run this line: ./Connect4


notes: 
1. for player 1, we recommend the piece to be "X", and for player 2, we recommend the piece to be "O"
2. if a loop occurs due to accidental text, escape the program either by closing the terminal, or by using ctrl/control + c
