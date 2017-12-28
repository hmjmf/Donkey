//
// Created by 启翔 张 on 2017/12/26.
//
#ifndef PROJECT_CODING_HPP
#define PROJECT_CODING_HPP

#include <sstream>
#include "Donkey.hpp"

namespace Donkey{
namespace coding{
template <typename __out_type__, typename __in_type__>
DONKEY_EXPORT __out_type__ convert_to(__in_type__ input){
    std::stringstream ss;
    __out_type__ out;
    ss << input;
    ss >> out;
    return out;
}

template <typename __type__>
DONKEY_EXPORT std::string to_str(__type__ input){
    return convert_to<std::string>(input);
}

template <typename __type__>
DONKEY_EXPORT int to_int(__type__ input){
    return convert_to<int>(input);
}

template <typename __type__>
DONKEY_EXPORT double to_double(__type__ input){
    return convert_to<double>(input);
}





std::string uint_to_hex_str(unsigned int num);


}
}

#endif //PROJECT_CODING_HPP