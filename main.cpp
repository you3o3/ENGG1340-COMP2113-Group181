#include<bits/stdc++.h>
#include<cstdio>
#include<conio.h>
#include<math.h>
#include<dir.h>
#include<unistd.h>
#include<windows.h>
#include<dos.h>
#include<dir.h>
#include<ctime>
#include"creature.h"

using namespace std;

//if file exists then return true, otherwise return false
inline bool save_exist (const string& save) {
    if (FILE *file = fopen(save.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }   
}

//set color of text
void setcolor(int ForgC){
     WORD wColor;
      HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
      CONSOLE_SCREEN_BUFFER_INFO csbi;
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi)){
          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
     return;
}

//move cursor to specific location
void gotoxy(int column, int line){
  COORD coord;
  coord.X = column;
  coord.Y = line;
  SetConsoleCursorPosition(
    GetStdHandle( STD_OUTPUT_HANDLE ),
    coord
    );
}

//delay running codes
void delay(int milliseconds) {
	clock_t start_time = clock();
	while(clock() < start_time + milliseconds);
}

//initialization (tbc)
void initialization(){
	
}

//getting arrow inputs
char getarrow() {
	int a;
	int ch;
    while ((ch = _getch()) != 27){
    	if( ch == 13 ) return 13;
        if (ch == 0 || ch == 224) {
			a = _getch ();
			if( a == 72 || a == 80 ) {
				return a;
        	}
        }
    }
    ch = getch();
    return ch;
}

//print a menu like selection which will be controlled using getarrow() and enter key.
int select(char choice[][20],int previouschosen, int totalitems, int lines) {
    int a,i=0;
    int chosen=previouschosen;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
    setcolor(10);
    setcolor(14);
    while(i < totalitems){
    	gotoxy(3,lines+i);
   	 	printf("%s\n",choice[i]);
    	i++;
    }
    setcolor(12);
    gotoxy(0,lines);
    while (1) {
    while (a!=13) {
        gotoxy(1,lines+chosen);
        printf("->");
        gotoxy(0,0);
        a=getarrow();
        gotoxy(1,lines+chosen);
        printf("  ");
        if (a==80){
            if (chosen<i-1){
                chosen++;
            } else {
				chosen = 0;
				gotoxy(1,lines+i);
				printf("  ");
			}
        }
        if (a==72){
            if (chosen>0){
                chosen--;
            } else {
				chosen = i-1;
				gotoxy(1,lines+i);
				printf("  ");
			}
        }
    }
    setcolor(10);
    gotoxy(0,lines+totalitems);
    return chosen;
    }
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
	switch(select(selections,0,2,3)){
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

//to load the save file (tbi)
void loadSave(){
}

//to save the file (tbi)
void saveFile(char fileName[]){
}

//printing specific plots based on the section
void Introduction(int section){
	system("CLS");
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

//menu of the game
void Menu(){
	//TODO: if save file exists ask if player want to load the files
	//if not, create character using characterCreation()
	
	//Print UI Here
	system("CLS");
	int i;
	setcolor(14);
	printf("================================================================================\n");
	setcolor(9);
	printf("              MONSTER SLAYER    -    An Endless Fight and Survive RPG           \n");
	setcolor(14);
	printf("                                                                                \n");
	setcolor(10);
	printf("|                                   |   \n");
	setcolor(14);
	printf("Loading: \n");
	printf("================================================================================\n");
	setcolor(12);
	for(i = 1; i <= 100; i++){
        gotoxy(i/3,3);
        if(i%3==0) printf(">>>\n");
		gotoxy(23,4);
		printf("%d%%", i);
		delay(10);
	}	
	setcolor(10);
	delay(500);
	for(i = 0; i <= 4; i++){
		system("COLOR FA");
		delay(50);
		system("COLOR 0A");
		delay(50);
	}
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
			system("CLS");
			characterCreation();
			Introduction(1);
		}
		
	} else {
		cout << "New game initializing... Starting character creation sequence." << endl;
		characterCreation();
	}
	
	
}

int main () {
	Menu();
}
