#include <limits>
#include <algorithm>

#include <constants.h>

#include "snake.h"

SnakePart::SnakePart()
    : m_position{Position(0,0)}
    , m_direction{constants::Direction::RIGHT}
{}

SnakePart::SnakePart(const Position &position, const constants::Direction &direction)
    : m_position(position)
    , m_direction(direction)
{}

const constants::Direction& SnakePart::get_direction() const
{
    return this->m_direction;
}

const Position& SnakePart::get_position() const
{
    return this->m_position;
}

void SnakePart::set_direction(const constants::Direction &direction)
{
    this->m_direction = direction;
}

void SnakePart::set_position(const Position &position)
{
    this->m_position = position;
}

Snake::Snake()
    : m_snake(1)
    , m_length(1)
{}

Snake::Snake(const Position& start_position, const constants::Direction& start_direction, const UShort& start_length, const UShort& max_length)
    : m_snake(max_length)
    , m_length{start_length}
{
    this->m_snake.front().m_position = start_position;
    this->m_snake.front().m_direction = start_direction;

    Position next_position{start_position};

    for (auto it_snake = this->m_snake.begin() + 1;
         it_snake != this->m_snake.begin() + this->m_length;
         ++it_snake)
    {
        switch (start_direction)
        {
        case constants::Direction::UP:
            ++next_position.first;
            break;
        case constants::Direction::DOWN:
            --next_position.first;
            break;
        case constants::Direction::LEFT:
            ++next_position.second;
            break;
        case constants::Direction::RIGHT:
            --next_position.second;
            break;
        }
        it_snake->m_position = next_position;
        it_snake->m_direction = start_direction;
    }
}

const SnakeVec& Snake::get_snake() const
{
    return this->m_snake;
}

const UShort& Snake::get_length() const
{
    return this->m_length;
}

void Snake::move()
{
    for (auto it_snake = this->m_snake.rend() - this->m_length;
         it_snake != this->m_snake.rend();
         ++it_snake)
    {
        if (it_snake == this->m_snake.rend() - 1)
        {
            switch (it_snake->m_direction)
            {
            case constants::Direction::UP:
                if (it_snake->m_position.first == std::numeric_limits<UShort>::min())
                {
                    it_snake->m_position.first = std::numeric_limits<UShort>::max();
                }
                else
                {
                    --it_snake->m_position.first;
                }
                break;
            case constants::Direction::DOWN:
                ++it_snake->m_position.first;
                break;
            case constants::Direction::LEFT:
                if (it_snake->m_position.second == std::numeric_limits<UShort>::min())
                {
                    it_snake->m_position.second = std::numeric_limits<UShort>::max();
                }
                else
                {
                    --it_snake->m_position.second;
                }
                break;
            case constants::Direction::RIGHT:
                ++it_snake->m_position.second;
                break;
            }
        }
        else if (it_snake->is_new)
        {
            // do not move the new item because it is iniitally located
            // on the same position as previous last item
            it_snake->is_new = false;
        }
        else
        {
            *it_snake = *std::next(it_snake);
        }
    }
}

void Snake::add_part()
{
    this->m_snake[m_length] = this->m_snake[m_length - 1];
    this->m_snake[m_length].is_new = true;
    ++this->m_length;
}

void Snake::set_front_direction(const constants::Direction &direction)
{
    this->m_snake.front().m_direction = direction;
}

const constants::Direction& Snake::get_front_direction() const
{
    return this->m_snake.front().m_direction;
}

bool Snake::is_occupied(Position position) const
{
    return this->m_snake.begin() + this->m_length != std::find_if(this->m_snake.begin(), this->m_snake.begin() + this->m_length, [&](const SnakePart &snake){
        return snake.m_position == position;
    });
}
