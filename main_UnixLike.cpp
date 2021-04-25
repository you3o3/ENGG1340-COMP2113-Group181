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
#include <string>
#include <fstream>
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
  ifstream fin;
  fin.open("save.sav");
  if (fin.fail()){
    cout << "Open file fails. Please contact us." << endl;
    exit(1);
  }
  getline(fin, p.name);
  fin >> p.level;
  fin >> p.xp;
  fin >> p.xpReq;
  fin >> p.hp;
  fin >> p.maxhp;
  fin >> p.mp;
  fin >> p.maxmp;
  fin >> p.att;
  fin >> p.def;
  fin >> p.crit_chance;
  fin.close();

  return p;
}

//save file into user's computer
void saveFile(){
  ofstream fout;
  fout.open("save.sav");
  if (fout.fail()){
    cout << "Open file fails. Please contact us." << endl;
    exit(1);
  }
  fout << player.name << endl;
  fout << player.level << " ";
  fout << player.xp << " ";
  fout << player.xpReq << " ";
  fout << player.hp << " ";
  fout << player.maxhp << " ";
  fout << player.mp << " ";
  fout << player.maxmp << " ";
  fout << player.att << " ";
  fout << player.def << " ";
  fout << player.crit_chance;
  fout.close();
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
void Battle(int zone){
	monster *mob = new monster;
	*mob = monsterCreation(zone);
	int tempAttackBoost = 0;
	while(player.isAlive() && mob->isAlive()){
		clrscr();
		printBar("Battle");
	    cout << mob->name << endl;
	    cout << "Level: " << mob->level << endl;
	    cout << "HP: " << mob->hp << "/" << mob->maxhp << endl;
	    cout << "Damage Range: " << mob->att*(1-0.2) << " to " << (mob->att*1.5)*(1+0.2) << endl;
	    color.set("yellow");
	    cout << "--------------------------------------------------------------------------------" << endl;
            color.set("blue");
	    cout << player.name << endl;
	    cout << "Level: " << player.level << endl;
	    cout << "HP: " << player.hp << "/" << player.maxhp << endl;
	    cout << "MP: " << player.mp << "/" << player.maxmp << endl;
	    cout << "Damage Range: " << player.att + tempAttackBoost - player.att*0.2 << " to " << (player.att + tempAttackBoost)*1.5 + player.att*0.2 << endl;
	    cout << endl;
		color.set("green");
		printDelay("A monster appeared in front of you. What will you do?", 0, true);
		color.set("yellow");
		char selections[3][40] = {"Attack", "Mana Skill", "Escape"};
	  	int x = 0, y = 0, roundDamage = 0;
		getxy(&y, &x);
		switch(select(selections,0,3,y-1)){
			case 0:{
				printDelay("You attacked as hard as you can.", 40 , true);
				if(randomNumber(0,100) > 10){
					roundDamage = player.att + tempAttackBoost;
					if(randomNumber(0,100) <= player.crit_chance){
						color.set("red");
						printDelay("Critical Hit!", 40, true);
						roundDamage *= 1.5;
						color.set("green");
					}
					if(randomNumber(0,1) == 0){
						roundDamage -= randomNumber(1,player.att*0.2);
					} else {
						roundDamage += randomNumber(1,player.att*0.2);
					}
					printDelay("You dealt " + to_string(roundDamage) + " damage to the monster.", 40, true);
					mob->hp -= roundDamage;
				} else {
					printDelay("The monster dodged your attack!", 40, true);
				}
				break;
			}
			case 1:{
				char magic[2][40] = {
					"Boost Attack. 25% Mana Cost.",
					"Heal 50% HP. Cost number of HP healed."
				};
				
				getxy(&y, &x);
				switch(select(magic,0,2,y-1)){
					case 0:{
						if(player.mp >= player.maxmp/5){
							printDelay("You boosted your attack by 25%!", 40, true);
							player.mp -= player.maxmp/5;
							tempAttackBoost += 0.25*player.att;
						} else {
							printDelay("You could not boost your attack as you do not have enough mana!", 40, true);
						}
						break;
					}
					case 1:{
						if(player.maxhp/5 < player.mp){
							printDelay("You used your mana to recover yourself!", 40 ,true);
							player.hp += player.maxhp/2;
							player.mp -= player.maxhp/2;
						} else {
							printDelay("You could not heal yourself as you do not have enough mana!", 40, true);
						}
						break;
					}
				}
				break;
			}
			case 2:{
				if(randomNumber(1,100) <= 25) {
					//fail
					printDelay("You failed to escape!", 40, true);
				} else {
					printDelay("You escaped from the monster!", 40 ,true);
					delay(1000);
					delete mob;
					return;
				}
				break;
			}
		}
		roundDamage = 0;
		if(mob->hp > 0){
			switch(randomNumber(0,1)){
				case 0:{
					printDelay("The monster attacked you!", 40 , true);
					roundDamage = mob->att;
					if(randomNumber(0,100) <= mob->crit_chance){
						color.set("red");
						printDelay("Critical Hit!", 40, true);
						roundDamage *= 1.5;
						color.set("green");
					}
					if(randomNumber(0,1) == 0){
						roundDamage -= randomNumber(1,mob->att*0.2);
					} else {
						roundDamage += randomNumber(1,mob->att*0.2);
					}
					printDelay("The monster inflicted " + to_string(roundDamage) + " damage to you!", 40 ,true);
					player.hp -= roundDamage;
          delay(1000);
					break;
				}
				case 1:{
					color.set("red");
					printDelay("The monster gets angry and its upcoming attacks will be more desrctuive!", 40 ,true);
					mob->att += mob->att * 0.3;
          delay(1000);
					break;
				}
			}
		}
	}
	if(player.mp < player.maxmp){
		printDelay("You recovered some mp.", 40 ,true);
		player.mp += (player.maxmp * 0.2);
		if(player.mp > player.maxmp) player.mp = player.maxmp;
	}
	if(player.hp > 0 && mob->hp <= 0){
		printDelay("You have slained the monster! You gained " + to_string(mob->expDrop) + " xp.", 40, true);
		player.xpUp(mob->expDrop);
    	printDelay("Press any button to continue...", 40, true);
    	getch();
	}
	if(player.hp <= 0){
	//dead	
		color.set("red");
		printDelay("You have fainted! All your current xp has been lost!", 40, true);
		player.xp = 0;
		printDelay("Press any button to continue...", 40, true);
		getch();
		
	}
	delete mob;
}


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

  int x = 0, y = 0, lvlimit = (player.level - 1) / 10;
  getxy(&y, &x);
  int pos = select(regions,0,7,y-1);
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
    pos = select(regions,0,7,y-1);
  }
  player.position = regions[pos];
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

