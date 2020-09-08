#include "snake.h"

#include <limits>
#include "constants/constants.h"

Snake::Snake() :
m_snake(10), m_length(1)
{

}

Snake::Snake(const Position& start_position, const constants::Direction& start_direction, const UShort& start_length, const UShort& max_length) :
    m_snake(max_length), m_length(start_length)
{
    this->m_snake.front().position = start_position;
    this->m_snake.front().direction = start_direction;

    Position next_position{start_position};

    for (auto it_snake = this->m_snake.begin()+1;
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
        it_snake->position = next_position;
        it_snake->direction = start_direction;
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
            switch (it_snake->direction)
            {
            case constants::Direction::UP:
                if (it_snake->position.first == std::numeric_limits<UShort>::min())
                {
                    it_snake->position.first = std::numeric_limits<UShort>::max();
                }
                else
                {
                    --it_snake->position.first;
                }
                break;
            case constants::Direction::DOWN:
                ++it_snake->position.first;
                break;
            case constants::Direction::LEFT:
                if (it_snake->position.second == std::numeric_limits<UShort>::min())
                {
                    it_snake->position.second = std::numeric_limits<UShort>::max();
                }
                else
                {
                    --it_snake->position.second;
                }
                break;
            case constants::Direction::RIGHT:
                ++it_snake->position.second;
                break;
            }
        }
        else
        {
            *it_snake = *std::next(it_snake);
        }
    }
}

void Snake::add_part()
{
    this->m_snake[m_length] = this->m_snake[m_length-1];

    switch (this->m_snake[m_length].direction)
    {
    case constants::Direction::UP:
        ++this->m_snake[m_length].position.first;
        break;
    case constants::Direction::DOWN:
        --this->m_snake[m_length].position.first;
        break;
    case constants::Direction::LEFT:
        ++this->m_snake[m_length].position.second;
        break;
    case constants::Direction::RIGHT:
        --this->m_snake[m_length].position.second;
        break;
    }
    ++this->m_length;
}

void Snake::set_front_direction(const constants::Direction &direction)
{
    this->m_snake.front().direction = direction;
}

const constants::Direction& Snake::get_front_direction() const
{
    return this->m_snake.front().direction;
}

bool Snake::is_occupied(Position position) const
{
    return this->m_snake.begin() + this->m_length != std::find_if(this->m_snake.begin(), this->m_snake.begin() + this->m_length, [&](const SnakePart &snake){
        return snake.position == position;
    });
}
