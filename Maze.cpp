/*
 * Jonathan Calderon Chavez
 * CS 315: with Dr. Ali A. Kooshesh
 * Project 01
 * This is the .cpp file to my Maze class, it contains the implementation for the definitions given in Maze.hpp
 */

#include "Maze.hpp"
#include <iostream>

Maze::Maze(std::string fileName ) {

    std::ifstream mazeStream;
    mazeStream.open(fileName);

    std::string row;
    while ( mazeStream >> row ) {  // reads and counts
        rows.push_back(row);
        col_total = row.size();
        rows_total++;
    }

    mazeStream.close();

    cell_population(rows);
    reset();

}

void Maze::cell_population(const std::vector<std::string>& Rows ) {

    for (int row = 0; row < Rows.size(); ++row) {

        for ( int col = 0; col < Rows.at(row).size() ; ++col ){

            if ( (Rows.at(row)).at(col) == '0' ){
                pathCells.push_back( std::make_tuple(row, col) );  //starts to sort path cells from wall cells
            }

            cells.push_back(std::make_tuple(row, col) );
        }
    }

    reset();
}

void Maze::find_start_end_cell() {

    for ( int i = 0; i < pathCells.size(); ++i ){

        if( std::get<0>(pathCells.at(i)) == 0 or std::get<0>(pathCells.at(i)) == rows_total - 1 ){  // def of start cell
            startCell = pathCells.at(i);
            explored.at(i) = true;
            break;
        }
        else if ( std::get<1>(pathCells.at(i)) == 0 or std::get<1>(pathCells.at(i)) == col_total - 1 ) {
            startCell = pathCells.at(i);
            explored.at(i) = true;
            break;
        }
    }
    for ( int f = 0; f < pathCells.size(); ++f ){

        if( ( std::get<0>(pathCells.at(f)) == 0 or std::get<0>(pathCells.at(f)) == rows_total - 1 )
        and !explored.at(f))  // def of end cell
        {
            endCell = pathCells.at(f);
            break;
        }
        else if (( std::get<1>(pathCells.at(f)) == 0 or std::get<1>(pathCells.at(f)) == col_total - 1 )
        and !explored.at(f) ) {
            endCell = pathCells.at(f);
            break;
        }
    }
}

void Maze::mazeSolver() {

    find_start_end_cell();
    pathFinder(startCell, endCell);
    PrintSolution();
    reset();
}

bool Maze::validMove( std::tuple<int, int> pCell1, std::tuple<int, int> pCell2) {

    bool valid = true;

    if( std::abs(std::get<1>(pCell1) - std::get<1>(pCell2)) == 1 and  // def of being adjacent cells
    std::abs(std::get<0>(pCell1) - std::get<0>(pCell2)) == 0 )
    {
        return valid;
    }

    return ((std::abs(std::get<0>(pCell1) - std::get<0>(pCell2)) == 1) and (   // def of being adjacent cells
            std::abs(std::get<1>(pCell1) - std::get<1>(pCell2)) == 0)) == valid;

}

int Maze::idxOfSuccessorWordFrom(std::tuple<int, int> Pathcell, int fromIdx) {

    for ( int idx = fromIdx; idx < size(); ++idx){

        if ( validMove( pathCells.at(idx), Pathcell )){

            if ( ! explored.at(idx) ){
                return idx;
            }
        }
    }

    return size();  // no Successor is found
}

std::vector<std::tuple<int , int> >Maze::pathFinder( std::tuple< int , int > start, std::tuple< int , int > end ) {

    path.push(start);  // base case
    std::tuple<int ,int> current;
    int idx = 0;

    // this is the backtracking algorithm
    while ( !path.empty() ) {   // if empty, then no path was found

        current = path.top();
        if (( std::get<0>(current) == std::get<0>(end) ) and (std::get<1>(current) == std::get<1>(end))){
            break;
        }

        idx = idxOfSuccessorWordFrom( current, 0 );

        if ( idx == size() ) {  // if dead end
            path.pop();   // then back track
        }
        else {
            path.push( pathCells.at(idx) );
            explored.at(idx) = true;
        }
    }

    return Solpath();
}

void Maze::PrintSolution() {
    
  if ( sPath.size() == 0 ){

    std::cout << "This maze does not have a solution";

  }

  else{ 


    int counter = 0;


    for (const auto & cell : cells){

        if ( counter  ==  col_total ){  // newline at the end of every row
            std::cout << std::endl;
            counter = 0;
        }
        if ( isMemberX(cell, pathCells) ){  // will format base on the cell type

            if ( isMemberX(cell, sPath ) ){
                std::cout << " ";
            }
            else{
                std::cout << "0";
            }
        }
        else{
            std::cout << "1";
        }

        counter++;
    }

  }

    std::cout << std::endl;

}

std::vector<std::tuple<int, int>> Maze::Solpath() {

    if (path.empty()) {
        return std::vector<std::tuple<int, int> >{};
    } else {
        while (!path.empty()) {

            sPath.insert(sPath.begin(), path.top());
            path.pop();

        }
    }
    return sPath;
}

void Maze::reset() {

    explored.resize(size());

    for (auto && f : explored){
        f = false;
    }
}

bool Maze::isMemberX(std::tuple<int, int> member, const std::vector<std::tuple<int, int>>& vec) {

    for (auto & i : vec){
        if ( (std::get<0>(i) == std::get<0>(member)) and (std::get<1>(i) == std::get<1>(member)) ){
            return true;
        }
    }

    return false;
}

