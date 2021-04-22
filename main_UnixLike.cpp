// this program is for Unix-like systems
// for Windows system, please refer to "main.cpp"


// with credits to https://stackoverflow.com/questions/1670891/how-can-i-print-a-string-to-the-console-at-specific-coordinates-in-c
// Normally stdout is "buffered" which means the C runtime library queues up what you print and only sends it to the console when
// (a) you output a newline, (b) the queue fills up, or (c) you manually flush the file.

// for ANSI escape codes, adding fflush(stdout) before or/and after (manual flush) would prevent problems


#include <iostream>
#include <cstdio>
#include <math.h>
#include <unistd.h>
#include <termios.h>
#include <ctime>
#include <chrono>
#include <thread>
#include "color.h"
#include "creature.h"

using namespace std;

Color color;

//if file exist then return true, otherwise return false
inline bool save_exist (const string& save) {
  if (FILE *file = fopen(save.c_str(), "r")) {
    fclose(file);
    return true;
  } else {
    return false;
  }
}

// with credits to https://stackoverflow.com/questions/4062045/clearing-terminal-in-linux-with-c-code
// clear the screen
void clrscr(){
  //using ANSI escape code
  cout << "\033[2J\033[1;1H";
  fflush(stdout);
}

// with credits to https://thoughtsordiscoveries.wordpress.com/2017/04/26/set-and-read-cursor-position-in-terminal-windows-and-linux/
//move cursor to specific position
void gotoxy(int XPos, int YPos){
  //using ANSI escape code
  printf("\033[%d;%dH",YPos+1,XPos+1);
  fflush(stdout);
}

// with credits to https://stackoverflow.com/questions/158585/how-do-you-add-a-timed-delay-to-a-c-program/9747668
// and https://stackoverflow.com/questions/2971254/c-sleep-and-loops
//delay running codes
void delay(int millisecond) {
  cout.flush();
  this_thread::sleep_until(chrono::system_clock::now() + chrono::milliseconds(millisecond));
}


void initialization(){

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

//getting arrow inputs (upward and downward)
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

//print a menu like selection which will be controlled using getarrow() and enter key.
int select(char choice[][20],int previouschosen, int totalitems, int lines) {
	int a,i=0;
	int chosen=previouschosen;
	color.set("yellow");
	while(i < totalitems){
		gotoxy(3,lines+i);
	printf("%s\n",choice[i]);
		i++;
	}
	color.set("red");

	gotoxy(0,lines);

	while (1) {
		while (a!=10) {
			gotoxy(1,lines+chosen);
			printf("->");
			fflush(stdout);		//flush is needed or else arrow would disappear
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
		color.set("green");
		gotoxy(0,lines+totalitems);

		return chosen;
	}

	return 0;
}

//printing strings with delay, to mimic speaking speak (user defined speed in miliseconds)
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

//basic character creation
void characterCreation(){
	string name;
	FILE *save = fopen("save.sav","rw");
	printDelay("In an abyss, a voice whispered: ", 40, false);
	printDelay("Welcome, novice.... I wonder what's your name...?", 60, true);
	cout << "> ";
	cin >> name;
	cout << name;
	printDelay("... a good name, indeed... So, you are a boy?", 40, true);
	char selections[2][20]; strcpy(selections[0],"Yes"); strcpy(selections[1],"No");
	switch(select(selections,0,2,4)){
		case 0:{
			character(name, true);
			printDelay("A boy will grow up and become a man... given enough challenges...", 60, true);
			break;
		}
		case 1:{
			character(name, false);
			printDelay("A girl will grow up and become a heroine... given enough challenges...", 60, true);
			break;
		}
	}


}

//printing specific plots based on the section
void Introduction(int section){
	clrscr();
	if(section == 1){
		string Story = "Many places are surrounded by a transparent wall that prevent people who are not good enough from entering, *and block monsters who are too strong from harming people. *Legend says that The Wall is a magic casted by the Almighty Mage Kinn at the end of his life, *but no one knows how long would it lasts for. *The Wall prevents people from entering the dangerous area and block monsters, *but still, there are places that are not being protected. *Adventurers, the best of all, protect weak traders travelling around the globe and fight monsters to obtain loot. *Over the years, many become brave warriors, enduring hardships and dangers. *Some become loyal knights, guarding the weak and the poor. *Some become wise sorcerers, mastering magics and knowledge. *And now... in the City of Quart, a novice adventurer is creating history";
		printDelay(Story,40,false);
		for(int i = 0; i < 3; i++){
			cout << '.';
			delay(400);
		}
		cout << endl;
	}
}

//load file from user and recover state based on the info in file
void loadSave(){

}

//save file into user's computer
void saveFile(char fileName[]){

}

//menu of the game
void Menu(){
	//TODO: if save file exists ask if player want to load the files
	//if not, create character using characterCreation()

	//Print UI Here

	int i;
	color.set("yellow");
	printf("================================================================================\n");
	color.set("blue");
	printf("              MONSTER SLAYER    -    An Endless Fight and Survive RPG           \n");
	color.set("yellow");
	printf("                                                                                \n");
	color.set("green");
	printf("|                                   |   \n");
  color.set("yellow");
	printf("Loading: \n");
	printf("================================================================================\n");
	color.set("yellow");
	for(i = 1; i <= 100; i++){
    gotoxy(i/3,3);
    if(i%3==0) printf(">>>\n");
		gotoxy(23,4);
		printf("%d%%", i);
		delay(10);
	}
	color.set("green");
	delay(500);
  //removed the flash effect which is avaliable in windows version
  //because system("Color __") is Windows-specific
	gotoxy(0,6);

	if(save_exist("save.sav")){
		char a;
		cout << "File exists, do you want to load the save file? Y/N: ";
		a = getchar();
		if(a=='Y'){
			//load file
			loadSave();
		} else {
      cout << "New game initializing... Initializing character creation sequence." << endl;
      delay(1000);
      clrscr();
      characterCreation();
      Introduction(1);
		}

	} else {
		cout << "New game initializing... Starting character creation sequence." << endl;
    delay(1000);
    clrscr();
    characterCreation();
    Introduction(1);
	}


}

int main () {
	Menu();
}
