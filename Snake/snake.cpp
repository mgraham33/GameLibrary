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

#define MAX_X 80
#define MAX_Y 24

// stores the coordinate points
typedef struct coordinate_point {
  int x;
  int y;
} point;
// stores the current direction types
typedef enum {
	      LEFT,
	      RIGHT,
	      UP,
	      DOWN
} dir;

// stores the snake length
int length = 0;
// stores the score
int score = 0;
// stores the food location
point food;
// stores the current direction
dir curr = RIGHT;
// stores the snake
std::vector<point> snake;

void io_init_terminal(void) {
  initscr();
  raw();
  noecho();
  curs_set(0);
  keypad(stdscr, TRUE);
  start_color();
}

void printBoard() {
  int i;
  for (i = 0; i < (int) snake.size(); i++) {
    mvaddch(snake.at(i).y, snake.at(i).x, 'o');
  }
}

void randomFood() {
  // chooses a random position for the food
  food.x = rand() % MAX_X;
  food.y = rand() % MAX_Y;
  mvaddch(food.y, food.x, 'x');
}

void gameLoop() {
  // sets the snake's head
  point head;
  head.x = 0;
  head.y = MAX_Y / 2;
  snake.push_back(head);

  printBoard();
  int key;
  int loop = 1;
  randomFood();
  while (loop) {
    key = getch();
    // checks for change in direction
    if (key == KEY_LEFT) {
      curr = LEFT;
    } else if(key == KEY_RIGHT) {
      curr = RIGHT;
    } else if (key == KEY_UP) {
      curr = UP;
    } else if (key == KEY_DOWN) {
      curr = DOWN;
    } else if (key == 'Q') {
      // exits the game
      return;
    }

    // stores the snake's head
    int x = snake.at(0).x;
    int y = snake.at(0).y;

    // moves in the appropriate direction
    if (curr == LEFT) {
      x--;
    } else if (curr == RIGHT) {
      x++;
    } else if (curr == UP) {
      y--;
    } else if (curr == DOWN) {
      y++;
    }

    if (x == food.x && y == food.y) {
      // checks of you collect food and creates new food
      score++;
      point addToSnake;
      addToSnake.x = x;
      addToSnake.y = y;
      snake.push_back(addToSnake);
      randomFood();
    } else {
      int i;
      for (i = 0; i < (int) snake.size(); i++) {
	// checks if you hit your own tail and ends the game
	if (x == snake.at(i).x && y == snake.at(i).y) {
	  return;
	}
      }
    }

    // checks if you hit the wall
    if (x >= MAX_X || x < 0 || y >= MAX_Y || y < 0) {
      return;
    }

    printBoard();
  }
}

int main(int argc, char *argv[]) {
  srand(time(NULL));
  io_init_terminal();
  // starts the game
  gameLoop();
  endwin();
  return 0;
}
