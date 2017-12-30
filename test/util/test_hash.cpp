//
// Created by 启翔 张 on 2017/12/26.
//

#include <iostream>
#include "gtest/gtest.h"
#include "util/hash.hpp"

TEST(HASH_MD5,base){
    EXPECT_EQ(Donkey::hash_to_string("TESTMD5"),Donkey::hash_to_string("TESTMD5"));
    EXPECT_EQ(Donkey::hash_to_uint("TESTMD5"), Donkey::hash_to_uint("TESTMD5"));
    EXPECT_NE(Donkey::hash_to_string("TESTMD5"),"");
    EXPECT_EQ(Donkey::hash_to_string("TESTMD5").length(),32);
}
TEST(HASH_MD5,chinese){
    EXPECT_EQ(Donkey::hash_to_string("中文测试"),Donkey::hash_to_string("中文测试"));
    EXPECT_NE(Donkey::hash_to_string("中文测试"),"");
    EXPECT_EQ(Donkey::hash_to_uint("中文测试"), Donkey::hash_to_uint("中文测试"));
    EXPECT_NE(Donkey::hash_to_uint("中文测试"), 0);
    EXPECT_EQ(Donkey::hash_to_string("中文测试").length(),32);
}
TEST(HASH_MD5,empty){
    EXPECT_EQ(Donkey::hash_to_string(""),"");
}
TEST(HASH_MD5,long_string){
    std::string base_string = "this is a base string";
    std::string long_string = "";
    for(int i = 0; i < 100; i++){
        long_string += base_string;
    }
    EXPECT_EQ(long_string.length() ,base_string.length() * 100);
    EXPECT_NE(Donkey::hash_to_string(long_string),"");
    EXPECT_NE(Donkey::hash_to_uint(long_string), 0);
}

