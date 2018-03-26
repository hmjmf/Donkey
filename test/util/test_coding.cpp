/*******************************************************
 *  test_coding
 *  My Website           https://zhangqixiang.cn
 *  My Github            https://github.com/hmjmf
 *  Email                zqx5449@gmail.com
 * 
 *  Created by 启翔 张 (QiXiang Zhang) on 2018/3/26.
 *  Copyright (c) 2018 . All rights reserved.
 *******************************************************/

#include <iostream>
#include "gtest/gtest.h"
#include "util/coding.hpp"

TEST(coding, base){
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

  EXPECT_EQ(Donkey::coding::uint_to_hex_str(156), "9c");

}

