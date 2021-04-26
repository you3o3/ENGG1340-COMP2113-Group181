#include "creature.h"

#include "usefulF.h"

#include <iostream>

#include <cstdlib>

#include <ctime>

#include <string>

#include <cmath>

using namespace std;

bool generalStats::isAlive() {
    return hp > 0;
}

char regions[8][40] = {
    "Adventurers' valley (lv1+)",
    "Slient forest (lv11+)",
    "Cemetery of the dark (lv21+)",
    "Forsaken castle (lv31+)",
    "Other side of the world (lv41+)",
    "Nest of dragons (lv51+)",
    "Abyss (requirement?\?\?)"
};

bool regionFlag[8] = {
    false,
    false,
    false,
    false,
    false,
    false,
    false
};

char regionMonsters[6][10][40] = {
    {
        "Green Slime",
        "Mini Slime",
        "Corrupted Slime",
        "Sparky",
        "Water trappers",
        "Giant Mantis",
        "Shroomitail",
        "Glittering Slime",
        "Boulder",
        "Frosted"
    },
    {
        "Screammaker",
        "Greedy Goblin",
        "Mangled Ogre",
        "Reaper",
        "Haunted",
        "Trapped Soul",
        "Glowing Spores",
        "Entangled Vines",
        "Goblin Leader",
        "Ogre Commander"
    },
    {
        "Brain Rot",
        "Headless",
        "Bloodthrist",
        "Armored Zombie",
        "Son of the Tempest",
        "Mimic",
        "Ravenger",
        "Hanged",
        "Suffocater",
        "Aetherized Zombie"
    },
    {
        "Witch Apprentice",
        "Evitch",
        "Spider Puppet",
        "Hellhound",
        "Wicked",
        "Witchcraft Master",
        "Salem",
        "Frankenpuppet",
        "Headslicer",
        "Raven"
    },
    {
        "Merezeda",
        "Mazerguito",
        "Dripper",
        "Vampire",
        "Haemoclotter",
        "Father of all",
        "Dracula",
        "Spike",
        "Amber",
        "Dream Maker"
    },
    {
        "Rathalos",
        "Tempest",
        "Valhazaard",
        "Behemoth",
        "Raijin",
        "Fieryostra",
        "Hellstrix",
        "Dragon Rider",
        "Alflection",
        "Ruler"
    }
};

//constructor of character
character::character(string nameInputed, bool genderInputed) {
    name = nameInputed;
    gender = genderInputed;
    level = 1;
    maxhp = 40;
    maxmp = 20;
    hp = maxhp;
    mp = maxmp;
    att = 10;
    def = 10;
    xp = 0;
    xpReq = 50;
    crit_chance = 5;
    position = "City of Quart";
    traitpoints = 1;
    traitAllocation[0] = 0;
    traitAllocation[1] = 0;
    traitAllocation[2] = 0;
    traitAllocation[3] = 0;
    traitAllocation[4] = 0;
    // role, skill, tbc
}

//level up
void character::lvUp() {
    xp -= xpReq;
    level += 1;
    if (level % 5 == 0) {
        traitpoints++;
    }
    xpReq = 50 * (level * level - level);

    //status increase
    maxhp += level * 3;
    maxmp += level * 2;
    att = (level * 10 + 3) * pow(1.17, traitAllocation[1]);
    def = level * 7;

}

//Add traits
void character::traitSet(int option) {
    if (option == 0) {
        if (traitAllocation[0] != 1) {
            maxhp = maxhp / pow(1.235, traitAllocation[0] - 1) * pow(1.235, traitAllocation[0]);
        } else {
            maxhp = maxhp * pow(1.235, traitAllocation[0]);
        }
        hp = maxhp;
    } else if (option == 1) {
        if (traitAllocation[1] != 1) {
            att = att / pow(1.17, traitAllocation[1] - 1) * pow(1.17, traitAllocation[1]);
        } else {
            att = att * pow(1.17, traitAllocation[1]);
        }
    } else if (option == 2) {
        if (traitAllocation[2] != 1) {
            maxmp = maxmp / pow(1.205, traitAllocation[2] - 1) * pow(1.205, traitAllocation[2]);
        } else {
            maxmp = maxmp * pow(1.205, traitAllocation[2]);
        }
        mp = maxmp;
    } else if (option == 3) {
        crit_chance = 5 + 4 * traitAllocation[3];
    }
}

//increase exp
void character::xpUp(int xpGain) {
    xp += xpGain;
    bool is_lvUp = false;
    while (xp >= xpReq) {
        lvUp();
        is_lvUp = true;
    }
    if (is_lvUp) {
        //recover hp, mp
        hp = maxhp;
        mp = maxmp;
        printDelay("You level up! Your current level is: " + to_string(level), 40, true);
        printDelay("You need " + to_string(xpReq) + " xp to reach next level.", 40, true);
        printDelay("Your hp and mp fully recovered!", 40, true);
    }
}

monster monsterCreation(int regionGrade) {
    monster newMob;
    int n = randomNumber(0, 9);
    newMob.name = regionMonsters[regionGrade][n];

    //newMob.expDrop = 100000;
    if (player.level >= (regionGrade + 1) * 10 + 1) {
        printDelay("Your level is higher than the region level.", 40, true);
        printDelay("Your xp gain would be significantly reduced.", 40, true);
        delay(1000);
        newMob.expDrop = randomNumber(1, 3) * (regionGrade + 1) * 100;
        newMob.level = (regionGrade + 1) * 10 + randomNumber(-4, 0);
    } else {
        newMob.expDrop = randomNumber(1, 3) * regionGrade * 100 + player.xpReq * 0.5;
        newMob.level = player.level + randomNumber(-2, 2);
        if (newMob.level <= 0) newMob.level = 1;
    }
    newMob.expDrop = 1000000;
    //mimic player status at the same level
    newMob.hp = 40;
    for (int i = 0; i < newMob.level; i++) {
        newMob.hp += newMob.level * 3;
    }
    newMob.att = newMob.level * 10 + 3;

    //adjustment
    newMob.hp = newMob.hp * randomNumber(10, 20) / 10 + regionGrade * randomNumber(10, 40);
    newMob.maxhp = newMob.hp;
    newMob.att = newMob.att * 0.7 + (regionGrade + 1) * 2 + randomNumber(-5, +5) * (regionGrade + 1);
    newMob.crit_chance = 5 + randomNumber(-3, 3);
    newMob.def = (regionGrade + 1) * 8;
    return newMob;
}

character player;

/* check

int main(){
  character player("John", true);
  std::cout << player.name << std::endl;
  std::cout << player.gender << std::endl;
  std::cout << player.level << std::endl;
  std::cout << player.maxhp << std::endl;
  std::cout << player.maxmp << std::endl;
  std::cout << player.hp << std::endl;
  std::cout << player.mp << std::endl;
  std::cout << player.att << std::endl;
  std::cout << player.def << std::endl;
  std::cout << player.exp << std::endl;
  std::cout << player.expReq << std::endl;


  return 0;

}
//*/
