#include "helper.h"

#include <sys/stat.h>
#include <limits>
#include <random>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <sstream>

#include <constants.h>

namespace Tools
{
    int sizet_to_int(size_t val)
    {
        return (val <= INT_MAX) ? (int)((size_t)val) : -1;
    }

    unsigned int int_to_uint(int val)
    {
        return (val <= UINT_MAX) ? (unsigned int)((int)val) : UINT_MAX;
    }
}

Position rand_position(const UShort &max_x, const UShort &max_y)
{
    UShort max = std::max(max_x, max_y);
    std::random_device seed_gen;
    std::mt19937 gen(seed_gen());
    std::uniform_int_distribution<UShort> dist(0, max);
    Position rand_position{dist(gen), dist(gen)};
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

    // the last element is jus for clean up and not part of the actual snake. This is why we have to search up to length - 1
    return snake_vec.begin() + snake.get_length() - 1 != std::find_if(snake_vec.begin() + 1, snake_vec.begin() + snake.get_length() - 1,
                                                                      [&](const SnakePart &snake_part)
                                                                      {
                                                                          return snake_part.get_position() == snake_vec.front().get_position();
                                                                      });
}

bool snake_ate_food(const Snake &snake, const Food &food)
{
    SnakeVec snake_vec = snake.get_snake();
    return snake_vec.front().get_position() == food.get_position();
}

bool file_exists(const std::string &filename)
{
    struct stat buf;
    if (stat(filename.c_str(), &buf) != -1)
    {
        return true;
    }
    return false;
}

std::vector<std::pair<std::string, std::string>> get_highscore_list()
{
    std::vector<std::pair<std::string, std::string>> highscore_list{};
    std::ifstream input_highscore{constants::HIGHSCORE_PATH};
    if (input_highscore.is_open())
    {
        std::string str_line;
        while (std::getline(input_highscore, str_line))
        {
            std::istringstream ss_line{str_line};
            std::pair<std::string, std::string> entry;
            ss_line >> entry.first;
            ss_line >> entry.second;
            highscore_list.push_back(entry);
        }
    }
    else
    {
        // raise exception
    }
    return highscore_list;
}

void save_highscore_list(const std::vector<std::pair<std::string, std::string>> &highscore_list)
{
    if (highscore_list.empty())
    {
        if (!file_exists(constants::HIGHSCORE_PATH))
        {
            std::ofstream output_highscore{constants::HIGHSCORE_PATH};
            output_highscore << "LoupingLoui    5000" << std::endl;
            output_highscore << "Fritz          4000" << std::endl;
            output_highscore << "SumseBiene     3000" << std::endl;
            output_highscore << "KingKarl       2000" << std::endl;
            output_highscore << "LarsLarson     1000" << std::endl;
            output_highscore << "HasiHinterbein  500" << std::endl;
            output_highscore << "BlinderMoench   200" << std::endl;
            output_highscore << "LahmeEnte       100";
            output_highscore.close();
        }
    }
    else
    {
        std::ofstream output_highscore{constants::HIGHSCORE_PATH, std::ios::trunc};
        for (auto it = highscore_list.begin(); it != highscore_list.end(); ++it)
        {
            output_highscore << it->first << " " << it->second;
            if (it != highscore_list.end() - 1)
            {
                output_highscore << std::endl;
            }
        }
        output_highscore.close();
    }
}

bool is_new_highscore(const unsigned int &points)
{
    std::vector<std::pair<std::string, std::string>> highscore_list;
    highscore_list = get_highscore_list();
    auto it = std::find_if(highscore_list.begin(), highscore_list.end(),
                           [&](const auto &entry)
                           {
                               return Tools::int_to_uint(std::stoi(entry.second)) <= points;
                           });

    return it != highscore_list.end();
}
