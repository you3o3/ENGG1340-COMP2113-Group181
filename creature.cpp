#include "creature.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using std::string;

bool generalStats::isAlive(){
  return hp > 0;
}

character::character(string nameInputed, bool genderInputed){
  name = nameInputed;
  gender = genderInputed;
  level = 1;
  maxhp =0;                             //tbc
  maxmp =0;                             //tbc
  hp = maxhp;
  mp = maxmp;
  att =0;                               //tbc
  def =0;                               //tbc
  xp = 0;
  xpReq =0;                            //tbc
  // role, skill, position tbc
}

void character::lvUp(){
  xp -= xpReq;
  level += 1;
  xpReq +=0;                           //tbc
  // stats increase tbc
  // hp/mp full recover tbc
  // print message tbc
}

void character::expUp(int xpGain){
  xp += xpGain;
  while (xp >= xpReq){
    lvUp();
  }
}

monster monsterCreation(int regionGrade){
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
