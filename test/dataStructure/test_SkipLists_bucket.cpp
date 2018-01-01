//
// Created by zqx on 18-1-1.
//

#include <iostream>
#include "gtest/gtest.h"
#include <vector>
#include <string>
#include <thread>
#include <future>
#include <time.h>
#include "util/range.hpp"
#include "dataStructure/SkipList_bucket.h"

TEST(TEST_SKIPLSTS_BUCKET, base){
    std::vector<int> bucket = {-50,0,50};
    auto sl = Donkey::SkipList_bucket<int>::create(bucket);
    sl -> insert(1);
    sl -> insert(0);
    sl -> insert(-100);
    sl -> insert(100);

    EXPECT_EQ(sl->contains(1), true);
    EXPECT_EQ(sl->contains(110), false);
    EXPECT_EQ(sl->contains(0), true);
    EXPECT_EQ(sl->contains(100), true);
    EXPECT_EQ(sl->contains(15), false);
    EXPECT_EQ(sl->contains(-100), true);
    EXPECT_EQ(sl->contains(-1), false);

    std::vector<std::string> bucket_str = {"b" ,"e" ,"f"};
    auto sl_str = Donkey::SkipList_bucket<std::string>::create(bucket_str);
    sl_str -> insert("a");
    sl_str -> insert("g");
    sl_str -> insert("c");
    sl_str -> insert("e");

    EXPECT_EQ(sl_str->contains("1"), true);
    EXPECT_EQ(sl_str->contains("110"), false);
    EXPECT_EQ(sl_str->contains("0"), true);
    EXPECT_EQ(sl_str->contains("100"), true);
    EXPECT_EQ(sl_str->contains("15"), false);
    EXPECT_EQ(sl_str->contains("-100"), true);
    EXPECT_EQ(sl_str->contains("-1"), false);
}