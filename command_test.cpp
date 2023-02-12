#include "command.h"
#include "gtest/gtest.h"

TEST(Command, mov) {
    int lhs = 3;
    int rhs = 10;
    Command<32>::mov(lhs, rhs);
    EXPECT_EQ(lhs, 10);
    EXPECT_EQ(rhs, 10);
}

TEST(Command, add) {
    int lhs = 0;
    int rhs = 0;
    Command<32>::add(lhs, rhs);
    EXPECT_EQ(lhs, 0);

    lhs = 1;
    rhs = 0;
    Command<32>::add(lhs, rhs);
    EXPECT_EQ(lhs, 1);

    lhs = 1;
    rhs = 1;
    Command<32>::add(lhs, rhs);
    EXPECT_EQ(lhs, 2);

    lhs = -1;
    rhs = 1;
    Command<32>::add(lhs, rhs);
    EXPECT_EQ(lhs, 0);

    lhs = -1;
    rhs = 0;
    Command<32>::add(lhs, rhs);
    EXPECT_EQ(lhs, -1);

    lhs = -1;
    rhs = -1;
    Command<32>::add(lhs, rhs);
    EXPECT_EQ(lhs, -2);

    lhs = -1;
    rhs = 2;
    Command<32>::add(lhs, rhs);
    EXPECT_EQ(lhs, 1);

    lhs = -1;
    rhs = -9;
    Command<32>::add(lhs, rhs);
    EXPECT_EQ(lhs, -10);

    lhs = 12321;
    rhs = 432432;
    Command<32>::add(lhs, rhs);
    EXPECT_EQ(lhs, 12321 + 432432);

    lhs = (1 << 31);
    rhs = 0;
    Command<32>::add(lhs, rhs);
    EXPECT_EQ(lhs, (1 << 31));

    lhs = (1 << 31);
    rhs = 16;
    Command<32>::add(lhs, rhs);
    EXPECT_EQ(lhs, (1 << 31) + 16);

    lhs = -12321;
    rhs = -432432;
    Command<32>::add(lhs, rhs);
    EXPECT_EQ(lhs, -12321 - 432432);
}

TEST(Command, mul) {
    int lhs = 0;
    int rhs = 0;
    Command<32>::mul(lhs, rhs);
    EXPECT_EQ(lhs, 0);

    lhs = 1;
    rhs = 0;
    Command<32>::mul(lhs, rhs);
    EXPECT_EQ(lhs, 0);

    lhs = 1;
    rhs = 1;
    Command<32>::mul(lhs, rhs);
    EXPECT_EQ(lhs, 1);

    lhs = 1;
    rhs = 2;
    Command<32>::mul(lhs, rhs);
    EXPECT_EQ(lhs, 2);

    lhs = 5;
    rhs = 7;
    Command<32>::mul(lhs, rhs);
    EXPECT_EQ(lhs, 35);

    lhs = 1123;
    rhs = 2131;
    Command<32>::mul(lhs, rhs);
    EXPECT_EQ(lhs, 2131 * 1123);
}

TEST(Command, MulThrow) {
    int lhs = 112306;
    int rhs = 213106;
    EXPECT_ANY_THROW(Command<32>::mul(lhs, rhs));
}