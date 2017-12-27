//
// Created by 启翔 张 on 2017/12/27.
//

#include "dataStructure/BloomFilter.hpp"
namespace Donkey{



BloomFilter::BloomFilter(uint32_t size, uint hash_time):
    hash_time(hash_time){
    this->size = (size / (sizeof(char) * 8)) + 1;
    lookup_list = new char [this->size];
    CHECK(lookup_list != nullptr) << "BloomFilter lookup_list is null";
    memset(lookup_list, 0, this->size);
}

struct position BloomFilter::computePosition(uint32_t num){
    struct position pos;
    num %= (size * 8);
    pos.index = num / 8;
    pos.offset = num % 8;
    CHECK_LT(pos.index, size) << "pos.index too big";
    return pos;
}

std::vector<struct position> BloomFilter::computePositions(std::string key){
    std::vector<struct position> pos;
    for(uint i = 0; i < hash_time; i++){
        pos.push_back(computePosition(hash_to_uint(key)));
        key = hash_to_string(key);
    }
    return pos;
}

void BloomFilter::addKey(std::string key){
    std::vector<struct position> pos_v = computePositions(key);

    std::lock_guard<std::mutex> lk(mut);
    for(std::vector<struct position>::const_iterator i = pos_v.begin(); i != pos_v.end(); i++){
        struct position pos = *i;
        lookup_list[pos.index] |= 1 << pos.offset;
    }
}

bool BloomFilter::keyMayMatch(std::string key){
    std::vector<struct position> pos_v = computePositions(key);
    for(std::vector<struct position>::const_iterator i = pos_v.begin(); i != pos_v.end(); i++){
        struct position pos = *i;
        if(!(lookup_list[pos.index] & (1 << pos.offset))){
            return false;
        }
    }
    return true;
}

}
