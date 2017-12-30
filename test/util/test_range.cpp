//
// Created by 启翔 张 on 2017/12/29.
//
#include <iostream>
#include "gtest/gtest.h"
#include "util/range.hpp"

TEST(TEST_RANGE,base){
    int i = 1;
    for (auto x: Donkey::Range<int>(1,5))
    {
        EXPECT_EQ(x, i);
        i++;
    }

    for (auto x: Donkey::Range<int>(5,1))
    {
        EXPECT_EQ(true, false);
    }

}
