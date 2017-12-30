//
// Created by 启翔 张 on 2017/12/28.
//
#include<iostream>    //std::cout std::endl
#include<thread>      //std::thread
#include<future>      //std::future std::promise
#include<utility>     //std::ref
#include<chrono>      //std::chrono::seconds
#include<vector>
#include <sstream>


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
int to_int(const in_t& input){
    return convert_to<int>(input);
}

template <typename in_t>
double to_double(const in_t& input){
    return convert_to<double>(input);
}


std::string& to_str_t(const int& input){
    std::stringstream ss;
    std::string out;
    ss << input;
    ss >> out;
    return out;
}
int main(){
    std::cout <<  to_str(11) <<std::endl;


    return 0;
}