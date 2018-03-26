//
// Created by 启翔 张 on 2017/12/27.
//

#include "dataStructure/BloomFilter.hpp"
namespace Donkey{



BloomFilter::BloomFilter(uint32_t size, uint hash_time):
  hash_time_(hash_time){
  this->size_ = (size / (sizeof(char) * 8)) + 1;
  lookup_list_ = new char [this->size_];
  CHECK(lookup_list_ != nullptr) << "BloomFilter lookup_list_ is null";
  memset(lookup_list_, 0, this->size_);
}

struct position BloomFilter::computePosition(uint32_t num) const{
  struct position pos;
  num %= (size_ * 8);
  pos.index = num / 8;
  pos.offset = num % 8;
  CHECK_LT(pos.index, size_) << "pos.index too big";
  return pos;
}

std::vector<struct position> BloomFilter::computePositions(std::string key) const{
  std::vector<struct position> pos;
  for(uint i = 0; i < hash_time_; i++){
    pos.emplace_back(computePosition(hash_to_uint(key)));
    key = hash_to_string(key);
  }
  return pos;
}

void BloomFilter::addKey(std::string key){
  std::vector<struct position> pos_v = computePositions(key);

  std::lock_guard<std::mutex> lk(mut);
  for(std::vector<struct position>::const_iterator i = pos_v.begin(); i != pos_v.end(); i++){
    struct position pos = *i;
    lookup_list_[pos.index] |= 1 << pos.offset;
  }
}

bool BloomFilter::keyMayMatch(std::string key) const{
  std::vector<struct position> pos_v = computePositions(key);
  for(std::vector<struct position>::const_iterator i = pos_v.begin(); i != pos_v.end(); i++){
    struct position pos = *i;
    if(!(lookup_list_[pos.index] & (1 << pos.offset))){
      return false;
    }
  }
  return true;
}

}
