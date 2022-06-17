// function explanation see utility.h

#include "utility.h"
#include "color.h"

#include <math.h>
#include <termios.h>
#include <unistd.h>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <thread>

using namespace std;

// with credits to https://stackoverflow.com/questions/4062045/clearing-terminal-in-linux-with-c-code
void clrscr()
{
    //using ANSI escape code
    cout << "\033[2J\033[1;1H";
    fflush(stdout);
}

// with credits to https://stackoverflow.com/questions/50884685/how-to-get-cursor-position-in-c-using-ansi-code
int getxy(int* y, int* x)
{
    char buf[30] = {0};
    int ret, i, pow;
    char ch;

    *y = 0;
    *x = 0;

    struct termios term, restore;

    tcgetattr(0, &term);
    tcgetattr(0, &restore);
    term.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(0, TCSANOW, &term);

    write(1, "\033[6n", 4);

    for (i = 0, ch = 0; ch != 'R'; i++) {
        ret = read(0, &ch, 1);
        if (!ret) {
            tcsetattr(0, TCSANOW, &restore);
            fprintf(stderr, "getpos: error reading response!\n");
            return 1;
        }
        buf[i] = ch;
        //printf("buf[%d]: \t%c \t%d\n", i, ch, ch);
    }

    if (i < 2) {
        tcsetattr(0, TCSANOW, &restore);
        printf("i < 2\n");
        return (1);
    }

    for (i -= 2, pow = 1; buf[i] != ';'; i--, pow *= 10)
        *x = *x + (buf[i] - '0') * pow;

    for (i--, pow = 1; buf[i] != '['; i--, pow *= 10)
        *y = *y + (buf[i] - '0') * pow;

    tcsetattr(0, TCSANOW, &restore);
    return 0;
}

// with credits to https://thoughtsordiscoveries.wordpress.com/2017/04/26/set-and-read-cursor-position-in-terminal-windows-and-linux/
void gotoxy(int XPos, int YPos)
{
    //using ANSI escape code
    printf("\033[%d;%dH", YPos + 1, XPos + 1);
    fflush(stdout);
}

// with credits to https://stackoverflow.com/questions/158585/how-do-you-add-a-timed-delay-to-a-c-program/9747668
// and https://stackoverflow.com/questions/2971254/c-sleep-and-loops
void delay(int millisecond)
{
    cout.flush();
    this_thread::sleep_until(chrono::system_clock::now() + chrono::milliseconds(millisecond));
}

//with credits to https://stackoverflow.com/questions/421860/capture-characters-from-standard-input-without-waiting-for-enter-to-be-pressed
char getch()
{
    char buf = 0;
    struct termios old = {0};
    if (tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if (read(0, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
    return (buf);
}

int getarrow()
{
    int a;
    int ch;
    a = getch();
    while (1) {
        if (a == 10) {  //note: Enter button would be 10 in getch()
            return a;
        }
        if (a
            == 27) {  //note: Top arrow would be 27 91 65, Bottom arrow would be 27 91 66 in getch()
            getch();
            ch = getch();
            if (ch == 65 || ch == 66) {
                return ch;
            }
        }
        a = getch();
    }
}

int select(char choice[][40], int previouschosen, int totalitems, int lines)
{
    int a, i = 0;
    int chosen = previouschosen;
    color.set("yellow");
    while (i < totalitems) {
        gotoxy(3, lines + i);
        printf("%s\n", choice[i]);
        i++;
    }
    color.set("red");

    gotoxy(0, lines);

    while (1) {
        while (a != 10) {
            gotoxy(1, lines + chosen);
            printf("->");
            fflush(stdout);
            gotoxy(0, 0);
            a = getarrow();

            gotoxy(1, lines + chosen);
            printf("  ");
            if (a == 66) {
                if (chosen < i - 1) {
                    chosen++;
                } else {
                    chosen = 0;
                    gotoxy(1, lines + i);
                    printf("  ");
                }
            }
            if (a == 65) {
                if (chosen > 0) {
                    chosen--;
                } else {
                    chosen = i - 1;
                    gotoxy(1, lines + i);
                    printf("  ");
                }
            }
        }
        color.set("green");
        gotoxy(0, lines + totalitems);

        return chosen;
    }

    return 0;
}

void printDelay(string a, int t, bool end)
{
    for (int i = 0; i < a.length(); i++) {
        if (a[i] != '*') {
            cout << a[i];
        } else {
            cout << endl;
        }
        delay(t);
    }
    if (end == true) {
        cout << endl;
    }
}

void printBar(string to_print)
{
    string final = "";
    int num_of_space = (80 - to_print.length()) / 2;
    for (int i = 0; i < num_of_space * 2; i++) {
        final += " ";
        if (final.length() == num_of_space) {
            final += to_print;
        }
    }
    color.set("yellow");
    printf("================================================================================\n");
    color.set("blue");
    printf("%s\n", final.c_str());
    color.set("yellow");
    printf("================================================================================\n");
    color.set("green");
}

int randomNumber(int low_limit, int up_limit)
{
    srand(time(NULL));
    return rand() % (up_limit - low_limit + 1) + low_limit;
}
