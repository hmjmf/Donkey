//
// Created by 启翔 张 on 2017/12/28.
//

#include <iostream>
#include "gtest/gtest.h"
#include <vector>
#include <string>
#include <thread>
#include <future>
#include <time.h>
#include "dataStructure/SkipList.hpp"

TEST(TEST_SKIPLISTS, SkipLists_Node_base){
    Donkey::SkipList_Node<uint>* node = new Donkey::SkipList_Node<uint>(10, 12);
    for (int i = 0; i < 12 ; i++){
        Donkey::SkipList_Node<uint>* node_ = new Donkey::SkipList_Node<uint>(i, 4);
        node->set_next(i, node_);
    }
    for (int i = 0; i < 12 ; i++){
        EXPECT_EQ(node->next(i)->get_key(), i);
        EXPECT_EQ(node->next(i)->next(0), nullptr);
        EXPECT_EQ(node->next(i)->next(100), nullptr);
    }
    EXPECT_EQ(node->get_key(), 10);
}

TEST(TEST_SKIPLISTS, base){
    auto sl = Donkey::SkipList<int>::create();

    std::vector<int> v;

    for (int i = -1000; i < 1000; i++){
        v.push_back(i);
    }
    Donkey::random::shuffle<int>(v);

    for(auto i = v.begin(); i != v.begin() + (v.size() / 2); i++){
        sl->insert(*i);
    }
    for(auto i = v.begin(); i != v.begin() + (v.size() / 2); i++){
        EXPECT_EQ(sl->contains(*i), true);
    }
    for(auto i = v.begin() + (v.size() / 2) ; i != v.end(); i++){
        EXPECT_EQ(sl->contains(*i), false);
    }

}
class t{
public:
    t(int i):i(i){}
    t():i(-1000){}
    int i;
};
ENABLE_COMPARATOR(t);

bool operator==(const t& lhs,const t& rhs){
    return lhs.i == rhs.i;
}
bool operator>=(const t& lhs,const t& rhs){
    return lhs.i >= rhs.i;
}
bool operator<=(const t& lhs,const t& rhs){
    return lhs.i <= rhs.i;
}
bool operator>(const t& lhs,const t& rhs){
    return lhs.i > rhs.i;
}
bool operator<(const t& lhs,const t& rhs){
    return lhs.i < rhs.i;
}

TEST(TEST_SKIPLISTS, class_obj){
    auto sl = Donkey::SkipList<t>::create();

    std::vector<t> v;

    for (int i = -1000; i < 1000; i++){
        v.push_back(t(i));
    }
    Donkey::random::shuffle<t>(v);

    for(auto i = v.begin(); i != v.begin() + (v.size() / 2); i++){
        sl->insert(*i);
    }
    for(auto i = v.begin(); i != v.begin() + (v.size() / 2); i++){
        EXPECT_EQ(sl->contains(*i), true);
    }
    for(auto i = v.begin() + (v.size() / 2); i != v.end(); i++){
        EXPECT_EQ(sl->contains(*i), false);
    }
}

TEST(TEST_SKIPLISTS, speed){
    auto sl = Donkey::SkipList<int>::create();
    std::vector<int> v;
    int min = -10000;
    int max = 10000;

    clock_t time_SL = clock();

    for (int i = min; i <= max; i++){
        sl->insert(i);
    }
    time_SL = clock() - time_SL;


    clock_t time_v = clock();
    for (int i = min; i <= max; i++){
        v.push_back(i);
        std::sort(v.begin(),v.end());
    }
    time_v = clock() - time_v;

    EXPECT_LT(time_SL, time_v);
    //std::cout << time_SL << "   " << time_v << std::endl;

    time_SL = clock();
    for (int i = -1000; i < 1000; i++){
        EXPECT_EQ(sl->contains(Donkey::random::uniform(min,max)), true);
    }
    time_SL = clock() - time_SL;


    time_v = clock();
    for (int i = -1000; i < 1000; i++){
        int random_num = Donkey::random::uniform(min,max);
        auto res = std::find(v.begin(),v.end(),random_num);
        EXPECT_EQ(*res, random_num);
    }
    time_v = clock() - time_v;
    EXPECT_LT(time_SL, time_v);
    //std::cout << time_SL << "   " << time_v << std::endl;



    time_SL = clock();
    for (int i = -1000; i < 1000; i++){
        EXPECT_EQ(sl->contains(Donkey::random::uniform(max+1,max*2)), false);
    }
    time_SL = clock() - time_SL;


    time_v = clock();
    for (int i = -1000; i < 1000; i++){
        int random_num = Donkey::random::uniform(max+1,max*2);
        auto res = std::find(v.begin(),v.end(),random_num);
        EXPECT_NE(*res, random_num);
    }
    time_v = clock() - time_v;
    EXPECT_LT(time_SL, time_v);
    //std::cout << time_SL << "   " << time_v << std::endl;
}

