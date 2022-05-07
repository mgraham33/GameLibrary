#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
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

// stroes the potential words
std::vector<std::string> wordList;
int score = 0;

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
void io_init_terminal(void)
{
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

// prints the hangman based on the amount of guesses used
void printHangman(int numGuesses) {
  int i;
  // clears the terminal
  for (i = 0; i < 14; i++) {
     mvprintw(i, 0, "                                                     ");
  }
  switch(numGuesses) {
  case 0:
    mvprintw(0, 0, " ________");
    mvprintw(1, 0, " |      |");
    mvprintw(2, 0, " |      |");
    mvprintw(3, 0, " |");
    mvprintw(4, 0, " |");
    mvprintw(5, 0, " |");
    mvprintw(6, 0, " |");
    mvprintw(7, 0, " |");
    mvprintw(8, 0, " |");
    mvprintw(9, 0, " |");
    mvprintw(10, 0, " |");
    mvprintw(11, 0, " |");
    mvprintw(12, 0, " |");
    mvprintw(13, 0, "___");
    break;
  case 1:
     mvprintw(0, 0, " ________");
     mvprintw(1, 0, " |      |");
     mvprintw(2, 0, " |      |");
     mvprintw(3, 0, " |    /---\\");
     mvprintw(4, 0, " |    |   |");
     mvprintw(5, 0, " |    \\---/");
     mvprintw(6, 0, " |");
     mvprintw(7, 0, " |");
     mvprintw(8, 0, " |");
     mvprintw(9, 0, " |");
     mvprintw(10, 0, " |");
     mvprintw(11, 0, " |");
     mvprintw(12, 0, " |");
     mvprintw(13, 0, "___");
    break;
  case 2:
    mvprintw(0, 0, " ________");
    mvprintw(1, 0, " |      |");
    mvprintw(2, 0, " |      |");
    mvprintw(3, 0, " |    /---\\");
    mvprintw(4, 0, " |    |   |");
    mvprintw(5, 0, " |    \\---/");
    mvprintw(6, 0, " |      |");
    mvprintw(7, 0, " |      |");
    mvprintw(8, 0, " |      |");
    mvprintw(9, 0, " |      |");
    mvprintw(10, 0, " |");
    mvprintw(11, 0, " |");
    mvprintw(12, 0, " |");
    mvprintw(13, 0, "___");
    break;
  case 3:
    mvprintw(0, 0, " ________");
    mvprintw(1, 0, " |      |");
    mvprintw(2, 0, " |      |");
    mvprintw(3, 0, " |    /---\\");
    mvprintw(4, 0, " |    |   |");
    mvprintw(5, 0, " |    \\---/");
    mvprintw(6, 0, " |      |");
    mvprintw(7, 0, " |   ___|");
    mvprintw(8, 0, " |      |");
    mvprintw(9, 0, " |      |");
    mvprintw(10, 0, " |");
    mvprintw(11, 0, " |");
    mvprintw(12, 0, " |");
    mvprintw(13, 0, "___");
    break;
  case 4:
    mvprintw(0, 0, " ________");
    mvprintw(1, 0, " |      |");
    mvprintw(2, 0, " |      |");
    mvprintw(3, 0, " |    /---\\");
    mvprintw(4, 0, " |    |   |");
    mvprintw(5, 0, " |    \\---/");
    mvprintw(6, 0, " |      |");
    mvprintw(7, 0, " |   ___|___");
    mvprintw(8, 0, " |      |");
    mvprintw(9, 0, " |      |");
    mvprintw(10, 0, " |");
    mvprintw(11, 0, " |");
    mvprintw(12, 0, " |");
    mvprintw(13, 0, "___");
    break;
  case 5:
    mvprintw(0, 0, " ________");
    mvprintw(1, 0, " |      |");
    mvprintw(2, 0, " |      |");
    mvprintw(3, 0, " |    /---\\");
    mvprintw(4, 0, " |    |   |");
    mvprintw(5, 0, " |    \\---/");
    mvprintw(6, 0, " |      |");
    mvprintw(7, 0, " |   ___|___");
    mvprintw(8, 0, " |      |");
    mvprintw(9, 0, " |      |");
    mvprintw(10, 0, " |     /");
    mvprintw(11, 0, " |    /");
    mvprintw(12, 0, " |");
    mvprintw(13, 0, "___");
    break;
  case 6:
    mvprintw(0, 0, " ________");
    mvprintw(1, 0, " |      |");
    mvprintw(2, 0, " |      |");
    mvprintw(3, 0, " |    /---\\");
    mvprintw(4, 0, " |    |   |");
    mvprintw(5, 0, " |    \\---/");
    mvprintw(6, 0, " |      |");
    mvprintw(7, 0, " |   ___|___");
    mvprintw(8, 0, " |      |");
    mvprintw(9, 0, " |      |");
    mvprintw(10, 0, " |     / \\");
    mvprintw(11, 0, " |    /   \\");
    mvprintw(12, 0, " |");
    mvprintw(13, 0, "___");
    break;
  }
}

int gameLoop() {
  mvprintw(19, 0, "                                                     ");
  mvprintw(19, 0, "Press 'Q' to exit at any time");
  std::vector<char> lettersUsed;
  int numGuesses = 0;
  // chooses a random word from the list
  std::string s("words.txt");
  int random = rand() % countLines(s) + 1;
  std::string currentWord = wordList.at(random);
  std::string blank;
  std::string guess;
  int i = 0;
  // creates the blank spaces for the selected word
  for (i = 0; i < (int) currentWord.length(); i++) {
    blank += "_";
    guess += "_";
    if (i < (int) currentWord.length() - 1) {
      blank += " ";
    }
  }
  // converts the blank for ncurses
  char* curseBlank = const_cast<char*>(blank.c_str());
  mvprintw(15, 0, curseBlank);
  int correct = 0;
  // prints the letters used
  while ((int) lettersUsed.size() < 26 && numGuesses < 6 && correct == 0) {
    std::string used = "Letters used: ";
    for (i = 0; i < (int) lettersUsed.size(); i++) {
      used += lettersUsed.at(i);
      if (i < (int) lettersUsed.size() - 1) {
	used += " ";
      }
    }
    // converts the letters used for ncurses
    char* curseUsed = const_cast<char*>(used.c_str());
    mvprintw(20, 0, "                                                     ");
    attron(COLOR_PAIR(COLOR_RED));
    mvprintw(20, 0, curseUsed);
    attroff(COLOR_PAIR(COLOR_RED));
    // prints the score
    std::string scoreOut = "Score: " + std::to_string(score);
    char* curseScore = const_cast<char*>(scoreOut.c_str());
    mvprintw(21, 0, "                                                     ");
    attron(COLOR_PAIR(COLOR_CYAN));
    mvprintw(21, 0, curseScore);
    attroff(COLOR_PAIR(COLOR_CYAN));
    int key;
    int letter = '!';
    // gets user input for their guessed letter
    while (letter == '!') {
      key = getch();
      // exits the game
      if (key == 'Q') {
	 mvprintw(15, 0, "                                                     ");
	 mvprintw(18, 0, "                                                     ");
	 mvprintw(19, 0, "                                                     ");
	 mvprintw(17, 0, "                                                     ");
	 mvprintw(20, 0, "                                                     ");
	 mvprintw(21, 0, "                                                     ");
	 attron(COLOR_PAIR(COLOR_YELLOW));
	 mvprintw(17, 0, "Game exited by user, press 'Q' to close");
	 attroff(COLOR_PAIR(COLOR_YELLOW));
	 return -1;
      }
      // checks for valid key
      if (key >= 97 && key <= 122) {
	int used = 0;
	// checks if the letter has been used
	for (i = 0; i < (int) lettersUsed.size(); i++) {
	  if (lettersUsed.at(i) == key) {
	    used = 1;
	  }
	}
	mvprintw(17, 0, "                                                       ");
	// alerts the user they have selected a duplicate letter
	if (used == 1) {
	  mvprintw(17, 0, "                                                     ");
	  attron(COLOR_PAIR(COLOR_YELLOW));
	  mvprintw(17, 0, "You already guessed that letter, try again");
	  attroff(COLOR_PAIR(COLOR_YELLOW));
	} else {
	  letter = key;
	  lettersUsed.push_back(letter);
	  int wrong = 0;
	  // checks if the user uses a guess incorrectly
	  for (i = 0; i < (int) currentWord.length(); i++) {
	    if (currentWord[i] == letter) {
	      wrong = 1;
	    }
	  }
	  if (wrong == 0) {
	    numGuesses++;
	    printHangman(numGuesses);
	  }
	}
      } else {
	// alerts the user of invalid input
	mvprintw(17, 0, "                                                       ");
	attron(COLOR_PAIR(COLOR_YELLOW));
	mvprintw(17, 0, "Please only enter letters a-z lower case");
	attroff(COLOR_PAIR(COLOR_YELLOW));
      }
    }
    // checks where the user's guess is in the word
    for (i = 0; i < (int) lettersUsed.size(); i++) {
      int j;
      for (j = 0; j < (int) currentWord.length(); j++) {
	if (currentWord[j] == lettersUsed.at(i)) {
	  guess[j] = lettersUsed.at(i);
	}
      }
    }
    // updates the blank with the guessed letters
    std::string guessOut;
    for (i = 0; i < (int) guess.length(); i++) {
      guessOut += guess[i];
      if (i < (int) guess.length() - 1) {
	guessOut += " ";
      }
    }
    int numLeft = 0;
    for (i = 0; i < (int) guess.length(); i++) {
      if (guess[i] == '_') {
	numLeft++;
      }
    }
    // checks if the user guessed the word correctly
    if (numLeft == 0) {
      correct = 1;
      mvprintw(17, 0, "                                                     ");
      attron(COLOR_PAIR(COLOR_GREEN));
      mvprintw(17, 0, "You have guessed the word correctly");
      attroff(COLOR_PAIR(COLOR_GREEN));
      // incremets the score
      score++;
    }
    // converts the user's guesses for ncurses
    char* curseGuess = const_cast<char*>(guessOut.c_str());
    mvprintw(15, 0, "                                                     ");
    mvprintw(15, 0, curseGuess);
  }
  // checks if the user completed the hangman
  if (numGuesses >= 6) {
     mvprintw(17, 0, "                                                     ");
     attron(COLOR_PAIR(COLOR_YELLOW));
     mvprintw(17, 0, "You have reached the maximum number of guesses");
     attroff(COLOR_PAIR(COLOR_YELLOW));
  }    
  std::string answer = "The word was " + currentWord;
  // converts the answer for ncurses
  char* curseCurrent = const_cast<char*>(answer.c_str());
  mvprintw(18, 0, "                                                     ");
  mvprintw(18, 0, curseCurrent);
  mvprintw(19, 0, "                                                     ");
  mvprintw(19, 0, "Press any key to play again or 'Q' to exit");
  return 0;
}

int main(int argc, char *argv[]) {
  io_init_terminal();
  srand(time(NULL));
  readFile();
  int loop = 0;
  // loops until the user presses Q
  while (loop == 0) {
    mvprintw(15, 0, "                                                     ");
    mvprintw(17, 0, "                                                     ");
    mvprintw(18, 0, "                                                     ");
    mvprintw(19, 0, "                                                     ");
    printHangman(0);
    loop = gameLoop();
    getch();
  }
  // ends the ncurses terminal
  endwin();
  return 0;
}
