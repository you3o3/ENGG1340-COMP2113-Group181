#ifndef USEFULF_H
#define USEFULF_H

// input: none
// output: none
// clear the screen
void clrscr();

// input: 2 variables to store the x y position of the cursor
// output: none, but the variables are stored with the x y position of the cursor
// get current cursor position
int getxy(int *y, int *x);

// input: 2 variables indicating the x y position of the cursor that we want to move to
// output: none
// move cursor to specific position
void gotoxy(int XPos, int YPos);

// input: a variable serve as the time in millisecond wanted, to delay the codes
// output: none
// delay running codes
void delay(int millisecond);

// input: keyboard presses from user
// output: the respective value for the key the user presses
// get character from user
char getch();

// input: keyboard presses from user, if user not pressing (top/bottom) arrow buttons then the user would need to press again, press enter to return the value
// output: the respective value for the (top/bottom) arrow button the user presses
// get arrow inputs (upward and downward) from user
int getarrow();

// input: options provided, initial choice, total num of items, starting line to print
// output: a selection menu that ask for user (top/bottom) arrow button input and 
// print a menu like selection which will be controlled using getarrow() and enter key.
int select(char choice[][40],int previouschosen, int totalitems, int lines);

// input: the string to delay, and the time in millisecond to delay and whether to add a endl at last
// output: printing strings with delay
// printing strings with delay, to mimic speaking speak (user defined speed in miliseconds)
void printDelay(std::string a, int t, bool end);

// input: the string to print with title
// output: print the title bar with the string
// print title bar
void printBar(std::string to_print);

// input: the lower limit and the upper limit of random number
// output: a random number ranging from low_limit to up_limit (including the number of both limits)
//return a random number ranging from low_limit to up_limit (including the number of both limits)
int randomNumber(int low_limit, int up_limit);

#endif