template <typename Key_t >
void insert(const std::vector<int>& src, const std::shared_ptr<Donkey::SkipList<Key_t>> sl){
    for(auto i = src.begin(); i != src.end(); i++){
        sl->insert(*i);
    }
}
template <typename Key_t >
void contains(const std::vector<int>& src, std::shared_ptr<Donkey::SkipList<Key_t>> sl, std::promise<std::vector<bool>>& promiseObj){
    std::vector<bool> res;
    for(auto i = src.begin(); i != src.end(); i++){
        res.push_back(sl->contains(*i));
    }
    promiseObj.set_value(res);
}

TEST(TEST_SKIPLISTS, multithreading){
    auto sl = Donkey::SkipList<int>::create();
    int thread_num = 8;
    int one_thread_size = 1000;
    int max = 10000;
    int min = -10000;

    std::vector<std::vector<int>> int_v_v;
    for (auto i = 0; i != thread_num; i++){
        std::vector<int> int_v;
        for (int j = 0; j <= one_thread_size;j++){
            int_v.push_back(Donkey::random::uniform(min,max));
        }
        int_v_v.push_back(int_v);
    }
    std::vector<std::thread*> threads_insert;
    clock_t time_MT = clock();
    for (auto i = int_v_v.begin(); i != int_v_v.end(); i++) {
        threads_insert.push_back(new std::thread(insert<int>, std::ref(*i), sl));
    }

    for (auto i = 0; i != thread_num; i++){
        threads_insert[i]->join();
    }



    std::vector<std::promise<std::vector<bool>>> promiseObj_v;
    for (int i = 0; i < thread_num; i++){
        promiseObj_v.push_back( std::promise<std::vector<bool>>());
    }
    std::vector<std::future<std::vector<bool>>> futureObj_v;
    for (int i = 0; i < thread_num; i++){
        futureObj_v.push_back(promiseObj_v[i].get_future());
    }

    std::vector<std::thread> thread_v;
    for (int i = 0; i < thread_num; i++){
        thread_v.push_back(std::thread(contains<int>, std::ref(int_v_v[i]), sl, std::ref(promiseObj_v[i])));
    }
    std::vector<std::vector<bool>> res_v;
    for (int i = 0; i < thread_num; i++){
        res_v.push_back(futureObj_v[i].get());
    }
    for (int i = 0; i < thread_num; i++){
        thread_v[i].join();
    }

    for (int i = 0; i < thread_num; i++){
        EXPECT_EQ(res_v[i].size(), one_thread_size + 1);
        for (auto j = res_v[i].begin(); j!=res_v[i].end(); j++){
            EXPECT_EQ(*j,true);
        }
    }


    for (int i = 0; i < 100; i++){
        EXPECT_EQ(sl->contains(Donkey::random::uniform(max+1, max*2)), false);
    }
    time_MT = clock() - time_MT;

    //SING
    auto sl2 = Donkey::SkipList<int>::create();
    std::vector<int> sing_v;
    for (int i = 0; i < thread_num * one_thread_size; i++){
        sing_v.push_back(Donkey::random::uniform(min,max));
    }
    clock_t time_SG = clock();
    for (auto i = sing_v.begin(); i!=sing_v.end(); i++){
        sl2->insert(*i);
    }
    for (auto i = sing_v.begin(); i!=sing_v.end(); i++){
        EXPECT_EQ(sl2->contains(*i), true);
    }
    for (int i = 0; i < 100; i++){
        EXPECT_EQ(sl2->contains(Donkey::random::uniform(max+1, max*2)), false);
    }
    time_SG = clock() - time_SG;
//    EXPECT_LT(time_MT, time_SG);
    std::cout<< time_MT << "   " << time_SG << std::endl;
}