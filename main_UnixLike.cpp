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
#include <ctime>
#include <chrono>
#include <thread>
#include "color.h"
#include "creature.h"
#include "usefulF.h"

using namespace std;


//if file exist then return true, otherwise return false
inline bool save_exist (const string& save) {
  if (FILE *file = fopen(save.c_str(), "r")) {
    fclose(file);
    return true;
  } else {
    return false;
  }
}


void initialization(){

}


//basic character creation
character characterCreation(){
	string name;
	FILE *save = fopen("save.sav","rw");
  printBar("???");
	printDelay("In an abyss, a voice whispered: ", 40, false);
	printDelay("Welcome, novice.... I wonder what's your name...?", 60, true);
	cout << "> ";
	cin >> name;
	cout << name;
	printDelay("... a good name, indeed... So, you are a boy?", 40, true);
	char selections[2][20];
  strcpy(selections[0],"Yes");
  strcpy(selections[1],"No");
  int x = 0, y = 0;
	getxy(&y, &x);
	switch(select(selections,0,2,y-1)){
		case 0:{
			character player(name, true);
			printDelay("A boy will grow up and become a man... given enough challenges...", 60, true);
      delay(400);
			return player;
		}
		case 1:{
			character player(name, false);
			printDelay("A girl will grow up and become a heroine... given enough challenges...", 60, true);
      delay(400);
			return player;
		}
	}
  character none;
  return none;

}

//printing specific plots based on the section
void Introduction(int section){
	clrscr();
	if(section == 1){
		printBar("INTRODUCTION");
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
character loadSave(){
	character player;
	//TODO: load file and save status into player, note that player can't save other status like monsters, and save file during battle is prohibited
	return player;
}

//save file into user's computer
void saveFile(char fileName[]){

}

//menu of the game
void Menu(){
	//TODO: if save file exists ask if player want to load the files
	//if not, create character using characterCreation()
	character player;
	//Print UI Here
  clrscr();
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
	color.set("red");
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
			player = loadSave();
		} else {
      cout << "New game initializing... Initializing character creation sequence." << endl;
      delay(1000);
      clrscr();
      player = characterCreation();
      Introduction(1);
		}

	} else {
		cout << "New game initializing... Starting character creation sequence." << endl;
    delay(1000);
    clrscr();
    player = characterCreation();
    Introduction(1);
	}


}

int main () {
	Menu();
}
