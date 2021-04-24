// this program is for Unix-like systems
// for Windows system, please refer to "main.cpp"

// with credits to https://stackoverflow.com/questions/1670891/how-can-i-print-a-string-to-the-console-at-specific-coordinates-in-c
// Normally stdout is "buffered" which means the C runtime library queues up what you print and only sends it to the console when
// (a) you output a newline, (b) the queue fills up, or (c) you manually flush the file.

// for ANSI escape codes, adding fflush(stdout) before or/and after (manually flush) would prevent problems



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
	char selections[2][40] = {"Yes", "No"};
  int x = 0, y = 0;
	getxy(&y, &x);
	switch(select(selections,0,2,y-1)){
		case 0:{
			character p(name, true);
			printDelay("A boy will grow up and become a man... given enough challenges...", 60, true);
      delay(400);
      return p;
		}
		case 1:{
			character p(name, false);
			printDelay("A girl will grow up and become a heroine... given enough challenges...", 60, true);
      delay(400);
      return p;
		}
	}
  character none;
  return none;

}

//printing specific plots based on the section
void Introduction(int section){
	if(section == 1){
    clrscr();
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


void initialization(){

}


//load file from user and recover state based on the info in file
character loadSave(){
  character p;
	//TODO: load file and save status into player, note that player can't save other status like monsters, and save file during battle is prohibited
	return p;
}

//save file into user's computer
void saveFile(char fileName[]){

}

//guide request and provide guide if user want
void Guide(){
  /*
  clrscr();
  printDelay("Do you want to have a guide?", 40, true);
  char selections[2][40] = {"Yes", "No"};
  int x = 0, y = 0;
  getxy(&y, &x);
  switch(select(selections,0,2,y-1)){
    case 0:{
      //TODO: add guide***
      return;
    }
    case 1:{
      printDelay("Starting game...", 40, true);
      return;
    }
  }
  */
}

//------------------------------------------------------------------------------------------------------
// the following should be made inside a file called battle.cpp and battle.h
/* not implemented
void Battle(){

}
*/

//------------------------------------------------------------------------------------------------------
// the following should be made inside a file called region.cpp and region.h

void Adventure_option(){
  clrscr();

  printDelay("The Wall blocks ignorant adventurers from entering dangerous places.", 40, true);
  printDelay("So, " + player.name + ", where do you want to go?", 40, true);
  color.set("yellow");
  printf("================================================================================\n");
  color.set("green");
  printDelay("List of places: ", 40, true);
  char selections[7][40] = {
    "Adventurers' valley (lv1+)",
    "Slient forest (lv11+)",
    "Cemetery of the dark (lv21+)",
    "Forsaken castle (lv31+)",
    "Other side of the world (lv41+)",
    "Nest of dragons (lv51+)",
    "Abyss (requirement?\?\?)"
  };

  int x = 0, y = 0, lvlimit = (player.level - 1) / 10;
  getxy(&y, &x);
  int pos = select(selections,0,7,y-1);
  while (lvlimit < pos){
    color.set("red");
    printDelay("The Wall blocked your way...", 40, true);
    printDelay("Please choose a place that is suitable for your current level.", 40, true);
    delay(1000);
    clrscr();
    color.set("yellow");
    printf("================================================================================\n");
    color.set("green");
    printDelay("List of places: ", 40, true);
    getxy(&y, &x);
    pos = select(selections,0,7,y-1);
  }
  player.position = selections[pos];
  printDelay("You're walking to the " + player.position + ".", 40, true);
  delay(1000);
}

int OptionsInRegion(){
  clrscr();
  printBar(player.position);
  printDelay("You are inside the " + player.position + ".", 40, true);
  printDelay(player.name + ", What do you want to do?", 40, true);
  char selections[6][40] = {
    "Move on",
    "Take a rest (heal)",
    "Return to city",
    "Check my status",
    "Save game",
    "Exit game"
  };
  int x = 0, y = 0, to_return = 0;
  getxy(&y, &x);
  to_return = select(selections,0,6,y-1);
  // converting to_return to options in Region()
  if (to_return == 0){
    return 3;
  }
  if (to_return == 1){
    return 2;
  }
  return to_return + 2;
}

int OptionsInCity(){
  clrscr();
  printBar("City of Quart");
  printDelay("You are inside the " + player.position + ".", 40, true);
  printDelay(player.name + ", What do you want to do?", 40, true);
  char selections[5][40] = {
    "Take an adventure",
    "Take a rest (heal)",
    "Check my status",
    "Save game",
    "Exit game"
  };
  int x = 0, y = 0, to_return = 0;
  getxy(&y, &x);
  to_return = select(selections,0,5,y-1);
  // converting to_return to options in Region()
  if (to_return <= 1){
    return to_return + 1;
  } else {
    return to_return + 3;
  }
}

void Region(){
  /*note: what options represent
  0: NULL
  1: Take an adventure (in city)
  2: Take a rest (heal)
  3: Move on (during an adventure)
  4: Return to city (during an adventure)
  5: Check my status
  6: Save game
  7: Exit game

  can add any new options

  */
  int options = 0;
  while (options != 7){
    if (player.position == "City of Quart"){
      options = OptionsInCity();
    } else {
      options = OptionsInRegion();
    }

    switch(options){
      //1: Take an adventure (in city)
      case 1:{
        Adventure_option();
        break;
      }

      //2: Take a rest (heal)
      case 2:{
        printDelay("Recovering hp and mp...", 60, true);
        //recover hp mp (how much?), if in city then just heal, if in other places have chance to encounter monster
        break;
      }

      //3: Move on (during an adventure)
      case 3:{
        //Battle();
        //After_battle();
        break;
      }

      //4: Return to city (during an adventure)
      case 4:{
        player.position = "City of Quart";
        printDelay("Returning to City of Quart...", 60, true);
        delay(1000);
        break;
      }

      //5: Check my status
      case 5:{
        //print current status
        break;
      }

      //6: Save game
      case 6:{
        //saveFile(?)
        break;
      }

      //7: Exit game
      case 7:{
        printDelay("Thank you for playing this game!", 40, true);
        break;
      }

    }
  }
}
//------------------------------------------------------------------------------------------------------


//menu of the game
void Menu(){
	//TODO: if save file exists ask if player want to load the files
	//if not, create character using characterCreation()

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
  Guide();
  Region();



}

int main () {
	Menu();
}
