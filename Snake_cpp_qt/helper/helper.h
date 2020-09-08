#pragma once

#include "model/snake.h"
#include "model/food.h"

Position rand_position(const UShort &max_x, const UShort &max_y);
[[nodiscard]]bool snake_hit_wall(const Snake &snake, const UShort &max_x, const UShort &max_y);
[[nodiscard]]bool snake_hit_snake(const Snake &snake);
[[nodiscard]]bool snake_ate_food(const Snake &snake, const Food &food);
