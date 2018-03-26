//
// Created by 启翔 张 on 2017/12/28.
//

#ifndef PROJECT_SKIPLIST_HPP
#define PROJECT_SKIPLIST_HPP

#include "util/comment.hpp"
#include "glog/logging.h"
#include "util/random.hpp"

namespace Donkey{

template<typename Tp>
class skip_lists_node{
public:
  explicit skip_lists_node(const Tp& k, const uint height) :
      key(k),height(height){
    next_list_ = new skip_lists_node*[height]();
    memset(next_list_, 0, sizeof(skip_lists_node*) * height);
  }

  ~skip_lists_node(){
    delete[](next_list_);
  }

  skip_lists_node* next(int level) {
    if (level > height || level < 0) return nullptr;
    return next_list_[level];
  }

  void set_next(int level, skip_lists_node* x) {
    check_level(level);
    next_list_[level] = x;
  }

  const Tp& get_key(){
    return key;
  }

  const uint height;

private:
  inline void check_level(int level){
    CHECK_GE(level, 0) << " level must >= 0";
    CHECK_LT(level, height) << " level must < height";
  }
  Tp const key;
  skip_lists_node** next_list_;
};


template<typename Tp>
struct skip_list_const_iterator{
  typedef Tp                 value_type;
  typedef value_type*             pointer;
  typedef value_type&             reference;
  typedef const Tp&              const_reference;

  typedef skip_lists_node<Tp>          node_type;
  typedef skip_list_const_iterator<Tp>      self_type;
  typedef std::forward_iterator_tag      iterator_category;

  skip_list_const_iterator() noexcept : node_() {}
  explicit skip_list_const_iterator(node_type* n) noexcept :node_(n){}

  reference operator*() const noexcept {
    return this->node_->get_key();
  }
  pointer operator->() const noexcept {
    return &(this->node_->get_key());
  }
  self_type& operator++() noexcept {
    node_ = node_ -> next(0);
    return *this;
  }
  self_type operator++(int) noexcept {
    self_type tmp(*this);
    node_ = node_->next(0);
    return tmp;
  }
  bool operator==(const self_type& rhs) const noexcept {
    return node_ == rhs.node_;
  }
  bool operator!=(const self_type& rhs) const noexcept {
    return node_ != rhs.node_;
  }
  self_type next_() const noexcept {
    if(node_){
      return skip_list_const_iterator(node_->next(0));
    } else {
      return skip_list_const_iterator(nullptr);
    }
  }
  node_type* node_;
};

template <typename Tp>
class skip_list final{
public:
  typedef Tp               value;
  typedef Tp&               reference;
  typedef const Tp&            const_reference;
  typedef value*             pointer;
  typedef skip_list<Tp>          self_type;
  typedef skip_lists_node<Tp>        node_type;
  typedef skip_list_const_iterator<Tp>    iterator;

public:
  static std::shared_ptr<self_type> create(const uint node_max_height_ = 12){
    return std::shared_ptr<self_type>(new self_type(node_max_height_));
  }
  ~skip_list(){
    node_type* x = head_;
    while (x->next(0) != NULL){
      node_type* will_del = x;
      x = x->next(0);
      delete(will_del);
    }
  }
private:
  explicit skip_list(const uint node_max_height_):
      node_max_height_(node_max_height_){
    CHECK_GT(node_max_height_, 0) << "node_max_height_ must > 0 ";
    head_ = new node_type(value(), node_max_height_); //todo: 0 or Tp()
    for (int i = 0; i < node_max_height_; i++) {
      head_->set_next(i, NULL);
    }
  }



public:
  void insert(const_reference key);

  bool contains(const_reference key) const;


  iterator begin(){
    return iterator(head_->next(0));
  }
  iterator end(){
    return iterator(NULL);
  }
private:
  const uint node_max_height_;
  node_type* head_;


  node_type* new_node(const Tp& key, const uint height);

  int random_height();

  // Return true if key is greater than the data stored in "n"
  bool key_is_after_node(const Tp& key, node_type* n) const;

  // Return the earliest node that comes at or after key.
  // Return NULL if there is no such node.
  //
  // If prev is non-NULL, fills prev[level] with pointer to previous
  // node at "level" for every level in [0..max_height_-1].
  node_type* find_greater_or_equal(const Tp& key, node_type** prev) const;

  // Return the latest node with a key < key.
  // Return head_ if there is no such node.
  node_type* find_less_than(const Tp& key) const;

  node_type* find_last() const;

  mutable std::mutex mut;
DISABLE_COPY_AND_ASSIGN(skip_list);
};



template <typename Tp>
skip_lists_node<Tp>* skip_list<Tp>::new_node(const Tp& key, const uint height){
  return new skip_lists_node<Tp>(key, height);
}

template<typename Tp>
int skip_list<Tp>::random_height() {
  // Increase height with probability 1 in kBranching
  static const unsigned int kBranching = 4;
  int height = 1;
  while (height < node_max_height_ &&
         ((Donkey::random::uniform(0,1024) % kBranching) == 0)) {
    height++;
  }
  CHECK_GT(height, 0) << " height must > 0";
  CHECK_LE(height, node_max_height_) << " height must <= node_max_height_" ;
  return height;
}

template<typename Tp>
bool skip_list<Tp>::key_is_after_node(const_reference key, node_type *n) const {
  // NULL n is considered infinite
  return (n != NULL) && (n->get_key() < key);
}

template<typename Tp>
skip_lists_node<Tp>* skip_list<Tp>::
    find_greater_or_equal(const_reference key, node_type** prev) const {
  node_type* x = head_;
  int level = node_max_height_ - 1;
  while (true) {
    CHECK(x == head_ || x->get_key() < key)
      << "(x == head_ || x->key < key) == false";
    node_type* next = x->next(level);
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
template<typename Tp>
skip_lists_node<Tp>* skip_list<Tp>::find_less_than(const_reference key) const{
  node_type* x = head_;
  int level = node_max_height_ - 1;
  while (true) {
    CHECK(x == head_ || x->get_key() < key)
      << "x>=key,x:"<<x->get_key()<<",key:"<<key;
    node_type* next = x->next(level);
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

template<typename Tp>
skip_lists_node<Tp>* skip_list<Tp>::find_last() const {
  node_type* x = head_;
  int level = node_max_height_ - 1;
  while (true) {
    node_type* next = x->next(level);
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


template<typename Tp>
void skip_list<Tp>::insert(const_reference key) {
  std::lock_guard<std::mutex> lk(mut);
  node_type* prev[node_max_height_];
  node_type* x = find_greater_or_equal(key, prev);

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

template<typename Tp>
bool skip_list<Tp>::contains(const_reference key) const {
  std::lock_guard<std::mutex> lk(mut);
  node_type* x = find_greater_or_equal(key, NULL);
  if(x == head_) return false;
  return x!=NULL && x->get_key() == key;
}




}



#endif //PROJECT_SKIPLIST_HPP
