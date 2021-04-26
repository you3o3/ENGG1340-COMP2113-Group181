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

string Story;

//if file exist then return true, otherwise return false
inline bool save_exist(const string & save) {
    if (FILE * file = fopen(save.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }
}

//basic character creation
character characterCreation() {
    string name;
    FILE * save = fopen("save.sav", "rw");
    printBar("???");
    printDelay("In an abyss, a voice whispered: ", 40, false);
    printDelay("Welcome, novice.... I wonder what's your name..?", 60, true);
    cout << "> ";
    cin >> name;
    cout << name;
    printDelay("... a good name, indeed..*So, are you a boy or a girl?", 40, true);
    char selections[2][40] = {
        "Boy",
        "Girl"
    };
    int x = 0, y = 0;
    getxy( & y, & x);
    switch (select(selections, 0, 2, y - 1)) {
    case 0: {
        character p(name, true);
        printDelay("A boy will grow up and become a man... given enough challenges...", 60, true);
        delay(400);
        return p;
    }
    case 1: {
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
void Introduction(int section) {
    clrscr();
    printBar("INTRODUCTION");
    switch (section) {
    case 1: {
        Story = "Many places are surrounded by a transparent wall that prevent people who are not good enough from entering,*and block monsters who are too strong from harming people.*Legend says that The Wall is a magic casted by the Almighty Mage Kinn at the end of his life, *but no one knows how long would it lasts for.*The Wall prevents people from entering the dangerous area and block monsters,*but still, there are places that are not being protected.*Adventurers, the best of all, protect weak traders travelling around the globe and fight monsters to obtain loot.*Over the years, many become brave warriors, enduring hardships and dangers.*Some become loyal knights, guarding the weak and the poor.*Some become wise sorcerers, mastering magics and knowledge.*And now... in the City of Quart, a novice adventurer is creating history";
        break;
    }
    case 2: {
        Story = "Located inside the innermost layer.*The Adventurers' valley is at the east of the City of Quart.*Though it is inside the innermost layer of The Wall,*small monsters often appear,*and it is the best place for new adventurers to strengthen their skills*to prepare for entering more dangerous places.";
        break;

    }
    case 3: {
        Story = "Located between the second inner layer and the innermost layer.*The silent forest is a huge forest that fills up the spaces between*the second inner layer and the innermost layer of The Wall.*There are many monsters and animals in the forest, so it is not silent at all…*Don’t know who named the forest… Is it a prank,*or a long time ago the forest is actually silent?*No one knows.*Anyways, it is a must for travelers to pass though place if they want to go to other cities.*So many of them hired adventurers to protect them.*The monsters in silent forest are relatively dangerous for common people,*but it is still a piece of cake for experienced adventurers.";
        break;
    }
    case 4: {
        Story = "Located between second inner layer and second outer layer.*Second inner layer and second outer layer separate the beginners and advanced adventurers.*People with no combat skills seldom enter those dangerous places.*The cemetery of the dark is one of the biggest places located between the second inner and outer layer.*Inside the cemetery, you will encounter undead creatures like zombies.";
        break;
    }
    case 5: {
        Story = "Located between second outer layer and the outermost layer.*The forsaken castle ‘was’ a rumor among experienced adventurers…*They said that the castle is left behind for a long time,*until an adventurer accidentally discovered it… and he never come back.*Now the rumor is proven to be true.*You re-discover it, and decide to do what the previous adventurer do – go inside the castle and explore it.";
        break;
    }
    case 6: {
        Story = "Located beyond the outermost layer of The Wall.*Only the top adventurers approved by The Wall can go outside the outermost layer of The Wall,*and explore anything they want.*However, none of the monsters outside The Wall is weak…*They are fighting with each other all the time…*But most of them are still bloodthirsty to humans' flesh,*hoping one day The Wall would disappear.*You’ll feel yourself living in another world when you reach there.*Enjoy the chaos, adventurer…";
        break;
    }
    case 7: {
        Story = "Located beyond the outermost layer of The Wall.*This place is supposed to have no WALL, but seems like it has.*No one knows what’s inside the mind of the Almighty Mage*when he made a separate wall to block the nest of dragons.*The wall allows you to go inside… This means that you have reached a great achievement in combating.*But are you really sure to go into the nest, and provoke the dignity of DRAGONs?";
        break;
    }
    case 8: {

        break;
    }
    }
    printDelay(Story, 0, true);
    cout << "Press any button to continue..." << endl;
    getch();
}

void initialization() {

}
//load file from user and recover state based on the info in file
character loadSave() {
    character p;
    //TODO: load file and save status into player, note that player can't save other status like monsters, and save file during battle is prohibited
    ifstream fin;
    fin.open("save.sav");
    if (fin.fail()) {
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
    fin >> p.traitpoints;
    fin >> p.traitAllocation[0];
    fin >> p.traitAllocation[1];
    fin >> p.traitAllocation[2];
    fin >> p.traitAllocation[3];
    fin >> p.traitAllocation[4];
    fin.close();

    return p;
}

//save file into user's computer
void saveFile() {
    ofstream fout;
    fout.open("save.sav");
    if (fout.fail()) {
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
    fout << player.crit_chance << " ";
    fout << player.traitpoints << " ";
    fout << player.traitAllocation[0] << " " << player.traitAllocation[1] << " " << player.traitAllocation[2] << " " << player.traitAllocation[3] << " " << player.traitAllocation[4];
    fout.close();
}

//guide request and provide guide if user want
void Guide() {
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
void Battle(int zone) {
    monster * mob = new monster;
    * mob = monsterCreation(zone);
    int tempAttackBoost = 0;
    while (player.isAlive() && mob -> isAlive()) {
        clrscr();
        printBar("Battle");
        cout << mob -> name << endl;
        cout << "Level: " << mob -> level << endl;
        cout << "HP: " << mob -> hp << "/" << mob -> maxhp << endl;
        cout << "Damage Range: " << round(mob -> att * (1 - 0.2)) << " to " << round((mob -> att * 1.5) * (1 + 0.2)) << endl;
        color.set("yellow");
        cout << "--------------------------------------------------------------------------------" << endl;
        color.set("blue");
        cout << player.name << endl;
        cout << "Level: " << player.level << endl;
        cout << "HP: " << player.hp << "/" << player.maxhp << endl;
        cout << "MP: " << player.mp << "/" << player.maxmp << endl;
        cout << "Damage Range: " << round(player.att + tempAttackBoost - player.att * 0.2) << " to " << round((player.att + tempAttackBoost) * 1.5 + player.att * 0.2) << endl;
        cout << endl;
        color.set("green");
        printDelay("A monster appeared in front of you. What will you do?", 0, true);
        color.set("yellow");
        char selections[3][40] = {
            "Attack",
            "Mana Skill",
            "Escape"
        };
        int x = 0, y = 0, roundDamage = 0;
        getxy( & y, & x);
        switch (select(selections, 0, 3, y - 1)) {
        case 0: {
            printDelay("You attacked as hard as you can.", 40, true);
            if (randomNumber(0, 100) > 10) {
                roundDamage = player.att + tempAttackBoost;
                if (randomNumber(1, 100) <= player.crit_chance) {
                    color.set("red");
                    printDelay("Critical Hit!", 40, true);
                    roundDamage = roundDamage * 1.5;
                    color.set("green");
                }
                if (randomNumber(0, 1) == 0) {
                    roundDamage -= randomNumber(1, player.att * 0.2);
                } else {
                    roundDamage += randomNumber(1, player.att * 0.2);
                }
                printDelay("You dealt " + to_string(roundDamage) + " damage to the monster.", 40, true);
                mob -> hp -= roundDamage;
            } else {
                printDelay("The monster dodged your attack!", 40, true);
            }
            break;
        }
        case 1: {
            char magic[2][40] = {
                "Boost Attack. 25% Mana Cost.",
                "Heal HP. Mana Cost: 1/3 of total HP."
            };

            getxy( & y, & x);
            switch (select(magic, 0, 2, y - 1)) {
            case 0: {
                if (player.mp >= player.maxmp / 5) {
                    printDelay("You boosted your attack by 25%!", 40, true);
                    player.mp -= player.maxmp / 5;
                    tempAttackBoost += 0.25 * player.att;
                } else {
                    printDelay("You could not boost your attack as you do not have enough mana!", 40, true);
                }
                break;
            }
            case 1: {
                if (player.mp >= player.maxhp / 3) {
                    printDelay("You used your mana to recover yourself!", 40, true);
                    player.hp += player.maxhp / 2;
                    if (player.hp > player.maxhp) player.hp = player.maxhp;
                    player.mp -= player.maxhp / 3;
                } else {
                    printDelay("You could not heal yourself as you do not have enough mana!", 40, true);
                }
                break;
            }
            }
            break;
        }
        case 2: {
            if (randomNumber(1, 100) <= 25) {
                //fail
                printDelay("You failed to escape!", 40, true);
            } else {
                printDelay("You escaped from the monster!", 40, true);
                delete mob;
                return;
            }
            break;
        }
        }
        roundDamage = 0;
        if (mob -> hp > 0) {
            switch (randomNumber(0, 1)) {
            case 0: {
                printDelay("The monster attacked you!", 40, true);
                roundDamage = mob -> att;
                if (randomNumber(0, 100) <= mob -> crit_chance) {
                    color.set("red");
                    printDelay("Critical Hit!", 40, true);
                    roundDamage *= 1.5;
                    color.set("green");
                }
                if (randomNumber(0, 1) == 0) {
                    roundDamage -= randomNumber(1, mob -> att * 0.2);
                } else {
                    roundDamage += randomNumber(1, mob -> att * 0.2);
                }
                if (randomNumber(1, 100) > (5 + 3 * player.traitAllocation[4])) {
                    printDelay("The monster inflicted " + to_string(roundDamage) + " damage to you!", 40, true);
                    player.hp -= roundDamage;
                    delay(1000);
                } else {
                    printDelay("You dodged the monster's attack!", 40, true);
                }
                break;
            }
            case 1: {
                color.set("red");
                printDelay("The monster gets angry and its upcoming attacks will be more desrctuive!", 40, true);
                mob -> att += mob -> att * 0.3;

                break;
            }
            }
        }
        delay(1000);
    }
    if (player.mp < player.maxmp) {
        printDelay("You recovered some mp.", 40, true);
        player.mp += (player.maxmp * 0.2);
        if (player.mp > player.maxmp) player.mp = player.maxmp;
    }
    if (player.hp > 0 && mob -> hp <= 0) {
        printDelay("You have slained the monster! You gained " + to_string(mob -> expDrop) + " xp.", 40, true);
        player.xpUp(mob -> expDrop);
        printDelay("Press any button to continue...", 40, true);
        getch();
    }
    if (player.hp <= 0) {
        //dead	
        color.set("red");
        printDelay("You have fainted! All your current xp has been lost!", 40, true);
        player.xp = 0;
        color.set("green");
        printDelay("Press any button to continue...", 40, true);
        getch();
        clrscr();
        printBar("City of Quart");
        player.position = "City of Quart";
        printDelay("When you wake up, you find yourself inside your room in the City of Quart...", 40, true);
        printDelay("You have no idea what's going on...", 40, true);
        player.hp = player.maxhp;
        player.mp = player.maxmp;
        delay(1000);
    }
    delete mob;
}

//------------------------------------------------------------------------------------------------------
// the following should be made inside a file called region.cpp and region.h
void Adventure_option() {
    clrscr();

    printDelay("The Wall blocks ignorant adventurers from entering dangerous places.", 20, true);
    printDelay("So, " + player.name + ", where do you want to go?", 20, true);
    color.set("yellow");
    printf("================================================================================\n");
    color.set("green");
    printDelay("List of places: ", 40, true);

    int x = 0, y = 0, lvlimit = (player.level - 1) / 10;
    getxy( & y, & x);
    int pos = select(regions, 0, 7, y - 1);
    while (lvlimit < pos) {
        color.set("red");
        printDelay("The Wall blocked your way...", 20, true);
        printDelay("Please choose a place that is suitable for your current level.", 20, true);
        delay(1000);
        clrscr();
        color.set("yellow");
        printf("================================================================================\n");
        color.set("green");
        printDelay("List of places: ", 40, true);
        getxy( & y, & x);
        pos = select(regions, 0, 7, y - 1);
    }
    player.position = regions[pos];
    printDelay("You're walking to the " + player.position + ".", 20, true);
    delay(1000);
    if (!regionFlag[pos]) {
        Introduction(pos + 2);
        regionFlag[pos] = true;
    }
}

int OptionsInRegion() {
    clrscr();
    printBar(player.position);
    printDelay("You are inside the " + player.position + ".", 20, true);
    printDelay(player.name + ", What do you want to do?", 20, true);
    char selections[7][40] = {
        "Move on",
        "Take a rest (heal)",
        "Return to city",
        "Check my status",
        "Save game",
        "Exit game",
        "Allocation of Trait Points"
    };
    int x = 0, y = 0, to_return = 0;
    getxy( & y, & x);
    to_return = select(selections, 0, 7, y - 1);
    // converting to_return to options in Region()
    if (to_return == 0) {
        return 3;
    }
    if (to_return == 1) {
        return 2;
    }
    return to_return + 2;
}

int OptionsInCity() {
    clrscr();
    printBar("City of Quart");
    printDelay("You are inside the " + player.position + ".", 20, true);
    printDelay(player.name + ", What do you want to do?", 20, true);
    char selections[6][40] = {
        "Take an adventure",
        "Take a rest (heal)",
        "Check my status",
        "Save game",
        "Exit game",
        "Allocation of Trait Points"
    };
    int x = 0, y = 0, to_return = 0;
    getxy( & y, & x);
    to_return = select(selections, 0, 6, y - 1);
    // converting to_return to options in Region()
    if (to_return <= 1) {
        return to_return + 1;
    } else {
        return to_return + 3;
    }
}

void show_player_status() {
    clrscr();
    color.set("yellow");
    printf("================================================================================\n");
    color.set("blue");
    cout << "Name:\t" + player.name << endl;
    if (!player.gender) {
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

void Region() {
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
    while (options != 7) {
        if (player.position == "City of Quart") {
            options = OptionsInCity();
        } else {
            options = OptionsInRegion();
        }

        switch (options) {
            //1: Take an adventure (in city)
        case 1: {
            Adventure_option();
            break;
        }

        //2: Take a rest (heal)
        case 2: {
            printDelay("Recovering hp and mp...", 60, true);
            if (player.position == "City of Quart") {
                player.hp = player.maxhp;
                player.mp = player.maxmp;
                printDelay("Your hp and mp fully recovered!", 40, true);
                delay(1000);
            } else {
                //if in other places have chance to encounter monster
                if (player.hp + player.maxhp * 0.4 > player.maxhp) {
                    player.hp = player.maxhp;
                } else {
                    player.hp += (int)(0.4 * player.maxhp);
                }
                if (player.mp + player.maxmp * 0.4 > player.maxmp) {
                    player.mp = player.maxmp;
                } else {
                    player.mp += (int)(0.4 * player.maxmp);
                }
                printDelay("Your hp and mp partially recovered!", 40, true);
                delay(1000);

                if (randomNumber(0, 5) == 0) {
                    color.set("red");
                    printDelay("While resting, a monster suddenly attacks you!", 30, true);
                    delay(1000);
                    color.set("green");
                    for (int i = 0; i < 7; i++) {
                        if (regions[i] == player.position) {
                            Battle(i);
                        }
                    }

                }
            }

            break;
        }

        //3: Move on (during an adventure)
        case 3: {
            color.set("red");
            printDelay("You encountered a monster!", 40, true);
            delay(1000);
            for (int i = 0; i < 7; i++) {
                if (regions[i] == player.position) {
                    Battle(i);
                }
            }
            break;
        }

        //4: Return to city (during an adventure)
        case 4: {
            player.position = "City of Quart";
            printDelay("Returning to City of Quart...", 60, true);
            delay(1000);
            break;
        }

        //5: Check my status
        case 5: {
            show_player_status();
            break;
        }

        //6: Save game
        case 6: {
            saveFile();
            printDelay("File saved!", 40, true);
            delay(1000);
            break;
        }

        //7: Exit game
        case 7: {
            printDelay("Thank you for playing this game!", 40, true);
            break;
        }

        //8: Allocation of trait points
        case 8: {
            int x = 0, y = 0;
            bool cont = true;
            char selections[2][40] = {
                "Yes",
                "No"
            };
            char options[7][40] = {
                "Add 1 point to HP",
                "Add 1 point to Attack",
                "Add 1 point to MP",
                "Add 1 point to Critical Hit Chance",
                "Add 1 point to Evasion Chance",
                "Finish"
            };
            while (cont) {
                clrscr();
                printBar("Traits");
                cout << "Name: " << player.name << "   Unspent trait points: " << player.traitpoints << endl;
                cout << "Current Level: " << player.level << endl;
                cout << "Trait points allocation : HP " << player.traitAllocation[0] << ", Attack " << player.traitAllocation[1] << ", MP " << player.traitAllocation[2] << ", Crit Chance " << player.traitAllocation[3] << ", Evasion " << player.traitAllocation[4] << endl;
                cout << "Current stat increases: HP: x" << pow(1.235, player.traitAllocation[0]) << endl;
                cout << "                    Attack: x" << pow(1.17, player.traitAllocation[1]) << endl;
                cout << "                        MP: x" << pow(1.205, player.traitAllocation[2]) << endl;
                cout << "               Crit Chance: x" << 5 + 4 * player.traitAllocation[3] << "%" << endl;
                cout << "            Evasion Chacne: x" << 5 + 3 * player.traitAllocation[4] << "%" << endl;
                color.set("red");
                cout << "Attention. All changes made here cannot be reversed. Choose wisely." << endl;
                color.set("green");
                getxy( & y, & x);
                switch (select(options, 0, 6, y - 1)) {
                case 0: {
                    if (player.traitpoints <= 0) {
                        printDelay("You do not have enough trait points!", 30, true);
                        delay(500);
                    } else {
                        cout << "One point will be allocated to HP and your boost will increase to x" << pow(1.235, player.traitAllocation[0] + 1) << endl << "Are you sure?" << endl;
                        getxy( & y, & x);
                        switch (select(selections, 0, 2, y - 1)) {
                        case 0: {
                            player.traitAllocation[0]++;
                            player.traitpoints--;
                            printDelay("One point has been allocated to HP.", 30, true);
                            player.traitSet(0);
                            delay(500);
                            break;

                        }
                        case 1: {
                            printDelay("No change was made to the traits!", 30, true);
                            delay(500);
                            break;
                        }
                        }
                    }
                    break;
                }
                case 1: {
                    if (player.traitpoints <= 0) {
                        printDelay("You do not have enough trait points!", 30, true);
                        delay(500);
                    } else {
                        cout << "One point will be allocated to Attack and your boost will increase to x" << pow(1.17, player.traitAllocation[1] + 1) << endl << "Are you sure?" << endl;
                        getxy( & y, & x);
                        switch (select(selections, 0, 2, y - 1)) {
                        case 0: {
                            player.traitAllocation[1]++;
                            player.traitpoints--;
                            printDelay("One point has been allocated to Attack.", 30, true);
                            player.traitSet(1);
                            delay(500);
                            break;

                        }
                        case 1: {
                            printDelay("No change was made to the traits!", 30, true);
                            delay(500);
                            break;
                        }
                        }
                    }
                    break;
                }
                case 2: {
                    if (player.traitpoints <= 0) {
                        printDelay("You do not have enough trait points!", 30, true);
                        delay(500);
                    } else {
                        cout << "One point will be allocated to MP and your boost will increase to x" << pow(1.205, player.traitAllocation[2] + 1) << endl << "Are you sure?" << endl;
                        getxy( & y, & x);
                        switch (select(selections, 0, 2, y - 1)) {
                        case 0: {
                            player.traitAllocation[2]++;
                            player.traitpoints--;
                            printDelay("One point has been allocated to MP.", 30, true);
                            player.traitSet(2);
                            delay(500);
                            break;

                        }
                        case 1: {
                            printDelay("No change was made to the traits!", 30, true);
                            delay(500);
                            break;
                        }
                        }
                    }
                    break;
                }
                case 3: {
                    if (player.traitpoints <= 0) {
                        printDelay("You do not have enough trait points!", 30, true);
                        delay(500);
                    } else {
                        cout << "One point will be allocated to Crit Chance and your chacne will be " << 5 + 4 * (player.traitAllocation[3] + 1) << "%" << endl << "Are you sure?" << endl;
                        getxy( & y, & x);
                        switch (select(selections, 0, 2, y - 1)) {
                        case 0: {
                            player.traitAllocation[3]++;
                            player.traitpoints--;
                            printDelay("One point has been allocated to Crit Chance.", 30, true);
                            player.traitSet(3);
                            delay(500);
                            break;

                        }
                        case 1: {
                            printDelay("No change was made to the traits!", 30, true);
                            delay(500);
                            break;
                        }
                        }
                    }
                    break;
                }
                case 4: {
                    if (player.traitpoints <= 0) {
                        printDelay("You do not have enough trait points!", 30, true);
                        delay(500);
                    } else {
                        cout << "One point will be allocated to Evasion and your chance will be " << 5 + 3 * (player.traitAllocation[4] + 1) << "%" << endl << "Are you sure?" << endl;
                        getxy( & y, & x);
                        switch (select(selections, 0, 2, y - 1)) {
                        case 0: {
                            player.traitAllocation[4]++;
                            player.traitpoints--;
                            printDelay("One point has been allocated to Evasion.", 30, true);
                            delay(500);
                            break;

                        }
                        case 1: {
                            printDelay("No change was made to the traits!", 30, true);
                            delay(500);
                            break;
                        }
                        }
                    }
                    break;
                }
                case 5: {
                    printDelay("Leaving the trait menu....", 40, true);
                    cont = false;
                    delay(500);
                    break;
                }
                }
            }

        }
        }
    }
}
//------------------------------------------------------------------------------------------------------

//menu of the game
void Menu() {
    //TODO: if save file exists ask if player want to load the files
    //if not, create character using characterCreation()

    //Print UI Here
    clrscr();
    int i;
    color.set("yellow");
    printf("================================================================================\n");
    color.set("blue");
    printf("                    Novice Adventurer    -    Road to the Abyss                 \n");
    color.set("yellow");
    printf("                                                                                \n");
    color.set("green");
    printf("|                                   |   \n");
    color.set("yellow");
    printf("Loading: \n");
    printf("================================================================================\n");
    color.set("red");
    for (i = 1; i <= 100; i++) {
        gotoxy(i / 3, 3);
        if (i % 3 == 0) printf(">>>\n");
        gotoxy(23, 4);
        printf("%d%%", i);
        delay(10);
    }
    color.set("green");
    delay(500);
    //removed the flash effect which is avaliable in windows version
    //because system("Color __") is Windows-specific
    gotoxy(0, 6);

    if (save_exist("save.sav")) {
        char a;
        cout << "File exists, do you want to load the save file? Y/N: ";
        a = getchar();
        if (a == 'Y') {
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

int main() {
    Menu();
}
