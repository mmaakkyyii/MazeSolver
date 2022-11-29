Cxx := g++
Inc := -I MazeSolver.hpp -I Adachi.hpp -I MazeDef.hpp


MazeSim: MazeSim.o MazeSolver.o Adachi.o
	g++ MazeSim.o MazeSolver.o Adachi.o -o MazeSim

MazeSim.o: MazeSim.cpp
	g++ -c -o MazeSim.o MazeSim.cpp  ${Inc}

MazeSolver.o: MazeSolver.cpp
	g++ -c -o MazeSolver.o MazeSolver.cpp ${Inc}

Adachi.o: Adachi.cpp
	g++ -c -o Adachi.o Adachi.cpp ${Inc}
clean:
	rm -f MazeSim.exe MazeSim.o MazeSolver.o Adachi
