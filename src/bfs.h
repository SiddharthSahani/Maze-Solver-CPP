
#pragma once

#include "src/base_algo.h"
#include <deque>


class BreadthFirstSearchAlgo : public BaseAlgo {

    public:
        BreadthFirstSearchAlgo(const Maze& maze);
        void reset() override;
        bool completed() const override;
        void step() override;

    private:
        std::deque<int> m_queue;

};


BreadthFirstSearchAlgo::BreadthFirstSearchAlgo(const Maze& maze)
: BaseAlgo(maze) {
    m_queue.push_back(start_coord);
    m_visited[start_coord] = true;
}


void BreadthFirstSearchAlgo::reset() {
    m_queue.clear();
}


bool BreadthFirstSearchAlgo::completed() const {
    return m_queue.empty();
}


void BreadthFirstSearchAlgo::step() {
    if (completed()) {
        return;
    }

    int cur_coord = m_queue.front();    
    m_queue.pop_front();

    int cur_row = cur_coord / col_count;
    int cur_col = cur_coord % col_count;

    int left_pos = cur_coord - 1;
    int right_pos = cur_coord + 1;
    int up_pos = cur_coord - col_count;
    int down_pos = cur_coord + col_count;

    if (cur_col > 0 && !m_visited[left_pos] && m_maze[left_pos].type != CellType::WALL) {
        m_maze[left_pos].parent_coord = cur_coord;
        m_queue.push_back(left_pos);
        if (m_maze[left_pos].type == CellType::END) {
            make_path();
            return;
        }
        m_visited[left_pos] = true;
    }
    if ((cur_col+1) < col_count && !m_visited[right_pos] && m_maze[right_pos].type != CellType::WALL) {
        m_maze[right_pos].parent_coord = cur_coord;
        m_queue.push_back(right_pos);
        if (m_maze[right_pos].type == CellType::END) {
            make_path();
            return;
        }
        m_visited[right_pos] = true;
    }
    if (cur_row > 0 && !m_visited[up_pos] && m_maze[up_pos].type != CellType::WALL) {
        m_maze[up_pos].parent_coord = cur_coord;
        m_queue.push_back(up_pos);
        if (m_maze[up_pos].type == CellType::END) {
            make_path();
            return;
        }
        m_visited[up_pos] = true;
    }
    if ((cur_row+1) < row_count && !m_visited[down_pos] && m_maze[down_pos].type != CellType::WALL) {
        m_maze[down_pos].parent_coord = cur_coord;
        m_queue.push_back(down_pos);
        if (m_maze[down_pos].type == CellType::END) {
            make_path();
            return;
        }
        m_visited[down_pos] = true;
    }
}
