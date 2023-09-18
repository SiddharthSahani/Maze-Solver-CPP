
#include <raylib.h>
#include <vector>


int row_count;
int col_count;
int cell_size;
int cell_padding;


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


void draw_maze(const std::vector<Cell>& maze) {
    const Color path_cell_color = DARKBLUE;
    const Color wall_cell_color = WHITE;
    const Color start_cell_color = GREEN;
    const Color end_cell_color = RED;

    for (int row = 0; row < row_count; row++) {
        for (int col = 0; col < col_count; col++) {
            int cell_coord = row * col_count + col;

            Color draw_color;
            switch (maze[cell_coord].type) {
                case CellType::PATH: draw_color = path_cell_color; break;
                case CellType::WALL:  draw_color = wall_cell_color;  break;
                case CellType::START: draw_color = start_cell_color; break;
                case CellType::END:  draw_color = end_cell_color;  break;
            }

            int draw_pos_x = col * (cell_size + 3*cell_padding);
            int draw_pos_y = row * (cell_size + 3*cell_padding);
            DrawRectangle(draw_pos_x, draw_pos_y, cell_size, cell_size, draw_color);
        }
    }
}


int main() {
    row_count = 20;
    col_count = 35;
    cell_size = 25;
    cell_padding = 2;

    int total_cell_size = cell_size + 2*cell_padding;
    InitWindow(col_count * total_cell_size, row_count * total_cell_size, "Maze Solver");
    SetTargetFPS(60);

    std::vector<Cell> maze(row_count * col_count);
    maze[0].type = CellType::WALL;
    maze[1].type = CellType::START;
    maze[2].type = CellType::END;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(DARKGRAY);

        draw_maze(maze);

        EndDrawing();
    }

    CloseWindow();
}
