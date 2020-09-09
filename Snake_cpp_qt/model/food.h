#pragma once
#include "snake.h"

class Food{
private:
   Position m_position;
   bool m_eaten{true};
   const int m_points;

public:
   Food(const Position& position, const int& points);
   const Position& get_position() const;
   void set_position(const Position &position);
   const int& get_points() const;
   const bool& is_eaten() const;
   void set_eaten (const bool &eaten);
};
