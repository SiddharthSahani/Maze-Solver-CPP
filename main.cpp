
// includes raylib and common.h
#include "src/utils.h"
// algorithms
#include "src/dfs.h"
#include "src/bfs.h"
#include "src/astar.h"


int main() {
    int rows = 20;
    int cols = 35;
    int cell_size_px = 25;
    int cell_padding_px = 2;

    setup(rows, cols, cell_size_px, cell_padding_px);

    Maze maze(rows * cols);

    BaseAlgo* algo = nullptr;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(DARKGRAY);

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) || IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
            edit_maze(maze);
        }

        draw_maze(maze);

        if (IsKeyPressed(KEY_SPACE) && (!algo || algo->completed())) {
            // spacebar is pressed and the current algorithm has found a path
            // algo = new DepthFirstSearchAlgo(maze);
            // algo = new BreadthFirstSearchAlgo(maze);
            algo = new AStarAlgo(maze);
        }

        if (algo) {
            if (algo->completed()) {
                draw_path(algo->get_path());
            } else {
                algo->step();
                draw_visited(algo->get_visited());
            }
        }

        EndDrawing();
    }

    CloseWindow();
    delete algo;
}
