/*******************************************************
 *  test_random
 *  My Website           https://zhangqixiang.cn
 *  My Github            https://github.com/hmjmf
 *  Email                zqx5449@gmail.com
 * 
 *  Created by 启翔 张 (QiXiang Zhang) on 2018/3/26.
 *  Copyright (c) 2018 . All rights reserved.
 *******************************************************/


#include <iostream>
#include "gtest/gtest.h"
#include "util/random.hpp"

TEST(random,base){


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

  std::vector<int> v;
  int arr[100];
  for (int i = 0; i < 100; i++){
    v.emplace_back(i);
    arr[i] = i;
  }
  Donkey::random::shuffle(v);
  Donkey::random::shuffle(v.begin() + 20, v.end() - 20);
  Donkey::random::shuffle(arr, sizeof(arr) / sizeof(int));

  int diff_num_vector = 0;
  int diff_num_arr = 0;
  for (int i = 0; i < 100; i++){
    diff_num_vector += (v[i] != i);
    diff_num_arr += (arr[i] != i);
  }
  EXPECT_GT(diff_num_vector,50);
  EXPECT_GT(diff_num_arr,50);

}