void show_player_status(){
  clrscr();
  color.set("yellow");
  printf("================================================================================\n");
	color.set("blue");
  cout << "Name:\t" + player.name << endl;
  if (!player.gender){
    cout << "Gender:\tFemale" << endl;
  } else {
    cout << "Gender:\tMale" << endl;
  }
  cout << "Level:\t" + to_string(player.level) << endl;
  cout << "XP:\t" + to_string(player.xp) + "/" + to_string(player.xpReq) << endl;
  cout << "HP:\t" + to_string(player.hp) + "/" + to_string(player.maxhp) << endl;
  cout << "MP:\t" + to_string(player.mp) + "/" + to_string(player.maxmp) << endl;
  color.set("yellow");
  printf("================================================================================\n");
	color.set("green");
  printDelay("Press any button to continue...", 40, true);
  getch();
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
        if (player.position == "City of Quart"){
          player.hp = player.maxhp;
          player.mp = player.maxmp;
          printDelay("Your hp and mp fully recovered!", 40, true);
          delay(1000);
        } else {
          //if in other places have chance to encounter monster
          if (player.hp + player.maxhp * 0.4 > player.maxhp){
            player.hp = player.maxhp;
          } else {
            player.hp += (int)(0.4 * player.maxhp);
          }
          if (player.mp + player.maxmp * 0.4  > player.maxmp){
            player.mp = player.maxmp;
          } else {
            player.mp += (int)(0.4 * player.maxmp);
          }
          printDelay("Your hp and mp partially recovered!", 40, true);
          delay(1000);
          if (randomNumber(0,5) == 0){
            color.set("red");
            printDelay("While resting, a monster suddenly attacks you!", 30, true);
            delay(1000);
            //Battle();
            color.set("green");
          }
        }

        break;
      }

      //3: Move on (during an adventure)
      case 3:{
        color.set("red");
        printDelay("You encounter a monster!", 40, true);
        delay(1000);
        for (int i = 0; i < 7; i++){
          if (regions[i] == player.position){
            Battle(i);
          }
        }
        if(player.hp <= 0){
        	player.position = "City of Quart";
        	printDelay("A mage resurrected you and teleported you back to the City of Quart...", 40, true);
        	player.hp = player.maxhp;
        	player.mp = player.maxmp;
        	delay(1000);
        }
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
        show_player_status();
        break;
      }

      //6: Save game
      case 6:{
        saveFile();
        printDelay("File saved!", 40 ,true);
        delay(1000);
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
