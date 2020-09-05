#include "snake.h"
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
    for (auto it_snake = this->m_snake.begin();
         it_snake != this->m_snake.begin() + this->m_length;
         ++it_snake)
    {
        switch (it_snake->direction)
        {
        case constants::Direction::UP:
            --it_snake->position.first;
            break;
        case constants::Direction::DOWN:
            ++it_snake->position.first;
            break;
        case constants::Direction::LEFT:
            --it_snake->position.second;
            break;
        case constants::Direction::RIGHT:
            ++it_snake->position.second;
            break;
        }
        if (it_snake != this->m_snake.begin())
        {
            it_snake->direction = std::prev(it_snake)->direction;
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

bool Snake::is_occupied(Position position) const
{
    for (const auto &snake_part : this->m_snake)
    {
        if(snake_part.position == position)
        {
            return true;
        }
    }
    return false;
}
