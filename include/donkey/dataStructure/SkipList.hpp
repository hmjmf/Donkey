//
// Created by 启翔 张 on 2017/12/28.
//

#ifndef PROJECT_SKIPLIST_HPP
#define PROJECT_SKIPLIST_HPP

#include "Donkey.hpp"
#include "glog/logging.h"
#include "util/random.hpp"
namespace Donkey{

template<typename Key_t>
class SkipList_Node{
public:
    explicit SkipList_Node(const Key_t& k, const uint height) :
            key(k),height(height){
        next_list_ = new SkipList_Node*[height]();
        memset(next_list_, 0, sizeof(SkipList_Node*) * height);
    }

    ~SkipList_Node(){
        delete[](next_list_);
    }

    SkipList_Node* next(int level) {
        if (level > height || level < 0) return nullptr;
        return next_list_[level];
    }

    void set_next(int level, SkipList_Node* x) {
        check_level(level);
        next_list_[level] = x;
    }

    const Key_t& get_key(){
        return key;
    }

    const uint height;

private:
    inline void check_level(int level){
        CHECK_GE(level, 0) << " level must >= 0";
        CHECK_LT(level, height) << " level must < height";
    }
    Key_t const key;
    SkipList_Node** next_list_;
};



template <typename Key_t>
class DONKEY_EXPORT SkipList final{
public:
    static std::shared_ptr<SkipList<Key_t>> create(const uint node_max_height_ = 12){
        return std::shared_ptr<SkipList<Key_t>>(new SkipList<Key_t>(node_max_height_));
    }
    ~SkipList(){
        SkipList_Node<Key_t>* x = head_;
        while (x->next(0) != NULL){
            SkipList_Node<Key_t>* will_del = x;
            x = x->next(0);
            delete(will_del);
        }
    }
private:
    explicit SkipList(const uint node_max_height_):
            node_max_height_(node_max_height_){
        CHECK_GT(node_max_height_, 0) << "node_max_height_ must > 0 ";
        head_ = new SkipList_Node<Key_t>(Key_t(), node_max_height_); //todo: 0 or Key_t()
        for (int i = 0; i < node_max_height_; i++) {
            head_->set_next(i, NULL);
        }
    }



public:
    void insert(const Key_t& key);

    bool contains(const Key_t& key) const;

    class iterator {
    public:
        explicit iterator(const SkipList* list);

        // Returns true if the iterator is positioned at a valid node.
        bool valid() const;


        // Returns the key at the current position.
        // REQUIRES: Valid()
        const Key_t& key() const;

        void next();

        void prev();

        void seek(const Key_t& target);

        void seek_to_first();

        void seek_to_last();

    private:
        const SkipList* list_;
        SkipList_Node<Key_t>* node_;
    };

private:
    const uint node_max_height_;
    SkipList_Node<Key_t>* head_;


    SkipList_Node<Key_t>* new_node(const Key_t& key, const uint height);

    int random_height();

    // Return true if key is greater than the data stored in "n"
    bool key_is_after_node(const Key_t& key, SkipList_Node<Key_t>* n) const;

    // Return the earliest node that comes at or after key.
    // Return NULL if there is no such node.
    //
    // If prev is non-NULL, fills prev[level] with pointer to previous
    // node at "level" for every level in [0..max_height_-1].
    SkipList_Node<Key_t>* find_greater_or_equal(const Key_t& key, SkipList_Node<Key_t>** prev) const;

    // Return the latest node with a key < key.
    // Return head_ if there is no such node.
    SkipList_Node<Key_t>* find_less_than(const Key_t& key) const;

    SkipList_Node<Key_t>* find_last() const;

