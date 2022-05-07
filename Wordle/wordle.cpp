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

// stroes the potential words
std::vector<std::string> wordList;

int countLines(std::string s) {
  // counts the number of lines in the file
  int numLines = 0;
  std::fstream in (s);
  std::string param;
  while (std::getline(in, param)) {
    numLines++;
  }
  in.close();
  return numLines;
}

void readFile() {
  // reads in the words in the file separated by a newline
  std::string s("words.txt");
  std::fstream input (s);
  int numLines = countLines(s);
  int line = 0;
  while(line < numLines) {
    std::string word;
    getline(input, word);
    wordList.push_back(word);
    line++;
  }
  input.close();
}

// initializes the terminal for ncurses
void io_init_terminal(void) {
  initscr();
  raw();
  noecho();
  curs_set(0);
  keypad(stdscr, TRUE);
  start_color();
  init_pair(COLOR_RED, COLOR_RED, COLOR_BLACK);
  init_pair(COLOR_GREEN, COLOR_GREEN, COLOR_BLACK);
  init_pair(COLOR_YELLOW, COLOR_YELLOW, COLOR_BLACK);
  init_pair(COLOR_BLUE, COLOR_BLUE, COLOR_BLACK);
  init_pair(COLOR_MAGENTA, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(COLOR_CYAN, COLOR_CYAN, COLOR_BLACK);
  init_pair(COLOR_WHITE, COLOR_WHITE, COLOR_BLACK);
}

void gameLoop() {
  int exit = 1;
  int guesses = 0;
  int score = 0;
  int line = 3;
  // chooses a random word
  std::string s("words.txt");
  int random = rand() % countLines(s) + 1;
  std::string currentWord = wordList.at(random);
  while (exit || guesses < 5) {
    // prompts the user
    mvprintw(0, 0, "Welcome to Wordle! Enter a word to start playing");
    std::string points = "Score: " + std::to_string(score);
    char* scoreCount = const_cast<char*>(points.c_str());
    mvprintw(1, 0, scoreCount);
    
    char* cheat = const_cast<char*>(currentWord.c_str());
    mvprintw(2, 0, cheat);

    // prints the attempt number
    std::string attempt = "Guess " + std::to_string(guesses + 1) + ":";
    char* attemptCount = const_cast<char*>(attempt.c_str());
    mvprintw(line++, 0, attemptCount);
    // gets the user's guess
    std::string guess;
    int letter = getch();
    int i = 0;
    while (guess.length() < currentWord.length() - 1) {
      if (letter >= 97 && letter <= 122) {
	guess.push_back(letter);
	mvaddch(line, i, guess.at(i));
	i++;
      } else {
	// alerts the user of invalid input
	attron(COLOR_PAIR(COLOR_RED));
	line++;
	mvprintw(line++, 0, "Error, please only enter lower case letters");
	attroff(COLOR_PAIR(COLOR_RED));
      }
      // checks for final letter entered
      if (guess.length() < currentWord.length() - 1) {
	letter = getch();
      }
    }
    // checks if a valid word was entered
    int found = 0;
    for (i = 0; i < (int) wordList.size(); i++) {
      // gets the formatted word
      int j;
      std::string temp;
      std::string current = wordList.at(i);
      for (j = 0; j < (int) current.length() - 1; j++) {
	temp += current.at(j);
      }
      if (temp == guess) {
	found = 1;
      }  
    }
    // checks if the word was found
    if (found == 0) {
      line++;
      mvprintw(line++, 0, "Error, please enter a valid word");
      guess = "";
      continue;
    }
    // increments the guesses
    guesses++;
    int correct = 0;
    // checks which letters were correct or ine wrong place
    for (i = 0; i < (int) guess.length(); i++) {
      if (guess.at(i) == currentWord.at(i)) {
	attron(COLOR_PAIR(COLOR_GREEN));
	mvaddch(line, i, guess.at(i));
	attroff(COLOR_PAIR(COLOR_GREEN));
	correct++;
      } else if (currentWord.std::string::find(guess.at(i)) != std::string::npos) {
	attron(COLOR_PAIR(COLOR_YELLOW));
	mvaddch(line, i, guess.at(i));
	attroff(COLOR_PAIR(COLOR_YELLOW));
      } else {
	mvaddch(line, i, guess.at(i));
      }
    }
    line++;
    if (correct == 5) {
      score++;
      attron(COLOR_PAIR(COLOR_GREEN));
      mvprintw(line++, 0, "Correct!");
      attroff(COLOR_PAIR(COLOR_GREEN));
      line++;
      mvprintw(line++, 0, "Press any key to play again or 'Q' to quit");
      int key = getch();
      if (key == 'Q') {
	exit = 0;
	break;
      } else {
	random = rand() % countLines(s) + 1;
	currentWord = wordList.at(random);
	guesses = 0;
	line = 3;
	clear();
      }
    } else if (guesses >= 6) {
      std::string fail = "You ran out of guesses, the word was " + currentWord;
      char* failureMessage = const_cast<char*>(fail.c_str());
      attron(COLOR_PAIR(COLOR_RED));
      mvprintw(line++, 0, failureMessage);
      attroff(COLOR_PAIR(COLOR_RED));
      line++;
      mvprintw(line++, 0, "Press any key to play again or 'Q' to quit");
      int key = getch();
      if (key == 'Q') {
        exit = 0;
	break;
      } else {
	random = rand() % countLines(s) + 1;
	currentWord = wordList.at(random);
	guesses = 0;
	line = 3;
	clear();
      }
    }
  }
}

int main(int argc, char *argv[]) {
  io_init_terminal();
  srand(time(NULL));
  readFile();
  gameLoop();
  endwin();
  return 0;
}
