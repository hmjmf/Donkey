//
// Created by 启翔 张 on 2017/12/27.
//

#include "util/random.hpp"

namespace Donkey{
namespace random{
std::mt19937 gen(time(NULL));
std::string lower_s = "abcdefghijklmnopqrstuvwxyz";
std::string caps_s = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
std::string num_s = "1234567890";
std::string special_s = "!@#$%^&*()_+=-[]{}|;:.,<>/?";


int uniform(int min, int max ){
  CHECK_LE(min, max) << "min > max";
  std::uniform_int_distribution<int> distr(min, max);
  return distr(gen);
}
double normal(int m, int s){
  std::normal_distribution<double> distr(m, s);
  return distr(gen);
}


std::string random_string(const uint length, bool lower,
                    bool caps , bool num,
                    bool special){
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