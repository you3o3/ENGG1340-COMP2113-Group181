#ifndef CREATURE_H
#define CREATURE_H

#include <string>

struct generalStats {
    std::string name;
    int level;
    int hp, maxhp;
    int mp, maxmp;
    int att;
    int def;
    // crit_chance ranging from 0 to 100 (%)
    int crit_chance;
    bool isAlive();
};

struct character : public generalStats {
    bool gender;
    int xp, xpReq;
    int skills[100];
    std::string position;
    character(std::string nameInputed = "", bool genderInputed = true);
    void lvUp();
    void xpUp(int);
    void traitSet(int);
    int traitpoints;
    int traitAllocation[5];
};

struct monster : public generalStats {
    std::string itemdrop;
    int expDrop;
};

// usage: monster x = monsterCreation(regionGrade);
monster monsterCreation(int);

extern character player;
extern char regionMonsters[6][10][40];
extern char regions[8][40];
extern bool regionFlag[8];

#endif
