//
// Created by 启翔 张 on 2017/12/27.
//
#include <iostream>
#include "gtest/gtest.h"
#include "util/random.hpp"

TEST(TEST_RANDOM,base){


    EXPECT_NE(Donkey::random::uniform(), Donkey::random::uniform());

    EXPECT_GE(Donkey::random::uniform(1, 10), 1);
    EXPECT_LE(Donkey::random::uniform(1, 10), 10);
    EXPECT_NE(Donkey::random::uniform(1, 1000), Donkey::random::uniform(1, 1000));
    EXPECT_LT(Donkey::random::uniform(1, 10), Donkey::random::uniform(11, 20));
    EXPECT_EQ(Donkey::random::uniform(1, 1), 1);


    EXPECT_LT(Donkey::random::normal(0, 1), 100);
    EXPECT_GT(Donkey::random::normal(0, 1), -100);
    EXPECT_NE(Donkey::random::normal(0, 1), Donkey::random::normal(0, 1));



    EXPECT_EQ(Donkey::random::random_string(15).length(), 15);
    EXPECT_NE(Donkey::random::random_string(15), Donkey::random::random_string(15));
}