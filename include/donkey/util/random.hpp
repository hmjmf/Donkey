//
// Created by 启翔 张 on 2017/12/27.
//

#ifndef PROJECT_RANDOM_HPP
#define PROJECT_RANDOM_HPP

#include <time.h>
#include <stdlib.h>
#include <Donkey.hpp>
#include <random>
#include "glog/logging.h"
#include "range.hpp"

namespace Donkey{
namespace random{


DONKEY_EXPORT int uniform(int min = -RAND_MAX, int max = RAND_MAX);
DONKEY_EXPORT double normal(int m = 0, int s = 1);

template <typename type>
DONKEY_EXPORT void shuffle(typename std::vector<type>::iterator begin,
                           typename std::vector<type>::iterator end){
    size_t size = end - begin;
    if (size <= 1) return;
    for(int i = 0; i < size; i++){
        std::swap(*(begin + i),*(begin + uniform(0, size - 1)));
    }
}

template <typename type>
DONKEY_EXPORT void shuffle(std::vector<type>& input){
    shuffle<type>(input.begin(), input.end());
}


template <typename type>
DONKEY_EXPORT void shuffle(type* input, size_t size){
    if (size <= 1) return;
    for(int i = 0; i < size; i++){
        std::swap(input[i],input[uniform(0, size - 1)]);
    }
}
template <typename type>
DONKEY_EXPORT std::vector<type>& random_chose(typename std::vector<type>::iterator begin,
                                             typename std::vector<type>::iterator end,
                                             uint choose_num){
    using std::max;
    choose_num = std::min<uint>(choose_num, end - begin);
    std::vector<type>* res = new std::vector<type>();
    std::vector<uint> index;
    for (auto x : Range<uint>(0,end - begin)){
        index.emplace_back(x);
    }
    shuffle<uint>(index);
    for (auto x : Range<uint>(0, choose_num)){
        res->emplace_back(*(begin + index[x]));
    }

    return *res;
}

DONKEY_EXPORT std::string random_string(const uint length, bool lower = true,
                                        bool caps = true, bool num = true,
                                        bool special = false);


}
}


#endif //PROJECT_RANDOM_HPP
