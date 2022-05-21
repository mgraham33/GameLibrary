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

void io_init_terminal(void) {
  initscr();
  raw();
  noecho();
  curs_set(0);
  keypad(stdscr, TRUE);
  start_color();
}

void gameLoop() {
  
}

int main(int argc, char *argv[]) {
  io_init_terminal();
  // starts the game
  gameLoop();
  endwin();
  return 0;
}
