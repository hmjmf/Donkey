/*******************************************************
 *  random
 *  My Website           https://zhangqixiang.cn
 *  My Github            https://github.com/hmjmf
 *  Email                zqx5449@gmail.com
 * 
 *  Created by 启翔 张 (QiXiang Zhang) on 2018/3/26.
 *  Copyright (c) 2018 . All rights reserved.
 *******************************************************/



#ifndef PROJECT_RANDOM_HPP
#define PROJECT_RANDOM_HPP

#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <random>

using namespace std;

namespace Donkey{
namespace random{


int uniform(const int min = -RAND_MAX, const int max = RAND_MAX);

double normal(const int m = 0, const int s = 1);

//return a random string
std::string random_string(const uint length, bool lower = true,
                          bool caps = true, bool num = true,
                          bool special = false);

//shuffle a vector or other
template <typename iterator_t>
void shuffle(iterator_t begin, iterator_t end){
  size_t size = end - begin;
  if (size <= 1) return;
  for(int i = 0; i < size; i++){
    std::swap(*(begin + i),*(begin + uniform(0, size - 1)));
  }
}

//shuffle<type>(input.begin(), input.end());
template <typename T>
void shuffle(T& input){
  shuffle(input.begin(), input.end());
}

//for array
template <typename type>
void shuffle(type* input, size_t size){
  if (size <= 1) return;
  for(int i = 0; i < size; i++){
    std::swap(input[i],input[uniform(0, size - 1)]);
  }
}


}
}



#endif //PROJECT_RANDOM_HPP
