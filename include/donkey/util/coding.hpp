/*******************************************************
 *  coding
 *  My Website           https://zhangqixiang.cn
 *  My Github            https://github.com/hmjmf
 *  Email                zqx5449@gmail.com
 * 
 *  Created by 启翔 张 (QiXiang Zhang) on 2018/3/26.
 *  Copyright (c) 2018 . All rights reserved.
 *******************************************************/



#ifndef PROJECT_CODING_HPP
#define PROJECT_CODING_HPP

#include <iostream>
#include <sstream>

using namespace std;

namespace Donkey{
namespace coding{

template <typename out_t, typename in_t>
out_t convert_to(const in_t& input){
  stringstream ss;
  out_t out;
  ss << input;
  ss >> out;
  return out;
}

template <typename out_t, typename in_t>
void convert_to(const in_t& input, out_t& out){
  stringstream ss;
  ss << input;
  ss >> out;
}

template <typename in_t>
string to_str(const in_t& input){
  return convert_to<string>(input);
}

template <typename in_t>
void to_str(const in_t& input, string& out){
  convert_to<string, in_t>(input, out);
}

template <typename in_t>
int to_int(const in_t& input){
  return convert_to<int>(input);
}

template <typename in_t>
double to_double(const in_t& input){
  return convert_to<double>(input);
}


string uint_to_hex_str(unsigned int num);


}
}


#endif //PROJECT_CODING_HPP
