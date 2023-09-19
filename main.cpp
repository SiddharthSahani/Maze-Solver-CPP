
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

    int algo_id = 1; // 1 is for dfs ; 2 is for bfs ; 3 is for a-start

    BaseAlgo* algo = nullptr;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(DARKGRAY);

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) || IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
            edit_maze(maze);
        }

        draw_maze(maze);

        if (IsKeyDown(KEY_ONE)) {
            algo_id = 1;
        } else if (IsKeyDown(KEY_TWO)) {
            algo_id = 2;
        } else if (IsKeyDown(KEY_THREE)) {
            algo_id = 3;
        }

        if (IsKeyPressed(KEY_SPACE) && (!algo || algo->completed())) {
            // spacebar is pressed and the current algorithm has found a path
            switch (algo_id) {
                case 1:
                    algo = new DepthFirstSearchAlgo(maze);
                    break;
                case 2:
                    algo = new BreadthFirstSearchAlgo(maze);
                    break;
                case 3:
                    algo = new AStarAlgo(maze);
                    break;
            }
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
