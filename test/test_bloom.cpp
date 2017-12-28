//
// Created by 启翔 张 on 2017/12/26.
//

#include <iostream>
#include "gtest/gtest.h"
#include <vector>
#include <string>
#include <thread>
#include "util/random.hpp"
#include "dataStructure/BloomFilter.hpp"



TEST(TEST_BLOOM,base){

    auto b =  Donkey::BloomFilter::create(102400, 6);

    std::vector<std::string> strs_in_bloom;
    std::vector<std::string> strs_not_in_bloom;

    for (int i = 0; i < 1024; i++){
        strs_in_bloom.push_back(Donkey::random::random_string(Donkey::random::uniform(10,50),true,true,true,true));
        strs_not_in_bloom.push_back(Donkey::random::random_string(Donkey::random::uniform(10,50),true,true,true,true));
    }
    for (std::vector<std::string>::const_iterator i = strs_in_bloom.begin(); i != strs_in_bloom.end(); i++){
        b->addKey(*i);
    }
    for (std::vector<std::string>::const_iterator i = strs_in_bloom.begin(); i != strs_in_bloom.end(); i++){
        EXPECT_EQ(b->keyMayMatch(*i), true); //in
    }
    for (std::vector<std::string>::const_iterator i = strs_not_in_bloom.begin(); i != strs_not_in_bloom.end(); i++){
        EXPECT_EQ(b->keyMayMatch(*i), false); //not in
    }

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

