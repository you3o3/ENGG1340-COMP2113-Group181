#include "creature.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using std::string;

bool generalStats::isAlive(){
  return hp > 0;
}

char regionMonsters[10][40][6] = {{
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

character::character(string nameInputed, bool genderInputed){
  name = nameInputed;
  gender = genderInputed;
  level = 1;
  maxhp = 10;                             //tbc
  maxmp = 5;                             //tbc
  hp = maxhp;
  mp = maxmp;
  att = 10;                               //tbc
  def = 10;                               //tbc
  xp = 0;
  xpReq = 50;                            //tbc
  position = "City of Quart";
  // role, skill, tbc
}

//level up
void character::lvUp(){
  xp -= xpReq;
  level += 1;
  xpReq = 50 (level * level - level) ;

  //status increase
  maxhp += level * 3;
  maxmp += level * 2;
  att = level * 10 + 3;
  def = level * 7;

  //recover hp, mp
  hp = maxhp;
  mp = maxmp;

  printDelay("You level up! Your current level is: " + level, 40, true);
  printDelay("You need " + xpReq + " xp to reach next level", 40, true);
  printDelay("Your hp and mp fully recovered!", 40, true);
}

monster monsterCreation(int regionGrade, string name){
  monster newMob;
  srand(time(NULL));
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
