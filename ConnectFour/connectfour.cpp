#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <sys/time.h>
#include <assert.h>
#include <unistd.h>
#include <ncurses.h>
#include <ctype.h>

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <algorithm>

// stores the current terminal line
int line = 0;

// stores the board
class ConnectFour {
public:
  // stores the board rows
  std::string rows[6] = {"| | | | | | | |", "| | | | | | | |", "| | | | | | | |",
			 "| | | | | | | |", "| | | | | | | |", "| | | | | | | |"};
  
  int addPiece(int col, char symbol) {
    // converts the column to sthe index of the string
    switch (col) {
    case 2:
      col = 3;
      break;
    case 3:
      col = 5;
      break;
    case 4:
      col = 7;
      break;
    case 5:
      col = 9;
      break;
    case 6:
      col = 11;
      break;
    case 7:
      col = 13;
      break;
    }
    // checks which row to insert into
    if (rows[5][col] == ' ') {
      rows[5][col] = symbol;
    } else if (rows[4][col] == ' ') {
      rows[4][col] = symbol;
    } else if (rows[3][col] == ' ') {
      rows[3][col] = symbol;
    } else if (rows[2][col] == ' ') {
      rows[2][col] = symbol;
    } else if (rows[1][col] == ' ') {
      rows[1][col] = symbol;
    } else if (rows[0][col] == ' ') {
      rows[0][col] = symbol;
    } else {
      // alerts the user of failure
      mvprintw(line++, 0, "Error, the selected column was full. Try again");
      return 0;
    }
    // returns 1 on success
    return 1;
  }
  
  void printBoard() {
    // prints the header
    mvprintw(line++, 0, "Welcome to connect four! Choose a column to place your piece");
    mvprintw(line++, 0, "Press 'Q' at any point to exit");
    line++;
    mvprintw(line++, 0, " 1 2 3 4 5 6 7");  
    // prints the board
    int i;
    int row = 0;
    for (i = 1; i < 13; i++) {
      if (i % 2 == 1) {
	// prints the rows
	int j;
	int y = line;
	for (j = 0; j < 15; j++) {
	  // prints pieces according to their color
	  if (rows[row].at(j) == 'O') {
	    attron(COLOR_PAIR(COLOR_RED));
	    mvaddch(y, j, rows[row][j]);
	    attroff(COLOR_PAIR(COLOR_RED));
	  } else if (rows[row].at(j) == '0') {
	    attron(COLOR_PAIR(COLOR_YELLOW));
	    mvaddch(y, j, rows[row][j]);
	    attroff(COLOR_PAIR(COLOR_YELLOW));
	  } else {
	    mvaddch(y, j, rows[row][j]);
	  }
	}
	y++;
	line++;
	row++;
      } else {
	// prints the border
        mvprintw(line++, 0, "+-+-+-+-+-+-+-+");
      }
    }
    line++;
  }

