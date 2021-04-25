#include "creature.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using std::string;

bool generalStats::isAlive(){
  return hp > 0;
}

char regions[7][40] = {
  "Adventurers' valley (lv1+)",
  "Slient forest (lv11+)",
  "Cemetery of the dark (lv21+)",
  "Forsaken castle (lv31+)",
  "Other side of the world (lv41+)",
  "Nest of dragons (lv51+)",
  "Abyss (requirement?\?\?)"
};

char regionMonsters[6][10][40] = {{
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
},{
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
},{
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
}, {
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
},{
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
}, {
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
}};


//constructor of character
character::character(string nameInputed, bool genderInputed){
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
  // role, skill, tbc
}

//level up
void character::lvUp(){
  xp -= xpReq;
  level += 1;
  xpReq = 50 * (level * level - level) ;

  //status increase
  maxhp += level * 3;
  maxmp += level * 2;
  att = level * 10 + 3;
  def = level * 7;

}

//increase exp
void character::xpUp(int xpGain){
  xp += xpGain;
  bool is_lvUp = false;
  while (xp >= xpReq){
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

monster monsterCreation(int regionGrade){
  monster newMob;
  int n = randomNumber(0,9);
  newMob.name = regionMonsters[regionGrade][n];

  newMob.def = (regionGrade+1) * 8;
  //newMob.expDrop = 100000;
  newMob.expDrop = randomNumber(1,3) * regionGrade * 100 + player.xpReq * 0.5;
  newMob.hp = player.hp * randomNumber(10,20) / 10 + regionGrade * randomNumber(10,40);
  newMob.maxhp = newMob.hp;
  newMob.level = player.level + randomNumber(1,4);
  newMob.att = newMob.level * 7 + (regionGrade+1) * 2;
  // refer to ppt 5.1, details tbc
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
