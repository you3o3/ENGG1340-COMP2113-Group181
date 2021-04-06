#continuously link in more files

FLAGS = -pedantic-errors -std=c++11

color.o: color.cpp color.h
	g++ $(FLAGS) -c $<

creature.o: creature.cpp creature.h
	g++ $(FLAGS) -c $<

weapon.o: weapon.cpp weapon.h
	g++ $(FLAGS) -c $<

template.o: template.cpp
	g++ $(FLAGS) -c $<

template: color.o creature.o weapon.o template.o
	g++ $(FLAGS) $^ -o $@
