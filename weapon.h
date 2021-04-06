#ifndef WEAPON_H
#define WEAPON_H

#include <string>

struct Weapon{
  std::string name;
  int att;
  int def;
  // add more features?

  Weapon(std::string, int, int);
};

#endif
