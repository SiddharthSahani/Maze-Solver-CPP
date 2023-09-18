
#pragma once

#include "src/common.h"
#include <raylib.h>


// for drawing the maze
inline int cell_size, cell_padding, total_cell_size;
//to avoid toggling of cell in quick successions
inline int last_edit_coord = -1;


void setup(int _rows, int _cols, int _cell_size, int _cell_padding) {
    row_count = _rows;
    col_count = _cols;
    cell_size = _cell_size;
    cell_padding = _cell_padding;
    total_cell_size = cell_size + 2*cell_padding;

    InitWindow(col_count * total_cell_size, row_count * total_cell_size, "Maze Solver");
    SetTargetFPS(60);
}


void draw_maze(const Maze& maze) {
    const Color path_cell_color = DARKBLUE;
    const Color wall_cell_color = WHITE;
    const Color start_cell_color = GREEN;
    const Color end_cell_color = RED;

    for (int row = 0; row < row_count; row++) {
        for (int col = 0; col < col_count; col++) {
            int cell_coord = row * col_count + col;

            Color draw_color;
            switch (maze[cell_coord].type) {
                case CellType::PATH:  draw_color = path_cell_color;  break;
                case CellType::WALL:  draw_color = wall_cell_color;  break;
                case CellType::START: draw_color = start_cell_color; break;
                case CellType::END:   draw_color = end_cell_color;   break;
            }

            int draw_pos_x = col * total_cell_size + cell_padding;
            int draw_pos_y = row * total_cell_size + cell_padding;
            DrawRectangle(draw_pos_x, draw_pos_y, cell_size, cell_size, draw_color);
        }
    }
}


void edit_maze(Maze& maze) {
    Vector2 mouse_pos = GetMousePosition();

    // checking if clicked position is in maze bounds
    if (mouse_pos.x > col_count*total_cell_size || mouse_pos.y > row_count*total_cell_size) {
        return;
    }

    int row = mouse_pos.y / (cell_size + 2*cell_padding);
    int col = mouse_pos.x / (cell_size + 2*cell_padding);
    int cell_coord = row * col_count + col;

    if (cell_coord == last_edit_coord) {
        return;
    }

    CellType& type = maze[cell_coord].type;

    if (IsMouseButtonDown(MouseButton::MOUSE_BUTTON_LEFT)) {
        // editing for wall and path
        switch (type) {
            case CellType::PATH:  type = CellType::WALL; break;
            case CellType::WALL:  type = CellType::PATH; break;
            case CellType::START: type = CellType::PATH; start_coord = -1; break;
            case CellType::END:   type = CellType::PATH; end_coord = -1; break;
        }
    } else {
        // editing for start and end
        switch (type) {
            case CellType::PATH:
            case CellType::WALL:
                if (start_coord == -1) {
                    type = CellType::START;
                    start_coord = cell_coord;
                } else if (end_coord == -1) {
                    type = CellType::END;
                    end_coord = cell_coord;
                }
                break;
            case CellType::START:
                type = CellType::PATH;
                start_coord = -1;
                break;
            case CellType::END:
                type = CellType::PATH;
                end_coord = -1;
                break;
        }
    }
    
    last_edit_coord = cell_coord;
}
