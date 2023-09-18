
#pragma once

#include "src/common.h"


class BaseAlgo {

    public:
        BaseAlgo(const Maze& maze) : m_maze(maze), m_visited(maze.size(), false) {}
        const std::vector<bool>& get_visited() const { return m_visited; }

        // need to override these 2 methods
        virtual bool completed() const = 0;
        virtual void step() = 0;

    private:
        Maze m_maze;
        std::vector<bool> m_visited;

};
