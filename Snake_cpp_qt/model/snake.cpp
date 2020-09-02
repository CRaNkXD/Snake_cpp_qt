#include "snake.h"
#include "constants/constants.h"

Snake::Snake() :
m_snake(10), m_length(1)
{

}

Snake::Snake(const Position& start_position, const constants::Direction& start_direction, const UShort& start_length, const UShort& max_length) :
    m_snake(max_length), m_length(start_length)
{
    Position next_position{start_position};

    for (UShort i = 0; i < this->m_length; ++i)
    {
        if (i == 0)
        {
            this->m_snake[i].position = start_position;
            this->m_snake[i].direction = start_direction;
        }
        else
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
            this->m_snake[i].position = next_position;
            this->m_snake[i].direction = start_direction;
        }
    }
}

void Snake::move()
{
    for (UShort i = 0; i < this->m_length; ++i)
    {
        switch (this->m_snake[i].direction)
        {
        case constants::Direction::UP:
            ++this->m_snake[i].position.first;
            break;
        case constants::Direction::DOWN:
            --this->m_snake[i].position.first;
            break;
        case constants::Direction::LEFT:
            --this->m_snake[i].position.second;
            break;
        case constants::Direction::RIGHT:
            ++this->m_snake[i].position.second;
            break;
        }
        if (i != 0)
        {
            this->m_snake[i].direction = this->m_snake[i-1].direction;
        }
    }
}

const SnakeComplete& Snake::get_snake() const
{
    return this->m_snake;
}

void Snake::add_part()
{

}

void Snake::set_front_direction(const constants::Direction &direction)
{
    this->m_snake.front().direction = direction;
}
