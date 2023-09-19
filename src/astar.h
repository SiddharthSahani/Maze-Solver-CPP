
#pragma once

#include "src/base_algo.h"
#include <vector>
#include <cmath>


class AStarAlgo : public BaseAlgo {

    public:
        AStarAlgo(const Maze& maze);
        void reset() override;
        bool completed() const override;
        void step() override;

    public:
        struct Score {
            float f = __FLT_MAX__;
            float g = __FLT_MAX__;
            float h = __FLT_MAX__;
        };

    private:
        std::vector<Score> m_scores;
        std::vector<int> m_open_set;
    
    private:
        float calculate_h(int row, int col) {
            int end_row = end_coord / col_count;
            int end_col = end_coord % col_count;
            return powf(end_row-row, 2) + powf(end_col-col, 2);
        }

};


AStarAlgo::AStarAlgo(const Maze& maze)
: BaseAlgo(maze), m_scores(maze.size()) {
    m_visited[start_coord] = true;
    m_open_set.push_back(start_coord);
    
    m_scores[start_coord].f = 0.0f;
    m_scores[start_coord].g = 0.0f;
    m_scores[start_coord].h = 0.0f;
}


void AStarAlgo::reset() {
    m_open_set.clear();
}


bool AStarAlgo::completed() const {
    return m_open_set.empty();
}


void AStarAlgo::step() {
    if (completed()) {
        return;
    }

    int current_index = 0;
    for (int i = 1; i < m_open_set.size(); i++) {
        if (m_scores[m_open_set[i]].f < m_scores[m_open_set[current_index]].f) {
            current_index = i;
        }
    }

    int cur_pos = m_open_set[current_index];
    m_open_set.erase(m_open_set.begin() + current_index);
    m_visited[cur_pos] = true;

    int cur_row = cur_pos / col_count;
    int cur_col = cur_pos % col_count;

    int left_pos = cur_pos - 1;
    int right_pos = cur_pos + 1;
    int up_pos = cur_pos - col_count;
    int down_pos = cur_pos + col_count;

    if (cur_col > 0 && !m_visited[left_pos] && m_maze[left_pos].type != CellType::WALL) {
        m_maze[left_pos].parent_coord = cur_pos;
        if (m_maze[left_pos].type == CellType::END) {
            make_path();
            return;
        }
        m_visited[left_pos] = true;
        m_open_set.push_back(left_pos);

        Score& score = m_scores[left_pos];
        score.g = m_scores[cur_pos].g + 1;
        score.h = calculate_h(cur_row, cur_col-1);
        score.f = score.g + score.h;
    }
    if ((cur_col+1) < col_count && !m_visited[right_pos] && m_maze[right_pos].type != CellType::WALL) {
        m_maze[right_pos].parent_coord = cur_pos;
        if (m_maze[right_pos].type == CellType::END) {
            make_path();
            return;
        }
        m_visited[right_pos] = true;
        m_open_set.push_back(right_pos);

        Score& score = m_scores[right_pos];
        score.g = m_scores[cur_pos].g + 1;
        score.h = calculate_h(cur_row, cur_col+1);
        score.f = score.g + score.h;
    }
    if (cur_row > 0 && !m_visited[up_pos] && m_maze[up_pos].type != CellType::WALL) {
        m_maze[up_pos].parent_coord = cur_pos;
        if (m_maze[up_pos].type == CellType::END) {
            make_path();
            return;
        }
        m_visited[up_pos] = true;
        m_open_set.push_back(up_pos);

        Score& score = m_scores[up_pos];
        score.g = m_scores[cur_pos].g + 1;
        score.h = calculate_h(cur_row-1, cur_col);
        score.f = score.g + score.h;
    }
    if ((cur_row+1) < row_count && !m_visited[down_pos] && m_maze[down_pos].type != CellType::WALL) {
        m_maze[down_pos].parent_coord = cur_pos;
        if (m_maze[down_pos].type == CellType::END) {
            make_path();
            return;
        }
        m_visited[down_pos] = true;
        m_open_set.push_back(down_pos);

        Score& score = m_scores[down_pos];
        score.g = m_scores[cur_pos].g + 1;
        score.h = calculate_h(cur_row+1, cur_col);
        score.f = score.g + score.h;
    }
}
