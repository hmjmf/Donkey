//
// Created by 启翔 张 on 2017/12/27.
//

#ifndef PROJECT_BLOOMFILTER_HPP
#define PROJECT_BLOOMFILTER_HPP

#include "Donkey.hpp"
#include "util/hash.hpp"
#include "glog/logging.h"
#include <iostream>
#include <memory>
#include <mutex>

namespace Donkey{

struct position{
    uint index;
    uint offset;
};

class BloomFilter{
public:
    static std::shared_ptr<BloomFilter> create(uint32_t size, uint hash_time){
        return std::shared_ptr<BloomFilter>(new BloomFilter(size, hash_time));
    }

    //return true means maybe in the BloomFilter
    //return false means must not in the BloomFilter
    bool keyMayMatch(std::string key) const;

    void addKey(std::string key);

protected:
    struct position computePosition(uint32_t num) const;
    std::vector<struct position> computePositions(std::string key) const;

private:
    BloomFilter(uint32_t size, uint hash_time);
    uint32_t size_;
    uint hash_time_;
    char* lookup_list_;

    mutable std::mutex mut;
DISABLE_COPY_AND_ASSIGN(BloomFilter);
};




}



#endif //PROJECT_BLOOMFILTER_HPP
