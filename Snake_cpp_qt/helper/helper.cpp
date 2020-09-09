#include "helper.h"

#include <limits>
#include <random>
#include <cmath>
#include <algorithm>

Position rand_position(const UShort &max_x, const UShort &max_y)
{
    UShort max = std::max(max_x, max_y);
    std::random_device seed_gen;
    std::mt19937 gen(seed_gen());
    std::uniform_int_distribution<UShort> dist(0, max);
    Position rand_position{ dist(gen), dist(gen) };
    return rand_position;
}

bool snake_hit_wall(const Snake &snake, const UShort &max_x, const UShort &max_y)
{
    SnakeVec snake_vec = snake.get_snake();

    if (snake_vec.front().get_position().first == max_x ||
        snake_vec.front().get_position().second == max_y ||
        snake_vec.front().get_position().first == std::numeric_limits<UShort>::max() ||
        snake_vec.front().get_position().second == std::numeric_limits<UShort>::max())
    {
        return true;
    }
    return false;
}

bool snake_hit_snake(const Snake &snake)
{
    SnakeVec snake_vec = snake.get_snake();

    return snake_vec.begin() + snake.get_length() != std::find_if(snake_vec.begin() + 1, snake_vec.begin() + snake.get_length(),
        [&](const SnakePart& snake_part){
        return snake_part.get_position() == snake_vec.front().get_position();
    });
}

bool snake_ate_food(const Snake &snake, const Food &food)
{
    SnakeVec snake_vec = snake.get_snake();
    return snake_vec.front().get_position() == food.get_position();
}
