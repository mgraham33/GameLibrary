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
    /*char* r1 = const_cast<char*>(rows[0].c_str());
    mvprintw(line++, 0, r1);
    mvprintw(line++, 0, "+-+-+-+-+-+-+-+");
    char* r2 = const_cast<char*>(rows[1].c_str());
    mvprintw(line++, 0, r2);
    mvprintw(line++, 0, "+-+-+-+-+-+-+-+");
    char* r3 = const_cast<char*>(rows[2].c_str());
    mvprintw(line++, 0, r3);
    mvprintw(line++, 0, "+-+-+-+-+-+-+-+");
    char* r4 = const_cast<char*>(rows[3].c_str());
    mvprintw(line++, 0, r4);
    mvprintw(line++, 0, "+-+-+-+-+-+-+-+");
    char* r5 = const_cast<char*>(rows[4].c_str());
    mvprintw(line++, 0, r5);
    mvprintw(line++, 0, "+-+-+-+-+-+-+-+");
    char* r6 = const_cast<char*>(rows[5].c_str());
    mvprintw(line++, 0, r1);
    mvprintw(line++, 0, "+-+-+-+-+-+-+-+");
    */
    line++;
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
      symbol = '0';
    } else {
      turn = "Yellow's Turn:";
      symbol = 'O';
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
    i++;
    clear();
    line = 0;
  }
}

int main(int argc, char *argv[]) {
  io_init_terminal();
  // starts the game
  gameLoop();
  endwin();
  return 0;
}
