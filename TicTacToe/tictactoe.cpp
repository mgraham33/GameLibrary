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
// stores the current line
int line = 0;

void initBoard() {
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
  std::string line1 = " " + std::to_string(board[0][0]) + " | " + std::to_string(board[0][1])
    + " | " + std::to_string(board[0][2]) + " ";
  char* row1  = const_cast<char*>(line1.c_str());
  std::string line2 = " " + std::to_string(board[1][0]) + " | " + std::to_string(board[1][1])
    + " | " + std::to_string(board[1][2]) + " ";
  char* row2  = const_cast<char*>(line2.c_str());
  std::string line3 = " " + std::to_string(board[2][0]) + " | " + std::to_string(board[2][1])
    + " | " + std::to_string(board[2][2]) + " ";
  char* row3  = const_cast<char*>(line3.c_str());
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

void gameLoop() {
  mvprintw(line++, 0, "Welocme to Tic Tac Toe! Enter the location you would like to play at");
  printBoard();
  std::string turn;
  int i = 1;
  char symbol;
  if (i % 2 == 1) {
    turn = "X's Turn:";
    symbol = 'X';
  } else {
    turn = "O's Turn:";
    symbol = 'O';
  }
  char* prompt = const_cast<char*>(turn.c_str());
  mvprintw(line++, 0, prompt);
  int input = getch();
  int loop = 1;
  do {
    switch (input) {
    case 49:
      if (board[0][0] == '1') {
	board[0][0] = symbol;
	loop = 0;
      } else {
	mvprintw(line++, 0, "Error, that position is already taken. Try again:");
	input = getch();
      }
      break;
    case 50:
      if (board[0][1] == '2') {
	board[0][1] = symbol;
	loop = 0;
      } else {
	mvprintw(line++, 0, "Error, that position is already taken. Try again:");
	input = getch();
      }
      break;
    case 51:
      if (board[0][2] == '3') {
	 board[0][2] = symbol;
	 loop = 0;
      } else {
	mvprintw(line++, 0, "Error, that position is already taken. Try again:");
	input = getch();
      }
      break;
    case 52:
      if (board[1][0] == '4') {
	board[1][0] = symbol;
	loop = 0;
      } else {
	 mvprintw(line++, 0, "Error, that position is already taken. Try again:");
	 input = getch();
      }
      break;
    case 53:
      if (board[1][1] == '5') {
	board[1][1] = symbol;
	loop = 0;
      } else {
	 mvprintw(line++, 0, "Error, that position is already taken. Try again:");
	 input = getch();
      }
      break;
    case 54:
      if (board[1][2] == '6') {
	board[1][2] = symbol;
	loop = 0;
      } else {
	 mvprintw(line++, 0, "Error, that position is already taken. Try again:");
	 input = getch();
      }
      break;
    case 55:
      if (board[2][0] == '7') {
	board[2][0] = symbol;
	loop = 0;
      } else {
	 mvprintw(line++, 0, "Error, that position is already taken. Try again:");
	 input = getch();
      }
      break;
    case 56:
      if (board[2][1] == '8') {
	board[2][1] = symbol;
	loop = 0;
      } else {
	 mvprintw(line++, 0, "Error, that position is already taken. Try again:");
	 input = getch();
      }
      break;
    case 57:
      if (board[2][2] == '9') {
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
}

int main(int argc, char *argv[]) {
  io_init_terminal();
  initBoard();
  // starts the game
  gameLoop();
  getch();
  endwin();
  return 0;
}
