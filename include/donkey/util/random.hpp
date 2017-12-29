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

namespace Donkey{
namespace random{


DONKEY_EXPORT int uniform(int min = -RAND_MAX, int max = RAND_MAX);
DONKEY_EXPORT double normal(int m = 0, int s = 1);

template <typename type>
DONKEY_EXPORT void shuffle(std::vector<type>& input,
                           typename std::vector<type>::iterator begin,
                           typename std::vector<type>::iterator end){
    size_t size = end - begin;
    if (size <= 1) return;
    for(int i = 0; i < size; i++){
        std::swap(*(begin + i),*(begin + uniform(0, size - 1)));
    }
}

template <typename type>
DONKEY_EXPORT void shuffle(std::vector<type>& input){
    shuffle<type>(input, input.begin(), input.end());
}


template <typename type>
DONKEY_EXPORT void shuffle(type* input, size_t size){
    if (size <= 1) return;
    for(int i = 0; i < size; i++){
        std::swap(input[i],input[uniform(0, size - 1)]);
    }
}


DONKEY_EXPORT std::string random_string(const uint length, bool lower = true,
                                        bool caps = true, bool num = true,
                                        bool special = false);


}
}


#endif //PROJECT_RANDOM_HPP
