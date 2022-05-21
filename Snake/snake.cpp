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

// stores the score
int score = 0;
int highScore = 0;
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
  clear();
  mvaddch(food.y, food.x, 'x');
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

void moveSnake() {
  // moves the snake with the head
  point end = snake.at((int) snake.size() - 1);
  int i;
  for(i = (int) snake.size() - 1; i > 0; i--) {
    snake.at(i) = snake.at(i - 1);;
  }
  
  snake.at(0) = end;
}

void gameLoop() {
  // sets the snake's head
  point head;
  head.x = 0;
  head.y = MAX_Y / 2;
  snake.push_back(head);

  randomFood();
  printBoard();
  int key;
  int loop = 1;
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

    // moves in the appropriate direction
    if (curr == LEFT) {
      snake.at(0).x--;
    } else if (curr == RIGHT) {
      snake.at(0).x++;
    } else if (curr == UP) {
      snake.at(0).y--;
    } else if (curr == DOWN) {
      snake.at(0).y++;
    }

    if (snake.at(0).x == food.x && snake.at(0).y == food.y) {
      // checks of you collect
      score++;
      // adds length to the snake
      point addToSnake;
      addToSnake.x = snake.at(0).x;
      addToSnake.y = snake.at(0).y;
      snake.push_back(addToSnake);
      // creates new food
      randomFood();
    } else {
      int i;
      for (i = 1; i < (int) snake.size(); i++) {
	// checks if you hit your own tail and ends the game
	if (snake.at(0).x == snake.at(i).x && snake.at(0).y == snake.at(i).y) {
	  return;
	}
      }
      // resets the head
      snake.at((int) snake.size() - 1).x = snake.at(0).x;
      snake.at((int) snake.size() - 1).y = snake.at(0).y;
    }

    moveSnake();
    
    // checks if you hit the wall
    if (snake.at(0).x >= MAX_X || snake.at(0).x < 0 || snake.at(0).y >= MAX_Y
	|| snake.at(0).y < 0) {
      return;
    }

    printBoard();

    // checks if a new high score was reached
    if (score > highScore) {
      highScore = score;
    }
  }
}

void reset() {
  // resets the game
  score = 0;
  curr = RIGHT;
  snake.clear();
}

int main(int argc, char *argv[]) {
  srand(time(NULL));
  io_init_terminal();
  // starts the game
  gameLoop();
  clear();
  // prints the results
  std::string scorePrint = "Score: " + std::to_string(score);;
  char* scoreOut  = const_cast<char*>(scorePrint.c_str());
  std::string highScorePrint = "High Score: " + std::to_string(highScore);;
  char* highScoreOut  = const_cast<char*>(highScorePrint.c_str());
  mvprintw(1, MAX_X / 4, "Game Over");
  mvprintw(3, MAX_X / 4, scoreOut);
  mvprintw(5, MAX_X / 4, highScoreOut);
  mvprintw(7, MAX_X / 4, "Press any key to play again, 'Q' to quit");
  int key = getch();
  // checks for play again
  while (key != 'Q') {
    reset();
    clear();
    gameLoop();
    scorePrint = "Score: " + std::to_string(score);;
    scoreOut  = const_cast<char*>(scorePrint.c_str());
    highScorePrint = "High Score: " + std::to_string(highScore);;
    highScoreOut  = const_cast<char*>(highScorePrint.c_str());
    mvprintw(1, MAX_X / 4, "Game Over");
    mvprintw(3, MAX_X / 4, scoreOut);
    mvprintw(5, MAX_X / 4, highScoreOut);
    mvprintw(7, MAX_X / 4, "Press any key to play again, 'Q' to quit");
    key = getch();
  }
  endwin();
  return 0;
}
