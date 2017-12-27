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
std::mt19937 gen(time(NULL));

DONKEY_EXPORT int uniform(int min = -RAND_MAX, int max = RAND_MAX){
    CHECK_LE(min, max) << "min > max";
    std::uniform_int_distribution<int> distr(min, max);
    return distr(gen);
}
DONKEY_EXPORT double normal(int m = 0, int s = 1){
    std::normal_distribution<double> distr(m, s);
    return distr(gen);
}


std::string lower_s = "abcdefghijklmnopqrstuvwxyz";
std::string caps_s = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
std::string num_s = "1234567890";
std::string special_s = "!@#$%^&*()_+=-[]{}|;:.,<>/?";
DONKEY_EXPORT std::string random_string(const uint length, bool lower = true,
                                        bool caps = true, bool num = true,
                                        bool special = false){
    CHECK(lower || caps || num || special)
        << "random_string (lower || caps || num || special) is false";

    std::string str = "";
    if (lower) str += lower_s;
    if (caps) str += caps_s;
    if (num) str += num_s;
    if (special) str += special_s;

    std::string res = "";
    for (int i = 0; i < length; i++){
        res += str[uniform(0, str.length() - 1)];
    }
    return res;
}

}




}


#endif //PROJECT_RANDOM_HPP
