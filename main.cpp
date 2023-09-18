
// includes raylib and common.h
#include "src/utils.h"


int main() {
    int rows = 20;
    int cols = 35;
    int cell_size_px = 25;
    int cell_padding_px = 2;

    setup(rows, cols, cell_size_px, cell_padding_px);

    Maze maze(rows * cols);

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
