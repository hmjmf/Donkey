//
// Created by 启翔 张 on 2017/12/26.
//

#include <iostream>
#include "gtest/gtest.h"

#include "dataStructure/BloomFilter.hpp"



TEST(TEST_BLOOM,base){

    auto b =  Donkey::BloomFilter::create(1024, 6);

    b->addKey("1234");
    b->addKey("2345");
    b->addKey("3456789");
    b->addKey("aweas");
    b->addKey("ccstg");

    EXPECT_EQ(b->keyMayMatch("1234"), true);
    EXPECT_EQ(b->keyMayMatch("2345"), true);
    EXPECT_EQ(b->keyMayMatch("ccstg"), true);

    EXPECT_EQ(b->keyMayMatch("cggg"), false);
    EXPECT_EQ(b->keyMayMatch("cddd"), false);
    EXPECT_EQ(b->keyMayMatch(""), false);
}

void addKey(std::string str, std::shared_ptr<Donkey::BloomFilter> bloom){
    bloom -> addKey(str);
}


TEST(TEST_BLOOM,multithreading){

    auto b =  Donkey::BloomFilter::create(1024, 6);


    b->addKey("1234");
    b->addKey("2345");
    b->addKey("3456789");
    b->addKey("aweas");
    b->addKey("ccstg");

    EXPECT_EQ(b->keyMayMatch("1234"), true);
    EXPECT_EQ(b->keyMayMatch("2345"), true);
    EXPECT_EQ(b->keyMayMatch("ccstg"), true);

    EXPECT_EQ(b->keyMayMatch("cggg"), false);
    EXPECT_EQ(b->keyMayMatch("cddd"), false);
    EXPECT_EQ(b->keyMayMatch(""), false);
}

