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
    EXPECT_EQ(snake_test.get_length(), start_length);
    const SnakeVec& snake = snake_test.get_snake();
    EXPECT_EQ(snake.size(), 10);
    Position position = start_position;

    Position empty{ 0,0 };
    EXPECT_EQ(snake[3].get_position(), empty);

    for (UShort i = 0; i < start_length; ++i)
    {
        EXPECT_EQ(snake[i].get_direction(), start_direction);
        EXPECT_EQ(snake[i].get_position(), position);
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
    const SnakeVec& snake = snake_test.get_snake();
    Position position = start_position;
    ++position.second;
    for (UShort i = 0; i < start_length; ++i)
    {
        EXPECT_EQ(snake[i].get_direction(), start_direction);
        EXPECT_EQ(snake[i].get_position(), position);
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
    const SnakeVec& snake = snake_test.get_snake();

    EXPECT_EQ(snake.front().get_direction(), constants::Direction::UP);
    EXPECT_EQ(snake[0].get_position(), start_position);

    snake_test.move();

    --position.first;
    EXPECT_EQ(snake[0].get_position(), position);

    EXPECT_EQ(snake[1].get_position(), start_position);

    position = start_position;
    --position.second;
    EXPECT_EQ(snake[2].get_position(), position);

}

/**
 * Tests if the Snake::add_part
 * adds a new SnakePart at the end of the
 * current snake depending on the direction of the
 * previous SnakePart.
 */
TEST_F(SnakeTest, SnakeAddPart)
{
    snake_test.add_part();
    const UShort& new_length = snake_test.get_length();
    EXPECT_EQ(new_length, start_length + 1);

    const SnakeVec& snake = snake_test.get_snake();

    EXPECT_EQ(snake[new_length-1].get_direction(), start_direction);

    Position prev_position = start_position;
    prev_position.second -= new_length - 1;

    EXPECT_EQ(snake[new_length-1].get_position(), prev_position);
}

/**
 * Tests if the Snake::is_occupied
 * returns false if a snake part is occupying the positon
 * and true if the position is free.
 */
TEST_F(SnakeTest, SnakeIsOccupied)
{
    Position position = start_position;

    EXPECT_EQ(snake_test.is_occupied(position), true);

    position.first = 0;
    EXPECT_EQ(snake_test.is_occupied(position), false);
}
