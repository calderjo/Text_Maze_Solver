mazeSolver: main.o Maze.o
	g++ -std=c++17 -g  main.o Maze.o -o mazeSolver

main.o: main.cpp
	g++ -std=c++17 -c -g  main.cpp

Maze.o: Maze.cpp
	g++ -std=c++17 -c -g  Maze.cpp

clean:
	rm *.o mazeSolver
