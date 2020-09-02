#ifndef TST_SNAKEMOVE_H
#define TST_SNAKEMOVE_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "../Snake_cpp_qt/model/snake.h"

using namespace testing;

TEST(Snake, SnakeMove)
{
    Snake snake_test;

    EXPECT_EQ(1, 1);
    ASSERT_THAT(0, Eq(0));
}

#endif // TST_SNAKEMOVE_H
