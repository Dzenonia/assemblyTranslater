#include "read.h"
#include "gtest/gtest.h"

TEST(Read, ReadTable) {
    auto result = Read::readTable("input.txt", '\n');
    EXPECT_EQ(result[0][0], ".data");
    EXPECT_EQ(result[1][0], "x00");
    EXPECT_EQ(result.back().back(), "end");
}

TEST(Read, ReadLines) {
    auto result = Read::readLines("input.txt", '\n');
    EXPECT_EQ(result[0], ".data\r");
    EXPECT_EQ(result[1], "x00  -1  // для инверсии знака\r");
    EXPECT_EQ(result.back(), "end");
}

