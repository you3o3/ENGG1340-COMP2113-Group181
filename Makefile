#continuously link in more files

FLAGS = -pedantic-errors -std=c++11

color.o: color.cpp color.h
	g++ $(FLAGS) -c $<

usefulF.o: usefulF.cpp usefulF.h
	g++ $(FLAGS) -c $<

creature.o: creature.cpp creature.h
	g++ $(FLAGS) -c $<

weapon.o: weapon.cpp weapon.h
	g++ $(FLAGS) -c $<

main.o: main.cpp
	g++ $(FLAGS) -c $<

main_UnixLike.o: main_UnixLike.cpp
	g++ $(FLAGS) -c $<

main: color.o creature.o weapon.o usefulF.o main.o
	g++ $(FLAGS) $^ -o $@

main_UnixLike: color.o creature.o weapon.o usefulF.o main_UnixLike.o
	g++ $(FLAGS) $^ -o $@
