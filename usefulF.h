#ifndef USEFULF_H
#define USEFULF_H

// clear the screen
void clrscr();

// get current cursor position
int getxy(int *y, int *x);

// move cursor to specific position
void gotoxy(int XPos, int YPos);

// delay running codes
void delay(int millisecond);

// get character from user
char getch();

// get arrow inputs (upward and downward) from user
int getarrow();

// print a menu like selection which will be controlled using getarrow() and enter key.
// input: options provided, initial choice, total num of items, starting line to print
int select(char choice[][40],int previouschosen, int totalitems, int lines);

// printing strings with delay, to mimic speaking speak (user defined speed in miliseconds)
void printDelay(std::string a, int t, bool end);

// print title bar
void printBar(std::string to_print);

#endif
