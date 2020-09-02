#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "model/snake.h"
#include "constants/constants.h"

/**
 * Fixture class to create Snake objects.
 */
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

/**
 * Tests if the constructor works as intended.
 */
TEST_F(SnakeTest, SnakeInit)
{
    const SnakeComplete& snake = snake_test.get_snake();
    EXPECT_EQ(snake.size(), 10);
    Position position = start_position;

    Position empty{ 0,0 };
    EXPECT_EQ(snake[3].position, empty);

    for (UShort i = 0; i < start_length; ++i)
    {
        EXPECT_EQ(snake[i].direction, start_direction);
        EXPECT_EQ(snake[i].position, position);
        --position.second;
    }
}

/**
 * Tests if the Snake can move in a straight line
 * and in the right direction.
 */
TEST_F(SnakeTest, SnakeMoveStraight)
{
    snake_test.move();
    const SnakeComplete& snake = snake_test.get_snake();
    Position position = start_position;
    ++position.second;
    for (UShort i = 0; i < start_length; ++i)
    {
        EXPECT_EQ(snake[i].direction, start_direction);
        EXPECT_EQ(snake[i].position, position);
        --position.second;
    }
}

/**
 * Tests if the Snake can make a curve
 * in the intended direction.
 */
TEST_F(SnakeTest, SnakeMoveCurve)
{
    Position position = start_position;

    snake_test.set_front_direction(constants::Direction::UP);
    const SnakeComplete& snake = snake_test.get_snake();

    EXPECT_EQ(snake.front().direction, constants::Direction::UP);
    EXPECT_EQ(snake[0].position, start_position);

    snake_test.move();

    --position.first;
    EXPECT_EQ(snake[0].position, position);

    EXPECT_EQ(snake[1].position, start_position);

    position = start_position;
    --position.second;
    EXPECT_EQ(snake[2].position, position);

}
