// this program is for Unix-like systems
// for Windows system, please refer to "main.cpp"

#include <iostream>
#include <cstdio>
#include <math.h>
#include <unistd.h>
#include <ctime>
#include <chrono>
#include <thread>
#include "color.h"
#include "creature.h"

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

//move cursor to specific position
void gotoxy(int XPos, int YPos){
	//using ANSI escape code
	printf("\033[%d;%dH",YPos+1,XPos+1);
}

//delay running codes
void delay(int millisecond) {
	this_thread::sleep_for(chrono::milliseconds(millisecond));
}


void initialization(){

}

void characterCreation(){


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
	Color color;
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
		}

	} else {
		cout << "New game initializing... Starting character creation sequence." << endl;
		characterCreation();
	}


}

int main () {
	Menu();
}
