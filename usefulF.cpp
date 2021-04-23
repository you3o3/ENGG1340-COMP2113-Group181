// function explanation see usefulF.h


#include <iostream>
#include <cstdio>
#include <math.h>
#include <unistd.h>
#include <termios.h>
#include <ctime>
#include <chrono>
#include <thread>
#include "usefulF.h"
#include "color.h"

using namespace std;

Color color_usefulF;

// with credits to https://stackoverflow.com/questions/4062045/clearing-terminal-in-linux-with-c-code
void clrscr(){
  //using ANSI escape code
  cout << "\033[2J\033[1;1H";
  fflush(stdout);
}

// with credits to https://thoughtsordiscoveries.wordpress.com/2017/04/26/set-and-read-cursor-position-in-terminal-windows-and-linux/
void gotoxy(int XPos, int YPos){
  //using ANSI escape code
  printf("\033[%d;%dH",YPos+1,XPos+1);
  fflush(stdout);
}

// with credits to https://stackoverflow.com/questions/158585/how-do-you-add-a-timed-delay-to-a-c-program/9747668
// and https://stackoverflow.com/questions/2971254/c-sleep-and-loops
void delay(int millisecond) {
  cout.flush();
  this_thread::sleep_until(chrono::system_clock::now() + chrono::milliseconds(millisecond));
}


//with credits to https://stackoverflow.com/questions/421860/capture-characters-from-standard-input-without-waiting-for-enter-to-be-pressed
char getch() {
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
		perror ("read()");
	old.c_lflag |= ICANON;
	old.c_lflag |= ECHO;
	if (tcsetattr(0, TCSADRAIN, &old) < 0)
		perror ("tcsetattr ~ICANON");
	return (buf);
}


int getarrow() {
	int a;
	int ch;
  a = getch();
  while (1){
    if (a == 10){			//note: Enter button would be 10 in getch()
      return a;
    }
    if(a == 27){			//note: Top arrow would be 27 91 65, Bottom arrow would be 27 91 66 in getch()
      getch();
      ch = getch();
      if (ch == 65 || ch == 66){
        return ch;
      }
    }
    a = getch();
  }

}

// with credit to https://stackoverflow.com/questions/8767166/passing-a-2d-array-to-a-c-function
int select(char choice[][20],int previouschosen, int totalitems, int lines) {
    int a,i=0;
    int chosen=previouschosen;
    color_usefulF.set("yellow");
    while(i < totalitems){
    	gotoxy(3,lines+i);
   	 	printf("%s\n",choice[i]);
    	i++;
    }
    color_usefulF.set("red");

    gotoxy(0,lines);

    while (1) {
        while (a!=10) {
            gotoxy(1,lines+chosen);
            printf("->");
            fflush(stdout);
            gotoxy(0,0);
            a=getarrow();

            gotoxy(1,lines+chosen);
            printf("  ");
            if (a==66){
                if (chosen<i-1){
                    chosen++;
                } else {
            				chosen = 0;
            				gotoxy(1,lines+i);
            				printf("  ");
    			      }
            }
            if (a==65){
                if (chosen>0){
                    chosen--;
                } else {
            				chosen = i-1;
            				gotoxy(1,lines+i);
            				printf("  ");
          			}
            }
        }
        color_usefulF.set("green");
        gotoxy(0,lines+totalitems);

        return chosen;
    }

    return 0;
}

void printDelay(string a, int t, bool end){
	for(int i = 0; i < a.length(); i++){
			if(a[i] != '*'){
				cout << a[i];
			} else {
				cout << endl;
			}
			delay(t);
	}
	if(end == true){
		cout << endl;
	}
}
