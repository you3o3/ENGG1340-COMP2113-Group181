#include <bits/stdc++.h>
#include <cstdio>
#include <conio.h>
#include <math.h>
#include <dir.h>
#include <unistd.h>
#include <windows.h>
#include <dos.h>
#include <ctime>
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

//move cursor to specific position
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
        	if(i%3==0)
			printf(">>>\n");
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
		}
		
	} else {
		cout << "New game initializing... Starting character creation sequence." << endl;
		characterCreation();
	}
	
	
}

int main () {
	Menu();
}
