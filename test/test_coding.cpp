//
// Created by 启翔 张 on 2017/12/26.
//

#include <iostream>
#include "gtest/gtest.h"
#include "util/coding.hpp"

TEST(TEST_CODING,base){
    int d;

    std::string salary;

    std::string s="12";
    std::stringstream stream;
    stream << s;
    stream >> d;
    EXPECT_EQ(d,12);

}