  int checkWin() {
    // returns 1 for red, 0 for yellow, 2 for tie, -1 for game unfinished
    int empty = 0;
    int i;
    for (i = 0; i < 6; i++) {
      int j;
      for (j = 0; j < 15; j++) {
	// checks if the board still has empty spaces
	if (rows[i][j] == ' ') {
	  empty++;
	}
      }
    }
    if (empty == 0) {
      // game is a tie
      return 2;
    }
    int color = -1;
    int row;
    // checks if either player wins based on the rows
    for (row = 0; row < 6; row++) {
      if (rows[row][1] != ' ' && rows[row][1] == rows[row][3] && rows[row][1] == rows[row][5]
	  && rows[row][1] == rows[row][7]) {
	if (rows[row][1] == '0') {
	  color = 0;
	} else {
	  color = 1;
	}
      } else if (rows[row][3] != ' ' && rows[row][3] == rows[row][5]
		 && rows[row][3] == rows[row][7] && rows[row][3] == rows[row][9]) {
	if (rows[row][3] == '0') {
	  color = 0;
	} else {
	  color = 1;
	}
      } else if (rows[row][5] != ' ' && rows[row][5] == rows[row][7]
		 && rows[row][5] == rows[row][9] && rows[row][5] == rows[row][11]) {
	if (rows[row][5] == '0') {
	  color = 0;
	} else {
	  color = 1;
	}
      } else if (rows[row][7] != ' ' && rows[row][7] == rows[row][9]
		 && rows[row][7] == rows[row][11] && rows[row][7] == rows[row][13]) {
	if (rows[row][7] == '0') {
	  color = 0;
	} else {
	  color = 1;
	}
      }
    }
    // checks if either player wins based on the columns
    int col;
    for (col = 1; col < 15; col += 2) {
      if (rows[0][col] != ' ' && rows[0][col] == rows[1][col] && rows[0][col] == rows[2][col]
	  && rows[0][col] == rows[3][col]) {
	if (rows[0][col] == '0') {
	  color = 0;
	} else {
	  color = 1;
	}
      } else if (rows[1][col] != ' ' && rows[1][col] == rows[2][col]
		 && rows[1][col] == rows[3][col] && rows[1][col] == rows[4][col]) {
	if (rows[0][col] == '0') {
	  color = 0;
	} else {
	  color = 1;
	}
      } else if (rows[2][col] != ' ' && rows[2][col] == rows[3][col]
		 && rows[2][col] == rows[4][col] && rows[2][col] == rows[5][col]) {
	if (rows[0][col] == '0') {
	  color = 0;
	} else {
	  color = 1;
	}
      }
    }
    // checks if either player wins on a diagonal
    if (rows[2][5] != ' '
	&& ((rows[0][1] == rows[1][3] && rows[0][1] == rows[2][5] && rows[0][1] == rows[3][7])
	|| (rows[1][3] == rows[2][5] && rows[1][3] == rows[3][7] && rows[1][3] == rows[4][9])
	|| (rows[2][5] == rows[5][7] && rows[2][5] == rows[4][9] && rows[2][5] == rows[5][11]))) {
      if (rows[2][5] == '0') {
	color = 0;
      } else {
	color = 1;
      }
    } else if (rows[2][3] != ' '
	       && ((rows[1][1] == rows[2][3] && rows[1][1] == rows[3][5]
		    && rows[1][1] == rows[4][7]) || (rows[2][3] == rows[3][5]
						     && rows[2][3] == rows[4][7]
						     && rows[2][3] == rows[5][9]))) {
      if (rows[2][3] == '0') {
	color = 0;
      } else {
	color = 1;
      }
    } else if (rows[2][1] != ' ' && rows[2][1] == rows[3][3] && rows[2][1] == rows[4][5]
		    && rows[2][1] == rows[5][7]) {
      if (rows[2][1] == '0') {
	color = 0;
      } else {
	color = 1;
      }
    } else if (rows[2][7] != ' '
	       && ((rows[0][3] == rows[1][5] && rows[0][3] == rows[2][7]
		    && rows[0][3] == rows[3][9]) || (rows[1][5] == rows[2][7]
						     && rows[1][5] == rows[3][9]
						     && rows[1][5] == rows[4][11])
		   || (rows[2][7] == rows[3][9] && rows[2][7] == rows[4][11]
		       && rows[2][7] == rows[5][13]))) {
      if (rows[2][7] == '0') {
	color = 0;
      } else {
	color = 1;
      }
    } else if (rows[1][7] != ' '
	       && ((rows[0][5] == rows[1][7] && rows[0][5] == rows[2][9]
		    && rows[0][5] == rows[3][11]) || (rows[1][7] == rows[2][9]
						      && rows[1][7] == rows[3][11]
						      && rows[2][9] == rows[4][13]))) {
      if (rows[1][7] == '0') {
	color = 0;
      } else {
	color = 1;
      }
    } else if (rows[0][7] != ' ' && rows[0][7] == rows[1][9] && rows[0][7] == rows[2][11]
		    && rows[0][7] == rows[3][13]) {
      if (rows[0][7] == '0') {
	color = 0;
      } else {
	color = 1;
      }
    } else if (rows[3][1] != ' ' && rows[3][1] == rows[2][3] && rows[3][1] == rows[1][5]
		    && rows[3][1] == rows[0][7]) {
      if (rows[3][1] == '0') {
	color = 0;
      } else {
	color = 1;
      }
    } else if (rows[3][3] != ' '
	       && ((rows[4][1] == rows[3][3] && rows[4][1] == rows[2][5]
		    && rows[4][1] == rows[1][7]) || (rows[3][3] == rows[2][5]
						     && rows[3][3] == rows[1][7]
						     && rows[3][3] == rows[0][9]))) {
      if (rows[3][3] == '0') {
	color = 0;
      } else {
	color = 1;
      }
    } else if (rows[3][5] != ' '
	       && ((rows[5][1] == rows[4][3] && rows[5][1] == rows[3][5]
		    && rows[5][1] == rows[2][7]) || (rows[4][3] == rows[3][5]
						     && rows[4][3] == rows[2][7]
						     && rows[4][3] == rows[1][9])
		   || (rows[3][5] == rows[2][7] && rows[3][5] == rows[1][9]
		       && rows[3][5] == rows[0][11]))) {
      if (rows[3][5] == '0') {
	color = 0;
      } else {
	color = 1;
      }
    } else if (rows[3][7] != ' '
	       && ((rows[5][3] == rows[4][5] && rows[5][3] == rows[3][7]
		    && rows[5][3] == rows[2][9]) || (rows[4][5] == rows[3][7]
						     && rows[4][5] == rows[2][9]
						     && rows[4][5] == rows[1][11])
		   || (rows[3][7] == rows[2][9] && rows[2][7] == rows[1][11]
		       && rows[3][7] == rows[0][13]))) {
      if (rows[3][7] == '0') {
	color = 0;
      } else {
	color = 1;
      }
    } else if (rows[4][7] != ' '
	       && ((rows[5][5] == rows[4][7] && rows[5][5] == rows[3][9]
		    && rows[5][5] == rows[2][11]) || (rows[4][7] == rows[3][9]
						      && rows[4][7] == rows[2][11]
						      && rows[4][7] == rows[1][13]))) {
      if (rows[4][7] == '0') {
	color = 0;
      } else {
	color = 1;
      }
    } else if (rows[5][7] != ' ' && rows[5][7] == rows[4][9] && rows[5][7] == rows[3][11]
		    && rows[5][7] == rows[2][13]) {
      if (rows[5][7] == '0') {
	color = 0;
      } else {
	color = 1;
      }
    }
    // checks who won
    if (color == 1) {
      // red wins
      return 1;
    } else if (color == 0) {
      // yellow wins
      return 0;
    } else {
      // game continues
      return -1;
    }
  }

