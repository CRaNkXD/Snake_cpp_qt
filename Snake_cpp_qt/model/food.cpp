#include "food.h"

Food::Food(const Position& position, const int& points)
    : m_position{position}
    , m_points{points}
{}

const Position& Food::get_position() const
{
    return this->m_position;
}

void Food::set_position(const Position &position)
{
    this->m_position = position;
}

const int& Food::get_points() const
{
    return this->m_points;
}

const bool& Food::is_eaten() const
{
    return this->m_eaten;
}

void Food::set_eaten (const bool &eaten)
{
    this->m_eaten = eaten;
}
