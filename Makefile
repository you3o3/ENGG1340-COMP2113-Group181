#continuously link in more files

FLAGS = -pedantic-errors -std=c++11

color.o: color.cpp color.h
	g++ $(FLAGS) -c $<

creature.o: creature.cpp creature.h
	g++ $(FLAGS) -c $<

weapon.o: weapon.cpp weapon.h
	g++ $(FLAGS) -c $<

test.o: test.cpp
	g++ $(FLAGS) -c $<

test: color.o creature.o weapon.o test.o
	g++ $(FLAGS) $^ -o $@
