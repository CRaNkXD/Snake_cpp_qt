#pragma once

#include <vector>
#include <utility>

#include "constants/constants.h"

typedef unsigned short UShort ;
typedef std::pair<UShort, UShort> Position;
struct SnakePart{
   Position position;
   constants::Direction direction;
};
typedef std::vector<SnakePart> SnakeComplete;

class Snake
{
private:
    SnakeComplete m_snake;
    UShort m_length;

public:
    Snake();
    Snake(const Position& start_position, const constants::Direction& start_direction, const UShort& start_length, const UShort& max_length);
    const SnakeComplete& get_snake() const;
    const UShort& get_length() const;
    void move();
    void add_part();
    void set_front_direction(const constants::Direction& direction);
};
