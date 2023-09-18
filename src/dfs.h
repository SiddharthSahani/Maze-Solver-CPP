
#pragma once

#include "src/base_algo.h"
#include <stack>


class DepthFirstSearchAlgo : public BaseAlgo {

    public:
        DepthFirstSearchAlgo(const Maze& maze);
        void reset() override;
        bool completed() const override;
        void step() override;

    private:
        std::stack<int> m_stack;

};


DepthFirstSearchAlgo::DepthFirstSearchAlgo(const Maze& maze)
: BaseAlgo(maze) {
    m_stack.push(start_coord);
    m_visited[start_coord] = true;
}


void DepthFirstSearchAlgo::reset() {
    while (!m_stack.empty()) {
        m_stack.pop();
    }
}


bool DepthFirstSearchAlgo::completed() const {
    return m_stack.empty();
}


void DepthFirstSearchAlgo::step() {
    if (completed()) {
        return;
    }

    int cur_coord = m_stack.top();
    m_stack.pop();

    int cur_row = cur_coord / col_count;
    int cur_col = cur_coord % col_count;

    int left_pos = cur_coord - 1;
    int right_pos = cur_coord + 1;
    int up_pos = cur_coord - col_count;
    int down_pos = cur_coord + col_count;

    if (cur_col > 0 && !m_visited[left_pos] && m_maze[left_pos].type != CellType::WALL) {
        m_maze[left_pos].parent_coord = cur_coord;
        if (m_maze[left_pos].type == CellType::END) {
            make_path();
            return;
        }
        m_visited[left_pos] = true;
        m_stack.push(left_pos);
    }
    if ((cur_col+1) < col_count && !m_visited[right_pos] && m_maze[right_pos].type != CellType::WALL) {
        m_maze[right_pos].parent_coord = cur_coord;
        if (m_maze[right_pos].type == CellType::END) {
            make_path();
            return;
        }
        m_visited[right_pos] = true;
        m_stack.push(right_pos);
    }
    if (cur_row > 0 && !m_visited[up_pos] && m_maze[up_pos].type != CellType::WALL) {
        m_maze[up_pos].parent_coord = cur_coord;
        if (m_maze[up_pos].type == CellType::END) {
            make_path();
            return;
        }
        m_visited[up_pos] = true;
        m_stack.push(up_pos);
    }
    if ((cur_row+1) < row_count && !m_visited[down_pos] && m_maze[down_pos].type != CellType::WALL) {
        m_maze[down_pos].parent_coord = cur_coord;
        if (m_maze[down_pos].type == CellType::END) {
            make_path();
            return;
        }
        m_visited[down_pos] = true;
        m_stack.push(down_pos);
    }
}
