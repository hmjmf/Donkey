/*******************************************************
 *  random
 *  My Website           https://zhangqixiang.cn
 *  My Github            https://github.com/hmjmf
 *  Email                zqx5449@gmail.com
 * 
 *  Created by 启翔 张 (QiXiang Zhang) on 2018/3/26.
 *  Copyright (c) 2018 . All rights reserved.
 *******************************************************/



#include "util/random.hpp"

namespace Donkey{
namespace random{
  mt19937 gen(time(NULL));
  const string lower_s = "abcdefghijklmnopqrstuvwxyz";
  const string caps_s = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  const string num_s = "1234567890";
  const string special_s = "!@#$%^&*()_+=-[]{}|;:.,<>/?";


  int uniform(const int min, const int max ){
    if (min > max){
      logic_error("min must <= max");
    }
    uniform_int_distribution<int> distr(min, max);
    return distr(gen);
  }
  double normal(const int m, const int s){
    normal_distribution<double> distr(m, s);
    return distr(gen);
  }


  string random_string(const uint length, const bool lower,
                       const bool caps , const bool num,
                       const bool special){
    if (lower || caps || num || special){
      logic_error("random_string(lower || caps || num || special)is false");
    }


    string str = "";
    if (lower) str += lower_s;
    if (caps) str += caps_s;
    if (num) str += num_s;
    if (special) str += special_s;

    string res = "";
    for (int i = 0; i < length; i++){
      res += str[uniform(0, str.length() - 1)];
    }
    return res;
  }


}
}