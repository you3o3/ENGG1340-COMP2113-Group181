#ifndef CREATURE_H
#define CREATURE_H

#include "weapon.h"
#include <vector>

struct generalStats{
  std::string name;
  int level;
  int hp, maxhp;
  int mp, maxmp;
  int att;
  int def;
  bool isAlive();
};

struct character : public generalStats {
  bool gender;
  int xp, xpReq;
  std::string role;
  std::vector<Weapon> weapons;           // weapon struct in weapon.h and weapon.cpp
  int skills[100];
  std::string position;
  character(std::string nameInputed = "", bool genderInputed = true);
  void lvUp();
  void expUp(int);

};

struct monster : public generalStats {
  std::string itemdrop;
  int expDrop;
};

// usage: monster x = monsterCreation(regionGrade);
monster monsterCreation(int);

extern character player;

#endif
