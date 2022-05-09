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

// stores the board
char board[3][3];
// stores the current line of the terminal
int line = 0;

void initBoard() {
  // fills the board with placeholder integers
  int number = 1;
  int i;
  for (i = 0; i < 3; i++) {
    int j;
    for (j = 0; j < 3; j++) {
      board[i][j] = number;
      number++;
    }
  }
}

void io_init_terminal(void) {
  initscr();
  raw();
  noecho();
  curs_set(0);
  keypad(stdscr, TRUE);
  start_color();
  // creates the color pairs
  init_pair(COLOR_RED, COLOR_RED, COLOR_BLACK);
  init_pair(COLOR_GREEN, COLOR_GREEN, COLOR_BLACK);
  init_pair(COLOR_YELLOW, COLOR_YELLOW, COLOR_BLACK);
  init_pair(COLOR_BLUE, COLOR_BLUE, COLOR_BLACK);
  init_pair(COLOR_MAGENTA, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(COLOR_CYAN, COLOR_CYAN, COLOR_BLACK);
  init_pair(COLOR_WHITE, COLOR_WHITE, COLOR_BLACK);
}

void printBoard() {
  line++;
  // formats the output
  std::string line1 = " " + std::to_string(board[0][0]) + " | " + std::to_string(board[0][1])
    + " | " + std::to_string(board[0][2]) + " ";
  int i;
  // replaces ASCII values with correct character
  for (i = 0; i < (int) line1.length() - 1; i++) {
    if (line1[i] == '8' && line1[i + 1] == '8') {
      line1[i] = 'X';
      line1.erase(i + 1, 1);
    } else if (line1[i] == '7' && line1[i + 1] == '9') {
      line1[i] = 'O';
      line1.erase(i + 1, 1);
    }
  }
  char* row1  = const_cast<char*>(line1.c_str());
  std::string line2 = " " + std::to_string(board[1][0]) + " | " + std::to_string(board[1][1])
    + " | " + std::to_string(board[1][2]) + " ";
  // replaces ASCII values with correct character
  for (i = 0; i < (int) line2.length() - 1; i++) {
    if (line2[i] == '8' && line2[i + 1] == '8') {
      line2[i] = 'X';
      line2.erase(i + 1, 1);
    } else if (line2[i] == '7' && line2[i + 1] == '9') {
      line2[i] = 'O';
      line2.erase(i + 1, 1);
    }
  }
  char* row2  = const_cast<char*>(line2.c_str());
  std::string line3 = " " + std::to_string(board[2][0]) + " | " + std::to_string(board[2][1])
    + " | " + std::to_string(board[2][2]) + " ";
  // replaces ASCII values with correct character
  for (i = 0; i < (int) line3.length() - 1; i++) {
    if (line3[i] == '8' && line3[i + 1] == '8') {
      line3[i] = 'X';
      line3.erase(i + 1, 1);
    } else if (line3[i] == '7' && line3[i + 1] == '9') {
      line3[i] = 'O';
      line3.erase(i + 1, 1);
    }
  }
  char* row3  = const_cast<char*>(line3.c_str());
  // prints the output
  mvprintw(line++, 0, "   |   |   ");
  mvprintw(line++, 0, row1);
  mvprintw(line++, 0, "   |   |   ");
  mvprintw(line++, 0, "---+---+--- ");
  mvprintw(line++, 0, "   |   |   ");
  mvprintw(line++, 0, row2);
  mvprintw(line++, 0, "   |   |   ");
  mvprintw(line++, 0, "---+---+---");
  mvprintw(line++, 0, "   |   |   ");
  mvprintw(line++, 0, row3);
  mvprintw(line++, 0, "   |   |   ");
  line++;
}

char checkWin() {
  if (board[0][0] == board[0][1] && board[0][0] == board[0][2]) {
    // checks first row
    return board[0][0];
  } else if (board[1][0] == board[1][1] && board[1][0] == board[1][2]) {
    // checks second row
    return board[1][0];
  } else if (board[2][0] == board[2][1] && board[2][0] == board[2][2]) {
    // checks third row
    return board[2][0];
  } else if (board[0][0] == board[1][0] && board[0][0] == board[2][0]) {
    // checks first column
    return board[0][0];
  } else if (board[0][1] == board[1][1] && board[0][1] == board[2][1]) {
    // chekcs second column
    return board[0][1];
  } else if (board[0][2] == board[1][2] && board[0][2] == board[2][2]) {
    // checks third column
    return board[0][2];
  } else if (board[0][0] == board[1][1] && board[0][0] == board[2][2]) {
    // checks top left to bottom right
    return board[0][0];
  } else if (board[0][2] == board[1][1] && board[0][2] == board[2][0]) {
    // checks top right to bottom left
    return board[0][2];
  } else if ((board[0][0] == 'X' || board[0][0] == 'O')
	     && (board[0][1] == 'X' || board[0][1] == 'O')
	     && (board[0][2] == 'X' || board[0][2] == 'O')
	     && (board[1][0] == 'X' || board[1][0] == 'O')
	     && (board[1][1] == 'X' || board[1][1] == 'O')
	     && (board[1][2] == 'X' || board[1][2] == 'O')
	     && (board[2][0] == 'X' || board[2][0] == 'O')
	     && (board[2][1] == 'X' || board[2][1] == 'O')
	     && (board[2][2] == 'X' || board[2][2] == 'O')) {
    // checks if catsgame
    return 'C';
  } else {
    // returns if game is stil in progress
    return 'P';
  }
}

void gameLoop() {
  int end = 1;
  int i = 1;
  while (end) {
    // prints header
    mvprintw(line++, 0, "Welocme to Tic Tac Toe! Enter the location you would like to play at");
    mvprintw(line++, 0, "Press 'Q' at any time to exit");
    printBoard();
    std::string turn;
    char symbol;
    // checks who's turn it is
    if (i % 2 == 1) {
      turn = "X's Turn:";
      symbol = 'X';
    } else {
      turn = "O's Turn:";
      symbol = 'O';
    }
    // prints the turn
    char* prompt = const_cast<char*>(turn.c_str());
    mvprintw(line++, 0, prompt);
    int input = getch();
    int loop = 1;
    // gets user input and assigns it if applicable
    do {
      switch (input) {
      case 'Q':
	end = 0;
	loop = 0;
	break;
      case 49:
	if (board[0][0] != 'X' && board[0][0] != 'O') {
	  board[0][0] = symbol;
	  loop = 0;
	} else {
	  mvprintw(line++, 0, "Error, that position is already taken. Try again:");
	  input = getch();
	}
	break;
      case 50:
	if (board[0][1] != 'X' && board[0][1] != 'O') {
	  board[0][1] = symbol;
	  loop = 0;
	} else {
	  mvprintw(line++, 0, "Error, that position is already taken. Try again:");
	  input = getch();
	}
	break;
      case 51:
	if (board[0][2] != 'X' && board[0][2] != 'O') {
	  board[0][2] = symbol;
	  loop = 0;
	} else {
	  mvprintw(line++, 0, "Error, that position is already taken. Try again:");
	  input = getch();
	}
	break;
      case 52:
	if (board[1][0] != 'X' && board[1][0] != 'O') {
	  board[1][0] = symbol;
	  loop = 0;
	} else {
	  mvprintw(line++, 0, "Error, that position is already taken. Try again:");
	  input = getch();
	}
	break;
      case 53:
	if (board[1][1] != 'X' && board[1][1] != 'O') {
	  board[1][1] = symbol;
	  loop = 0;
	} else {
	  mvprintw(line++, 0, "Error, that position is already taken. Try again:");
	  input = getch();
	}
	break;
      case 54:
	if (board[1][2] != 'X' && board[1][2] != 'O') {
	  board[1][2] = symbol;
	  loop = 0;
	} else {
	  mvprintw(line++, 0, "Error, that position is already taken. Try again:");
	  input = getch();
	}
	break;
      case 55:
	if (board[2][0] != 'X' && board[2][0] != 'O') {
	  board[2][0] = symbol;
	  loop = 0;
	} else {
	  mvprintw(line++, 0, "Error, that position is already taken. Try again:");
	  input = getch();
	}
	break;
      case 56:
	if (board[2][1] != 'X' && board[2][1] != 'O') {
	  board[2][1] = symbol;
	  loop = 0;
	} else {
	  mvprintw(line++, 0, "Error, that position is already taken. Try again:");
	  input = getch();
	}
	break;
      case 57:
	if (board[2][2] != 'X' && board[2][2] != 'O') {
	  board[2][2] = symbol;
	  loop = 0;
	} else {
	  mvprintw(line++, 0, "Error, that position is already taken. Try again:");
	  input = getch();
	}
	break;
      default:
	mvprintw(line++, 0, "Error, please only enter numbers 1-9. Try again:");
	input = getch();
      }
    } while (loop);
    // checks if the game is over
    char win = checkWin();
    if (win == 'C') {
      clear();
      line = 0;
      // prints the header
      mvprintw(line++, 0, "Welocme to Tic Tac Toe! Enter the location you would like to play at");
      mvprintw(line++, 0, "Press 'Q' at any time to exit");
      printBoard();
      // prints the result
      mvprintw(line++, 0, "Game over, it was a tie!");
      mvprintw(line++, 0, "Press any key to play again, 'Q' to quit");
      // prompts the user to play again
      int key = getch();
      if (key == 'Q') {
	end = 0;
      } else {
	initBoard();
      }
    } else if (win == 'P') {
      // moves on with the game
      i++;
    } else {
      clear();
      line = 0;
      // prints the header
      mvprintw(line++, 0, "Welocme to Tic Tac Toe! Enter the location you would like to play at");
      mvprintw(line++, 0, "Press 'Q' at any time to exit");
      printBoard();
      // prints the result
      std::string winStr = "Game over, " + std::to_string(win) + "'s win!";
      // replaces ASCII values with correct character
      for (i = 0; i < (int) winStr.length() - 1; i++) {
	if (winStr[i] == '8' && winStr[i + 1] == '8') {
	  winStr[i] = 'X';
	  winStr.erase(i + 1, 1);
	} else if (winStr[i] == '7' && winStr[i + 1] == '9') {
	  winStr[i] = 'O';
	  winStr.erase(i + 1, 1);
	}
      }
      char* winMessage = const_cast<char*>(winStr.c_str());
      mvprintw(line++, 0, winMessage);
      mvprintw(line++, 0, "Press any key to play again, 'Q' to quit");
      // prompts the user to play again
      int key = getch();
      if (key == 'Q') {
	end = 0;
      } else {
	initBoard();
      }
    }
    // resets the terminal
    clear();
    line = 0;
  }
}

int main(int argc, char *argv[]) {
  io_init_terminal();
  initBoard();
  // starts the game
  gameLoop();
  endwin();
  return 0;
}
