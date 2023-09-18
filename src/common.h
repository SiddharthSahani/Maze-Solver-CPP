
#pragma once

#include <vector>


// maze dimensions
inline int row_count, col_count;
// coordinates of start and end points (required by the algorithm)
inline int start_coord = -1, end_coord = -1;


enum class CellType {
    PATH,
    WALL,
    START,
    END,
};


struct Cell {
    CellType type = CellType::PATH;
    int parent_coord = -1; // required for making the path when algorithm is finished
};


typedef std::vector<Cell> Maze;
