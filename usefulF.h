#ifndef USEFULF_H
#define USEFULF_H

// clear the screen
void clrscr();

// move cursor to specific position
void gotoxy(int XPos, int YPos);

// delay running codes
void delay(int millisecond);

// get character from user
char getch();

// get arrow inputs (upward and downward) from user
int getarrow();

// this only works when the dimensions are known in compile time
// print a menu like selection which will be controlled using getarrow() and enter key.
// input: options provided, initial choice, total num of items, starting line to print
int select(char choice[][20],int previouschosen, int totalitems, int lines);

// printing strings with delay, to mimic speaking speak (user defined speed in miliseconds)
void printDelay(std::string a, int t, bool end);

#endif
