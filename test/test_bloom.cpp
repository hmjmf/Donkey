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

void addKey(const std::vector<std::string>& strs, const std::shared_ptr<Donkey::BloomFilter> bloom){
    for (auto i = strs.begin(); i != strs.end(); i++){
        bloom -> addKey(*i);
    }
}


TEST(TEST_BLOOM,multithreading){

    auto b =  Donkey::BloomFilter::create(204800, 6);

    std::vector<std::vector<std::string>> strs_in_bloom_vector;
    std::vector<std::string> strs_not_in_bloom;

    for (int i = 0; i < 5; i++) {
        std::vector<std::string> strs_in_bloom;
        for (int j = 0; j < 1024; j++) {
            strs_in_bloom.push_back(
                    Donkey::random::random_string(Donkey::random::uniform(10, 50), true, true, true, true));
            strs_not_in_bloom.push_back(
                    Donkey::random::random_string(Donkey::random::uniform(10, 50), true, true, true, true));
        }
        strs_in_bloom_vector.push_back(strs_in_bloom);
    }

    std::vector<std::thread*> threads;
    for (auto i = strs_in_bloom_vector.begin(); i != strs_in_bloom_vector.end(); i++) {
        threads.push_back(new std::thread(addKey, std::ref(*i), b));
    }

    for (auto i = threads.begin(); i != threads.end(); i++){
        (*i)->join();
    }

    for (auto i = strs_in_bloom_vector.begin(); i != strs_in_bloom_vector.end(); i++) {
        for (auto j = i -> begin(); j != i -> end(); j++){
            EXPECT_EQ(b->keyMayMatch(*j), true);
        }

    }
    for (std::vector<std::string>::const_iterator i = strs_not_in_bloom.begin(); i != strs_not_in_bloom.end(); i++){
        EXPECT_EQ(b->keyMayMatch(*i), false); //not in
    }

    for (auto i = threads.begin(); i != threads.end(); i++){
        delete *i;
    }
}

