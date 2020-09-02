#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "model/snake.h"
#include "constants/constants.h"

class SnakeTest : public ::testing::Test
{
protected:
    Snake snake_test;
    Position start_position{10,10};
    constants::Direction start_direction = constants::Direction::RIGHT;
    UShort start_length = 3;
    UShort max_length = 10;
    void SetUp() override
    {
        snake_test = Snake(start_position, start_direction, start_length, max_length);
    }
};

using namespace testing;

TEST_F(SnakeTest, SnakeInit)
{
    SnakeComplete snake = snake_test.get_snake();
    EXPECT_EQ(snake.size(), 10);
    Position position = start_position;

    Position empty{ 0,0 };
    EXPECT_EQ(snake[3].position, empty);

    for (UShort i = 0; i < start_length; ++i)
    {
        EXPECT_EQ(snake[i].direction, start_direction);
        EXPECT_EQ(snake[i].position, position);
        position.second -= 1;
    }
}

TEST_F(SnakeTest, SnakeMoveStraight)
{
    snake_test.move();
    SnakeComplete snake = snake_test.get_snake();
    Position position = start_position;
    position.second += 1;
    for (UShort i = 0; i < start_length; ++i)
    {
        EXPECT_EQ(snake[i].direction, start_direction);
        EXPECT_EQ(snake[i].position, position);
        position.second -= 1;
    }
}
