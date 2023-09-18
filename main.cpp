
#include <raylib.h>
#include <vector>


int row_count;
int col_count;
int cell_size;
int cell_padding;
int total_cell_size;

int start_coord = -1;
int end_coord = -1;

int last_edit_coord = -1;


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


void edit_maze(std::vector<Cell>& maze) {
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


int main() {
    row_count = 20;
    col_count = 35;
    cell_size = 25;
    cell_padding = 2;

    total_cell_size = cell_size + 2*cell_padding;
    InitWindow(col_count * total_cell_size, row_count * total_cell_size, "Pathfinding Algorithms");
    SetTargetFPS(60);

    std::vector<Cell> maze(row_count * col_count);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(DARKGRAY);

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) || IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
            edit_maze(maze);
        }

        draw_maze(maze);

        EndDrawing();
    }

    CloseWindow();
}
