#pragma once

#include <gtest/gtest.h>

#include <constants.h>
#include <helper.h>
#include <snake.h>
#include <food.h>


using namespace testing;

TEST(HelperTest, RandPosition)
{
    Position position = rand_position(10, 10);

   EXPECT_LE(position.first, 10);
   EXPECT_LE(position.second, 10);

   EXPECT_GE(position.first, 0);
   EXPECT_GE(position.second, 0);
}

TEST(HelperTest, SnakeHitWall)
{
    Position position{ 1, 1 };
    Snake snake{position, constants::Direction::DOWN , 1, 10};

    EXPECT_EQ(snake_hit_wall(snake, 2, 2), false);

    EXPECT_EQ(snake_hit_wall(snake, 1, 1), true);
}

TEST(HelperTest, SnakeHitSnake)
{
    Position position{ 5, 5 };
    Snake snake{position, constants::Direction::RIGHT , 6, 100};

    EXPECT_EQ(snake_hit_snake(snake), false);

    snake.set_front_direction(constants::Direction::UP);
    snake.move();
    snake.set_front_direction(constants::Direction::LEFT);
    snake.move();
    snake.set_front_direction(constants::Direction::DOWN);
    snake.move();

    EXPECT_EQ(snake_hit_snake(snake), true);

}

TEST(HelperTest, SnakeAteFood)
{
    Position position{ 1, 1 };
    Food food(position, 100);
    Snake snake{position, constants::Direction::DOWN , 1, 10};

    EXPECT_EQ(snake_ate_food(snake, food), true);

    position.first = 0;
    food.set_position(position);
    EXPECT_EQ(snake_ate_food(snake, food), false);
}
