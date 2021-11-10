/*
 * Jonathan Calderon Chavez
 * CS 315: Dr. Ali A. Kooshesh
 * Project 01
 *
 * This is the header file to Maze class, and will be used in main.cpp.
 * contain member function definition for Maze
 */

#include<fstream>
#include<vector>
#include<tuple>
#include<stack>

class Maze{

public:
    Maze( std::string fileName );
    void mazeSolver( );


private:

    std::vector<std::string> rows;
    int rows_total = 0;           // Just keeps track of total num of row and col
    int col_total = 0;

    void cell_population(const std::vector<std::string>& Rows );  //This function will number every cell
    // with its row and col number, and will ident. path cells

    // these vectors will contain all path cells
    // all cells that are not in pathCell are consider wall cells in cells
    std::vector< std::tuple<int , int> > cells;
    std::vector< std::tuple<int, int> > pathCells;
    int size(){
        return pathCells.size();
    }

    // this function will determine if a cell belongs in a vector.
    bool isMemberX( std::tuple<int, int > member, const std::vector<std::tuple<int, int>>& vec);

    std::vector<bool> explored;  // This will be used to insure that no cell are reused

    void reset();  // sets all path cells back to not explored
    // this will help find position to mark off in used

    std::tuple< int , int >  startCell;  // these are the equal of start and target function of
    std::tuple< int , int >  endCell;   // ladder problem

    void find_start_end_cell( );  // to find the start and end of the maze

    // stacks keeps records of the order of the path cells used
    std::stack< std::tuple< int, int> > path;

    // This function will find the answer to the maze
    std::vector<std::tuple<int, int>> pathFinder(std::tuple<int, int> start, std::tuple<int, int> end);

    // This function will determine if the distance between two cell are adjacent
    bool validMove( std::tuple<int, int> pCell1, std::tuple<int, int> pCell2);

    // will find the next available path cell to move to
    int idxOfSuccessorWordFrom(std::tuple<int, int>, int fromIdx);


    std::vector<std::tuple<int, int>> Solpath( );  // will organize the path from start to end
    std::vector<std::tuple<int, int>>sPath;  // will contain the path

    void PrintSolution();  // prints the solved maze
};