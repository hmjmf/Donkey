//
// Created by 启翔 张 on 2017/12/26.
//
#ifndef PROJECT_CODING_HPP
#define PROJECT_CODING_HPP

#include <sstream>
#include "Donkey.hpp"

namespace Donkey{
namespace coding{ 
    
template <typename out_t, typename in_t>
out_t convert_to(const in_t& input){
    std::stringstream ss;
    out_t out;
    ss << input;
    ss >> out;
    return out;
}

template <typename out_t, typename in_t>
void convert_to(const in_t& input, out_t& out){
    std::stringstream ss;
    ss << input;
    ss >> out;
}

template <typename in_t>
std::string to_str(const in_t& input){ 
    return convert_to<std::string>(input);
}
    
template <typename in_t>
void to_str(const in_t& input, std::string& out){
    convert_to<std::string, in_t>(input, out);
}

template <typename in_t>
DONKEY_EXPORT int to_int(const in_t& input){
    return convert_to<int>(input);
}

template <typename in_t>
DONKEY_EXPORT double to_double(const in_t& input){
    return convert_to<double>(input);
}


std::string uint_to_hex_str(unsigned int num);


}
}

#endif //PROJECT_CODING_HPP