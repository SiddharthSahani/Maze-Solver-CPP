
#pragma once

#include "src/common.h"
#include <fstream>


Maze load_maze(const std::string& data) {
    Maze maze(data.size());
    for (int i = 0; i < data.size(); i++) {
        CellType& type = maze[i].type;
        
        switch (data[i]) {
            case '.': type = CellType::PATH; break;
            case '#': type = CellType::WALL; break;
            case 's': type = CellType::START; start_coord = i; break;
            case 'e': type = CellType::END; end_coord = i; break;
        }
    }

    return maze;
}


Maze load_maze_from_file(const char* filename, int& maze_rows, int& maze_cols) {
    std::fstream infile(filename, std::ios::in);

    if (!infile.good()) {
        maze_rows = 20;
        maze_cols = 35;
        return Maze(maze_rows * maze_cols);
    }

    infile >> maze_rows >> maze_cols;

    std::string data_string;
    infile >> data_string;

    return load_maze(data_string);
}
