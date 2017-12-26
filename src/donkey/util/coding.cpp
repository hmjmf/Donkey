//
// Created by 启翔 张 on 2017/12/26.
//
#include "util/coding.hpp"
namespace Donkey{

std::string uint32_2_hexstr(uint32 const src){

}
uint32 hexstr_2_uint32(std::string const src){
    if(src.substr(0,2) != "0x"){
        src = "0x" + src;
    }

}


}