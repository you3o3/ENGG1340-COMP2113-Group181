#include<bits/stdc++.h>
#include<cstdio>
using namespace std;

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

void characterCreation(){
  
	
}

void loadSave(){
}

void saveFile(char fileName[]){
}

void Menu(){
	//TODO: if save file exists ask if player want to load the files
	//if not, create character using characterCreation()
	
	//Print UI Here
	
	if(save_exist("save.sav")){
		char a;
		cout << "File exists, do you want to load the save file? Y/N: ";
		a = getchar();
		if(a=='Y'){
			//load file
			loadSave();
		} else {
			cout << "Opening new save... Initializing character creation sequence." << endl;
		}
		
	} else {
		cout << "New game initializing... Starting character creation sequence." << endl;
		characterCreation();
		initialization();
	}
	
	
}

int main () {
	Menu();
}
