#pragma once

#include <string>
#include <array>

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

constexpr std::string HIGHSCORE_PATH = "highscore.txt";

constexpr uint NUMBER_OF_DIFFICULTIES = 4;
constexpr uint DEFAULT_DIFFICULTY = 1; // Normal
constexpr std::array<std::string, NUMBER_OF_DIFFICULTIES> DIFFICULTY_LABELS { "Easy", "Normal", "Hard", "Insane" };
constexpr std::array<int, NUMBER_OF_DIFFICULTIES> DIFFICULTY_SPEEDS { 300, 150, 75, 30 }; // ms per tick
}