    mutable std::mutex mut;
DISABLE_COPY_AND_ASSIGN(SkipList);
};



template <typename Key_t>
SkipList_Node<Key_t>* SkipList<Key_t>::new_node(const Key_t& key, const uint height){
    return new SkipList_Node<Key_t>(key, height);
}

template<typename Key_t>
inline SkipList<Key_t>::iterator::iterator(const SkipList* list) {
    list_ = list;
    node_ = list -> head_;
}

template<typename Key_t>
inline bool SkipList<Key_t>::iterator::valid() const {
    return node_ != NULL;
}


template<typename Key_t>
inline const Key_t& SkipList<Key_t>::iterator::key() const {
    CHECK(valid()) << "key not valid";
    return node_->get_key();
}

template<typename Key_t>
inline void SkipList<Key_t>::iterator::next() {
    CHECK(valid()) << "key not valid";
    node_ = node_->next(0);
}

template<typename Key_t>
inline void SkipList<Key_t>::iterator::prev() {
    // Instead of using explicit "prev" links, we just search for the
    // last node that falls before key.
    CHECK(valid()) << "key not valid";
    node_ = list_->find_less_than(node_->get_key());
    if (node_ == list_->head_) {
        node_ = NULL;
    }
}

template<typename Key_t>
inline void SkipList<Key_t>::iterator::seek(const Key_t& target) {
    node_ = list_->find_greater_or_equal(target, NULL);
}

template<typename Key_t>
inline void SkipList<Key_t>::iterator::seek_to_first(){
    node_ = list_->head_->next(0);
}

template<typename Key_t>
inline void SkipList<Key_t>::iterator::seek_to_last() {
    node_ = list_->find_last();
    if (node_ == list_->head_) {
        node_ = NULL;
    }
}


template<typename Key_t>
int SkipList<Key_t>::random_height() {
    // Increase height with probability 1 in kBranching
    static const unsigned int kBranching = 4;
    int height = 1;
    while (height < node_max_height_ && ((Donkey::random::uniform(0,1024) % kBranching) == 0)) {
        height++;
    }
    CHECK_GT(height, 0) << " height must > 0";
    CHECK_LE(height, node_max_height_) << " height must <= node_max_height_" ;
    return height;
}

template<typename Key_t>
bool SkipList<Key_t>::key_is_after_node(const Key_t &key, SkipList_Node<Key_t> *n) const {
    // NULL n is considered infinite
    return (n != NULL) && (n->get_key() < key);
}

template<typename Key_t>
SkipList_Node<Key_t>* SkipList<Key_t>::find_greater_or_equal(const Key_t &key, SkipList_Node<Key_t> **prev) const {
    SkipList_Node<Key_t>* x = head_;
    int level = node_max_height_ - 1;
    while (true) {
        CHECK(x == head_ || x->get_key() < key) << "(x == head_ || x->key < key) == false";
        SkipList_Node<Key_t>* next = x->next(level);
        if (key_is_after_node(key, next)) { // next NULL is considered infinite
            // Keep searching in this list
            x = next;
        } else {
            if (prev != NULL) prev[level] = x;
            if (level == 0) {
                return next;
            } else {
                level--;
            }
        }
    }
}
template<typename Key_t>
SkipList_Node<Key_t>* SkipList<Key_t>::find_less_than(const Key_t& key) const{
    SkipList_Node<Key_t>* x = head_;
    int level = node_max_height_ - 1;
    while (true) {
        CHECK(x == head_ || x->get_key() < key) << "x>=key,x:"<<x->get_key()<<",key:"<<key;
        SkipList_Node<Key_t>* next = x->next(level);
        if (next == NULL || next->get_key() >= key) {
            if (level == 0) {
                return x;
            } else {
                // Switch to next list
                level--;
            }
        } else {
            x = next;
        }
    }
}

template<typename Key_t>
SkipList_Node<Key_t>* SkipList<Key_t>::find_last() const {
    SkipList_Node<Key_t>* x = head_;
    int level = node_max_height_ - 1;
    while (true) {
        SkipList_Node<Key_t>* next = x->next(level);
        if (next == NULL) {
            if (level == 0) {
                return x;
            } else {
                // Switch to next list
                level--;
            }
        } else {
            x = next;
        }
    }
}


template<typename Key_t>
void SkipList<Key_t>::insert(const Key_t& key) {
    std::lock_guard<std::mutex> lk(mut);
    SkipList_Node<Key_t>* prev[node_max_height_];
    SkipList_Node<Key_t>* x = find_greater_or_equal(key, prev);

    //x is null means tail
    if (x != NULL && key == x->get_key()) return;
    CHECK(x == NULL || x == head_ || x->get_key() >= key) << "";

    int height = random_height();

    x = new_node(key, height);
    for (int i = 0; i < height; i++){
        x->set_next(i, prev[i]->next(i));
        prev[i]->set_next(i,x);
    }

}

template<typename Key_t>
bool SkipList<Key_t>::contains(const Key_t& key) const {
    std::lock_guard<std::mutex> lk(mut);
    SkipList_Node<Key_t>* x = find_greater_or_equal(key, NULL);
    if(x == head_) return false;
    return x!=NULL && x->get_key() == key;
}




}



#endif //PROJECT_SKIPLIST_HPP
