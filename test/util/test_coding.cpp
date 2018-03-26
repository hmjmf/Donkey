//
// Created by 启翔 张 on 2017/12/26.
//

#include <iostream>
#include "gtest/gtest.h"
#include "util/coding.hpp"

TEST(TEST_CODING,base){
  std::string str = "";
  EXPECT_EQ(Donkey::coding::to_str(11), "11");
  EXPECT_EQ(Donkey::coding::to_str(11.11), "11.11");
  Donkey::coding::to_str(11, str);
  EXPECT_EQ(str, "11");
  Donkey::coding::to_str(11.11, str);
  EXPECT_EQ(str, "11.11");

  EXPECT_EQ(Donkey::coding::to_int("11"), 11);
  EXPECT_EQ(Donkey::coding::to_int("11.11"), 11);


  EXPECT_DOUBLE_EQ(Donkey::coding::to_int("11"), 11.0);
  EXPECT_DOUBLE_EQ(Donkey::coding::to_double("11.11"), 11.11);


  EXPECT_EQ(Donkey::coding::convert_to<int>("11.11"), 11);
  EXPECT_EQ(Donkey::coding::convert_to<std::string>(11), "11");

  Donkey::coding::convert_to<std::string>(12.12, str);
  EXPECT_EQ(str, "12.12");
}