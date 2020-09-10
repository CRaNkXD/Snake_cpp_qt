#pragma once

#include <vector>
#include <utility>

#include "constants/constants.h"

typedef unsigned short UShort ;
typedef std::pair<UShort, UShort> Position;

class SnakePart{
private:
    Position m_position;
    constants::Direction m_direction;
    bool is_new{false};

public:
    SnakePart();
    SnakePart(const Position &position, const constants::Direction &direction);
    const constants::Direction& get_direction() const;
    void set_direction(const constants::Direction &direction);
    const Position& get_position() const;
    void set_position(const Position &position);

    friend class Snake;
};

typedef std::vector<SnakePart> SnakeVec;

class Snake
{
private:
    SnakeVec m_snake;
    UShort m_length;

public:
    Snake();
    Snake(const Position& start_position, const constants::Direction& start_direction, const UShort& start_length, const UShort& max_length);
    const SnakeVec& get_snake() const;
    const UShort& get_length() const;
    void move();
    void add_part();
    void set_front_direction(const constants::Direction& direction);
    const constants::Direction& get_front_direction() const;
    bool is_occupied(Position position) const;
};
