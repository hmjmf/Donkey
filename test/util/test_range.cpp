/*******************************************************
 *  test_range
 *  My Website           https://zhangqixiang.cn
 *  My Github            https://github.com/hmjmf
 *  Email                zqx5449@gmail.com
 * 
 *  Created by 启翔 张 (QiXiang Zhang) on 2018/3/26.
 *  Copyright (c) 2018 . All rights reserved.
 *******************************************************/


#include <iostream>
#include "gtest/gtest.h"
#include "util/range.hpp"

TEST(range, base){
  int i = 1;
  for (auto x: Donkey::range(1, 5)) {
    EXPECT_EQ(x, i);
    i++;
  }

  i = 1;
  for (auto x: Donkey::range(1, 10, 2)) {
    EXPECT_EQ(x, i);
    i += 2;
  }

  i = 10;
  for (auto x: Donkey::range(10, 1, -1)) {
    EXPECT_EQ(x, i);
    i += -1;
  }

  i = 0;
  for (auto x: Donkey::range(10)) {
    EXPECT_EQ(x, i);
    i += 1;
  }

  float f = 1.5;
  for (auto x: Donkey::range(1.5, 10.5)) {
    EXPECT_EQ(x, f);
    f += 1;
  }

  f = 1;
  for (auto x: Donkey::range(1.0, 10.5, 0.5)) {
    EXPECT_EQ(x, f);
    f += 0.5;
  }

  f = 10.5;
  for (auto x: Donkey::range(10.5, 1.0, -0.5)) {
    EXPECT_EQ(x, f);
    f -= 0.5;
  }

  char c = 'a';
  for (auto x: Donkey::range('a', 'z', 1)) {
    EXPECT_EQ(x, c);
    c += 1;
  }
}
