#include "helper.h"

#include <random>

Position* rand_position(const UShort &max_x, const UShort &max_y)
{
    std::random_device seed_gen;
    std::mt19937 gen(seed_gen());
    std::uniform_int_distribution<UShort> dist(max_x, max_y);
    Position rand_position{ dist(gen), dist(gen) };
    Position *position = &rand_position ;
    return position;
}
