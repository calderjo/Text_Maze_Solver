/*
 * Jonathan Calderon Chavez
 * CS 315:  Dr. Ali A. Kooshesh
 * Project 01
 *
 * This is program will take a txt file given by a user in main, this txt file shall be a solvable maze.
 * From this point the program will take the maze and find the solution to the maze, then prints it.
 */

#include <iostream>
#include "Maze.hpp"


int main(int argc, char *argv[]) {

    // This section is to check if file exists and can be used for this program
    if (argc != 2) {
        std::cout << "usage: " << argv[0]
                  << " inputFileNameThatContainsMaze\n";
        exit(1);
    }

    std::ifstream mazeStream;

    mazeStream.open(argv[1], std::ios_base::in);
    if (!mazeStream.is_open()) {
        std::cout << "Unable to open input file ->" << argv[1] << "<-\n";
        exit(2);
    }

    mazeStream.close();

    Maze Maze( argv[1] );
    Maze.mazeSolver();  // the process begins

}