  void reset() {
    int i;
    for (i = 0; i < 6; i++) {
      int j;
      for (j = 0; j < 15; j++) {
	if (rows[i][j] == '0' || rows[i][j] == 'O') {
	  rows[i][j] = ' ';
	}
      }
    }
  }
};

// creates an instance of the board
ConnectFour gameBoard;

void io_init_terminal(void) {
  initscr();
  raw();
  noecho();
  curs_set(0);
  keypad(stdscr, TRUE);
  start_color();
  // creates the color pairs
  init_pair(COLOR_RED, COLOR_RED, COLOR_BLACK);
  init_pair(COLOR_YELLOW, COLOR_YELLOW, COLOR_BLACK);
}

void gameLoop() {
  int end = 1;
  int i = 1;
  while (end) {
    gameBoard.printBoard();
    std::string turn;
    char symbol;
    // checks who's turn it is
    if (i % 2 == 1) {
      turn = "Red's Turn:";
      symbol = 'O';
    } else {
      turn = "Yellow's Turn:";
      symbol = '0';
    }
    char* prompt = const_cast<char*>(turn.c_str());
    mvprintw(line++, 0, prompt);
    // gets user input
    int key = getch();
    int loop = 1;
    int valid = 0;
    do {
      // checks if the move is valid
      switch (key) {
      case 'Q':
	// ends the game
	end = 0;
	loop = 0;
	break;
      case '1':
	valid = gameBoard.addPiece(1, symbol);
	if (valid == 1) {
	  loop = 0;
	} else {
	  key = getch();
	}
	break;
      case '2':
	valid = gameBoard.addPiece(2, symbol);
	if (valid == 1) {
	  loop = 0;
	} else {
	  key = getch();
	}
	break;
      case '3':
	valid = gameBoard.addPiece(3, symbol);
	if (valid == 1) {
	  loop = 0;
	} else {
	  key = getch();
	}
	break;
      case '4':
	valid = gameBoard.addPiece(4, symbol);
	if (valid == 1) {
	  loop = 0;
	} else {
	  key = getch();
	}
	break;
      case '5':
	valid = gameBoard.addPiece(5, symbol);
	if (valid == 1) {
	  loop = 0;
	} else {
	  key = getch();
	}
	break;
      case '6':
	valid = gameBoard.addPiece(6, symbol);
	if (valid == 1) {
	  loop = 0;
	} else {
	  key = getch();
	}
	break;
      case '7':
	valid = gameBoard.addPiece(7, symbol);
	if (valid == 1) {
	  loop = 0;
	} else {
	  key = getch();
	}
	break;
      default:
	// prints error message
	mvprintw(line++, 0, "Error, please only enter numbers 1-7");
	key = getch();
      }
    } while (loop);
    clear();
    line = 0;
    gameBoard.printBoard();
    int win = gameBoard.checkWin();
    if (win == 1) {
      // red wins
      mvprintw(line++, 0, "Red wins! Press any key to play again or 'Q' to exit");
      int playAgain = getch();
      // prompts to play again
      if (playAgain == 'Q') {
	end = 0;
      } else {
	// resets the game
	gameBoard.reset();
	i = 1;
	line = 0;
	clear();
      }
    } else if (win == 0) {
      // yellow wins
      mvprintw(line++, 0, "Yellow wins! Press any key to play again or 'Q' to exit");
      int playAgain = getch();
      // prompts to play again
      if (playAgain == 'Q') {
	end = 0;
      } else {
	// resets the game
	gameBoard.reset();
	i = 1;
	line = 0;
	clear();
      }
    } else if (win == 2) {
      // tie occurs
      mvprintw(line++, 0, "It's a tie! Press any key to play again or 'Q' to exit");
      int playAgain = getch();
      // prompts to play again
      if (playAgain == 'Q') {
	end = 0;
      } else {
	// resets the game
	gameBoard.reset();
	i = 1;
	line = 0;
	clear();
      }
    } else {
      // game continues
      i++;
      clear();
      line = 0;
    }
  }
}

int main(int argc, char *argv[]) {
  io_init_terminal();
  // starts the game
  gameLoop();
  endwin();
  return 0;
}
