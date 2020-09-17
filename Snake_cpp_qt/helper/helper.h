#pragma once

#include <vector>
#include <utility>
#include <string>

#include "model/snake.h"
#include "model/food.h"

Position rand_position(const UShort &max_x, const UShort &max_y);
[[nodiscard]]bool snake_hit_wall(const Snake &snake, const UShort &max_x, const UShort &max_y);
[[nodiscard]]bool snake_hit_snake(const Snake &snake);
[[nodiscard]]bool snake_ate_food(const Snake &snake, const Food &food);
std::vector<std::pair<std::string, std::string>> get_highscore_list();
void save_highscore_list(const std::vector<std::pair<std::string, std::string>>& highscore_list);
bool is_new_highscore(const unsigned int& points);
