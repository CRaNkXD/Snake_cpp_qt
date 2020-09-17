#pragma once

#include <string>

namespace constants {
/**
 * Defines the directions the snake can move.
 */
enum class Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT,

};

const std::string HIGHSCORE_PATH = "highscore.txt";
}
