//
// Created by zqx on 18-1-1.
//

#ifndef PROJECT_SKIPLIST_BUCKET_H
#define PROJECT_SKIPLIST_BUCKET_H

#include "SkipList.hpp"
#include "util/range.hpp"
#include <algorithm>



namespace Donkey{


template <typename Key_t>
class DONKEY_EXPORT SkipList_bucket final{
public:
    //bucket:{....,-100,0,100,...}
    static std::shared_ptr<SkipList_bucket> create(std::vector<Key_t> bucket, const uint node_max_height = 12){
        return std::shared_ptr<SkipList_bucket<Key_t>>(new SkipList_bucket<Key_t>(node_max_height, bucket));
    }
    void insert(const Key_t& key){
        int index = find_index(key);
        SL_bucket[index] -> insert(key);
    }
    bool contains(const Key_t& key) const {
        int index = find_index(key);
        SL_bucket[index] -> contains(key);
    }

private:
    SkipList_bucket(const uint node_max_height, const std::vector<Key_t> bucket){
        bucket_ = bucket;
        std::sort(bucket_.begin(), bucket_.end());
        bucket_szie = bucket.size() + 1;
        for(auto x: Range<int>(0,bucket_szie)){
            SL_bucket.emplace_back(SkipList<Key_t>::create(node_max_height));
        }
    }
    int find_index(const key_t& key) const {
        int index = 0;
        for (; index < bucket_szie; index++){
            if (key < bucket_[index]){
                break;
            }
        }
        CHECK_GE(index , 0) << "index must >= 0";
        CHECK_LT(index, bucket_szie) << "index must < bucket_size";
        return index;
    }
    std::vector<Key_t> bucket_;
    std::vector<std::shared_ptr<SkipList<key_t>>> SL_bucket;
    uint bucket_szie;


};




}

#endif //PROJECT_SKIPLIST_BUCKET_H
