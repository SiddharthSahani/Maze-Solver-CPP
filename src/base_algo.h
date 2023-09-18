
#pragma once

#include "src/common.h"


class BaseAlgo {

    public:
        BaseAlgo(const Maze& maze) : m_maze(maze), m_visited(maze.size(), false) {}
        const std::vector<bool>& get_visited() const { return m_visited; }
        const std::vector<int>& get_path() const { return m_path; }
        void make_path(); // subclasses have to call this function after they have found a path

        // need to override these 3 methods
        virtual void reset() = 0;
        virtual bool completed() const = 0;
        virtual void step() = 0;

    protected:
        Maze m_maze;
        std::vector<bool> m_visited;
        std::vector<int> m_path;

};


void BaseAlgo::make_path() {
    // resets the underlying data-structure
    reset();

    int parent = end_coord;
    while (parent != -1) {
        m_path.push_back(parent);
        parent = m_maze[parent].parent_coord;
    }
}
