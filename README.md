# ENGG1340-COMP2113-Group181
  Welcome to ENGG1340/COMP2113 project group 181!

## Members
- Ho Chun Fai ()
- Tseung Kai Fai (3035787085)

## Description
We want to implement a turn-based role-playing game (RPG). 

## Game rules
Fight with evil monsters and survive!

1. It is a turn-based game, which means in battle, player and monster would take turn to action.
2. Player can choose to attack, defend, use skills, use potions, or escape. Same as monsters (which would be controlled by computer).
3. There are two ways of ending a battle, one is escape and another one is the HP of one side falls below (or equal to) 0, i.e. died.
4. When one side escape or died, the other side is considered the winner of the battle.
5. If the player wins, he/she would be awarded with exp.
6. If the player kills the monster, he/she would have the chance to receive item awards.
7. After reaching the required exp, the player would level up. The status would increase.
8. Player could equip weapons to boost their status.
9. The game ends when the HP of the player falls below (or equal to) 0, i.e. died.


## Features
1. Guide module: how to play?
2. Save/load module
3. Background story
4. Status module
   - Player
     -	Basic information (name, gender)
     -	Normal status (hp, mp, att, def, skills, etc.)
     -	Exp system (level, exp, required exp)     
     -	Job system (warrior, knight, mage, etc.) (we plan to implement 2 jobs first, if time allows, we will add more)
     -	Weapons (sword, magic wand, etc.) (with different stats and drop rates)
     -	Extra attributes (physical/magic resist, etc.) (if time allows, we will add more)
   - Monsters
     -	Basic information (name, gender)
     -	Normal status (hp, mp, att, def, skills, etc.)
     -	Extra attributes (physical/magic resist, etc.)
5. Explore module
   -	Require minimum level to unlock different regions
   -	Player can choose which region to enter
   -	Different regions with different monsters having different level and status
   -	Monsters having random level and status, but bounded by limits
   -	Chance to encounter elite monsters
   -	Boss
6. Battle module
   -	Actions to choose (attack, defend, skills, potions, escape)
   -	Randomness (e.g. attack damage varies within certain range)
   -	Buffs/ debuffs
   -	Winning award (exp, items)

## How the coding elements are involved?
I copied below part from the code requirements. "Stage 1 Submission - Proposal" require us to "explain how each coding element 1 to 5 ... support your features."

1. Generation of random game sets or events
   - Explanation needed
2. Data structures for storing game status
   - Explanation needed
3. Dynamic memory management
   - Explanation needed
4. File input/output
   - Explanation needed
5. Program codes in multiple files
   - Explanation needed
