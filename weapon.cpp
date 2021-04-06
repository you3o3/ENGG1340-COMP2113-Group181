#include "weapon.h"
#include <iostream>

using std::string;

Weapon::Weapon(string nameInputed, int attInputed, int defInputed){
  name = nameInputed;
  att = attInputed;
  def = defInputed;
}
