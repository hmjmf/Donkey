//
// Created by 启翔 张 on 2017/12/26.
//

#include <iostream>
#include "gtest/gtest.h"
#include "util/hash.hpp"



TEST(HASH_MD5,base){
    EXPECT_EQ(Donkey::hash("TESTMD5"),"ae05741a93699a5c4d7bb1744aa9a1b0");
}
TEST(HASH_MD5,chinese){
    EXPECT_EQ(Donkey::hash("中文测试"),"089b4943ea034acfa445d050c7913e55");
}
TEST(HASH_MD5,empty){
    EXPECT_EQ(Donkey::hash(""),"");
}
TEST(HASH_MD5,LONG_STRING){
    std::string base_string = "this is a base string";
    std::string long_string = "";
    for(int i = 0; i < 100; i++){
        long_string += base_string;
    }
    EXPECT_EQ(long_string.length() ,base_string.length() * 100);
    EXPECT_NE(Donkey::hash(long_string),"");
}

