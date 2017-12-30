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

    std::vector<int> v;
    int arr[100];
    for (int i = 0; i < 100; i++){
        v.emplace_back(i);
        arr[i] = i;
    }
    Donkey::random::shuffle<int>(v);
    Donkey::random::shuffle<int>(v.begin() + 20, v.end() - 20);
    Donkey::random::shuffle<int>(arr, sizeof(arr) / sizeof(int));

    int diff_num_vector = 0;
    int diff_num_arr = 0;
    for (int i = 0; i < 100; i++){
        diff_num_vector += (v[i] != i);
        diff_num_arr += (arr[i] != i);
    }
    EXPECT_GT(diff_num_vector,50);
    EXPECT_GT(diff_num_arr,50);

    std::vector<int> v2;
    for (int i = 0; i < 100; i++){
        v2.emplace_back(i);
    }
    std::vector<int> choose1 = Donkey::random::random_chose<int>(v2.begin(),v2.end(),10);
    std::vector<int> choose2 = Donkey::random::random_chose<int>(v2.begin(),v2.end(),10);
    EXPECT_EQ(choose1.size(), 10);

    int diff = 0;
    for(auto i: Donkey::Range<int>(0,10)){
        diff += (choose1[i] != choose2[i]);
    }
    EXPECT_GT(diff, 5);


}