# ENGG1340-COMP2113-Group181
  Welcome to ENGG1340/COMP2113 project group 181!

## Members
- Ho Chun Fai (3035789124)
- Tseung Kai Fai (3035787085)

## Description
"Novice Adventurer - Road to the Abyss" is an endless fight and survive turn-based role-playing game (RPG). User plays the role of a novice adventurer, explore different areas and fight with monsters.

## Game rules
Fight with evil monsters and survive!

1. It is a turn-based game, which means in a battle, player and monster would take turn to action.
2. Player can choose to attack, use mana skills, or escape. Similar to monsters (but without escape option) (which would be controlled by computer).
3. There are two ways of ending a battle, one is escape and another one is the HP of one side falls below (or equal to) 0, i.e. died.
4. When one side escape or died, the other side is considered the winner of the battle.
5. If the player wins, he/she would be awarded with exp.
6. After reaching the required exp, the player would level up. The status would increase.
7. After reaching specific levels, the player would be awarded with a trait point.
8. He/she can use trait points to enhance their status.
9. When the HP of the player falls below (or equal to) 0, i.e. died, he/she would be retrieved but he/she would lose all xp.

## Features
1. Background story
2. Player creation
3. Save/load module
4. Status module
   - Player
     -	Basic information (name, gender)
     -	Normal status (hp, mp, att, def, crit, etc.)
     -	Xp system (level, xp, required xp)     
     -	Trait system (every 5 levels gain a trait point and can be used in strengthening status)
   - Monsters
     -	Basic information (name, gender)
     -	Normal status (hp, mp, att, def, crit, etc.)
     -	Extra information (xp drop)
5. Region module
   -	Require minimum level to unlock different regions
   -	Player can choose which region to enter
   -	Different regions with different monsters having different level and status
   -	Monsters having random level and status, but bounded by limits
6. Battle module
   -	Actions to choose (attack, mana skills, escape)
   -	Randomness (e.g. critical attack)
   -	Winning award (xp)

## How do the coding elements get involved?

1. Generation of random game sets or events
   - `randomNumber()` in `usefulF.cpp` using `rand()` and `srand(time(NULL))` to generate a random number between 2 integers
   - `randomNumber()` is heavily used in `monsterCreation()` in `creature.cpp` to spawn 'random' monsters with random stats
   - critical attacks, and successful evasion determined by using `randomNumber()`, checking whether the result falls between a specific zone
2. Data structures for storing game status
   - A struct storing all status of the character
   - A struct storing all status of the monsters
3. Dynamic memory management
   - Using dynamic memory management to store monster status (See `Battle()` in `main_UnixLike.cpp`)
   - Monster status would be immediately deleted after battle finish avoid high usage of memory
4. File input/output
   - reading and saving player stats using ifstream and ofstream, saving the file in .sav format
5. Program codes in multiple files
   - separating codes of different parts and combining them using “Makefile”
   - custom header files linking all parts

## Compilation and execution instructions

1. Download all files into your computer
2. Open your computer's terminal, and go to the directory where the files are stored
3. Enter "make main_UnixLike"
4. Enter "./main_UnixLike" to run the program

## List of non-standard C/C++ libraries

1. unistd.h
   1. used in `getch()` in file `usefulF.cpp`
   - `getch()` is used to mimic the effect of `getch()`in header `conio.h` (unable to use in CS server), which is to read a single character from the keyboard
   - serve for creating a selection table, when user press the arrow button on the kwyboard, `getch()` can detect what key is pressed
2. termios.h
   1. used in `getxy()` and `getch()` in file `usefulF.cpp`
   - `getxy()` is used to get the current position of the cursor
   - both serve for creating a selection table, `getxy()`

## Testing

According to requirements:

> You should make sure your code can be successfully compiled in the Computer Science department's `academy11` server or the `academy21` server. Please indicate which of the two servers you have used for testing in your project documentation.

We tested our code and it successfully compiled on the `academy21` server.
