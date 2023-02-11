#include "read.h"
#include "gtest/gtest.h"

TEST(Read, ReadTable) {
    auto result = Read::readTable("input.txt", ' ', '\n');
    std::cout << std::endl;
    for (const auto& line : result) {
        for (const auto& value : line) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }
//    EXPECT_EQ(result[0][0], ".data\r");
//    EXPECT_EQ(result[1][0], "x00");
//    EXPECT_EQ(result[1][1], "-1");
//    EXPECT_EQ(result[1][2], "// для инверсии знака\r");
//    EXPECT_EQ(result.back().back(), "end\r");
}

