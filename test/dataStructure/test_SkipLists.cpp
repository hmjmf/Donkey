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
#include "util/range.hpp"
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

    auto sl_str = Donkey::SkipList<std::string>::create();
    sl_str -> insert("1");
    sl_str -> insert("0");
    sl_str -> insert("-100");
    sl_str -> insert("100");

    EXPECT_EQ(sl_str->contains("1"), true);
    EXPECT_EQ(sl_str->contains("110"), false);
    EXPECT_EQ(sl_str->contains("0"), true);
    EXPECT_EQ(sl_str->contains("100"), true);
    EXPECT_EQ(sl_str->contains("15"), false);
    EXPECT_EQ(sl_str->contains("-100"), true);
    EXPECT_EQ(sl_str->contains("-1"), false);
}
TEST(TEST_SKIPLISTS, iterator){
    auto sl = Donkey::SkipList<int>::create();
    sl -> insert(1);
    sl -> insert(0);
    sl -> insert(-100);
    sl -> insert(100);
    sl->insert(1);


    Donkey::SkipList<int>::iterator it(sl.get());

    it.next();
    EXPECT_EQ(it.key(),-100);
    it.next();
    EXPECT_EQ(it.key(), 0);
    it.next();
    EXPECT_EQ(it.key(), 1);
    it.next();
    EXPECT_EQ(it.key(), 100);


    it.prev();
    EXPECT_EQ(it.key(),1);
    it.next();
    EXPECT_EQ(it.key(),100);

}
TEST(TEST_SKIPLISTS, base_big){
    auto sl = Donkey::SkipList<int>::create();

    std::vector<int> v;

    for (int i = -1000; i < 1000; i++){
        v.emplace_back(i);
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
        v.emplace_back(t(i));
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
        v.emplace_back(i);
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
//    int one_thread_size = 1000;
    int max = 10000;
    int min = -10000;

    std::vector<int> all_num;
    for(auto i : Donkey::Range<int>(0, std::abs(max) + std::abs(min))){
        all_num.emplace_back(i);
    }
    Donkey::random::shuffle(all_num);

    std::vector<std::vector<int>> in_int_v_v;
    for (auto i : Donkey::Range<int>(0, thread_num)){
        in_int_v_v.emplace_back(std::vector<int>());
    }

    std::vector<std::vector<int>> not_in_int_v_v;
    for (auto i : Donkey::Range<int>(0, thread_num)){
        not_in_int_v_v.emplace_back(std::vector<int>());
    }

    int index=0;
    for(auto i = all_num.begin(); i!= (all_num.end()-all_num.begin())/2 + all_num.begin();i++,index++){
        //in
        in_int_v_v[index % thread_num].emplace_back(*i);

    }
    index=0;
    for(auto i = (all_num.end()-all_num.begin())/2 + all_num.begin(); i!= all_num.end();i++,index++){
        //not in
        not_in_int_v_v[index % thread_num].emplace_back(*i);
    }
//insert
    std::vector<std::thread*> threads_insert;
    clock_t time_MT = clock();
    for (auto i = in_int_v_v.begin(); i != in_int_v_v.end(); i++) {
        threads_insert.emplace_back(new std::thread(insert<int>, std::ref(*i), sl));
    }

    for (auto i : Donkey::Range<int>(0, thread_num)){
        threads_insert[i]->join();
    }
//contains in
    std::vector<std::promise<std::vector<bool>>> in_promiseObj_v;
    for (int i = 0; i < thread_num; i++){
        in_promiseObj_v.emplace_back( std::promise<std::vector<bool>>());
    }
    std::vector<std::future<std::vector<bool>>> in_futureObj_v;
    for (int i = 0; i < thread_num; i++){
        in_futureObj_v.emplace_back(in_promiseObj_v[i].get_future());
    }

    std::vector<std::thread> in_thread_v;
    for (int i = 0; i < thread_num; i++){
        in_thread_v.emplace_back(std::thread(contains<int>, std::ref(in_int_v_v[i]), sl, std::ref(in_promiseObj_v[i])));
    }
    std::vector<std::vector<bool>> in_res_v;
    for (int i = 0; i < thread_num; i++){
        in_res_v.emplace_back(in_futureObj_v[i].get());
    }
    for (int i = 0; i < thread_num; i++){
        in_thread_v[i].join();
    }
    int err_t = 0;
    for (int i = 0; i < thread_num; i++){
        for (auto j = in_res_v[i].begin(); j!=in_res_v[i].end(); j++){
            err_t += !(*j);
        }
    }

    EXPECT_EQ(err_t ,0);
//contains not in
    std::vector<std::promise<std::vector<bool>>> not_in_promiseObj_v;
    for (int i = 0; i < thread_num; i++){
        not_in_promiseObj_v.emplace_back( std::promise<std::vector<bool>>());
    }
    std::vector<std::future<std::vector<bool>>> not_in_futureObj_v;
    for (int i = 0; i < thread_num; i++){
        not_in_futureObj_v.emplace_back(not_in_promiseObj_v[i].get_future());
    }

    std::vector<std::thread> not_in_thread_v;
    for (int i = 0; i < thread_num; i++){
        not_in_thread_v.emplace_back(std::thread(contains<int>, std::ref(not_in_int_v_v[i]), sl, std::ref(not_in_promiseObj_v[i])));
    }
    std::vector<std::vector<bool>> not_in_res_v;
    for (int i = 0; i < thread_num; i++){
        not_in_res_v.emplace_back(not_in_futureObj_v[i].get());
    }
    for (int i = 0; i < thread_num; i++){
        not_in_thread_v[i].join();
    }
    err_t = 0;
    for (int i = 0; i < thread_num; i++){
        for (auto j = not_in_res_v[i].begin(); j!=not_in_res_v[i].end(); j++){
            err_t += (*j);
        }
    }
    EXPECT_EQ(err_t ,0);
    time_MT = clock() - time_MT;

    auto sl_SG = Donkey::SkipList<int>::create();
    clock_t time_SG = clock();

    for(auto i = all_num.begin(); i!= (all_num.end()-all_num.begin())/2 + all_num.begin();i++){
        sl_SG->insert(*i);
    }
    for(auto i = all_num.begin(); i!= (all_num.end()-all_num.begin())/2 + all_num.begin();i++){
        sl_SG->contains(*i);
    }
    for(auto i = (all_num.end()-all_num.begin())/2 + all_num.begin(); i!= all_num.end();i++){
        sl_SG->contains(*i);
    }
    time_SG = clock() - time_SG;
    //EXPECT_LT(time_MT, time_SG)<< time_MT << "   " << time_SG;
}
