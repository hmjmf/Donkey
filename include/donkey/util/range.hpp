//
// Created by 启翔 张 on 2017/12/29.
//

#ifndef PROJECT_RANGE_HPP
#define PROJECT_RANGE_HPP


namespace Donkey{

template <typename value_t>
class range_iterator{
public:
  explicit range_iterator(value_t val):value_(val){}

  bool operator!=(const range_iterator<value_t>& rhs) const {
   return (this->get_value()) != (rhs.get_value());
  }

  value_t operator*() const {
   return this->get_value();
  }

  const range_iterator& operator++() {
   ++value_;
   return *this;
  }
  const range_iterator& operator--() {
    --value_;
    return *this;
  }

private:
  value_t get_value() const {
    return value_;
  }
  value_t value_;
};


template <typename value_t>
class Range{
public:
  Range(value_t begin_v, value_t end_v)
      :begin_value_(begin_v), end_value_(end_v){
    if(begin_value_ > end_value_){
      begin_value_ = end_value_;
    }
  }


  range_iterator<value_t> begin() const {
   return range_iterator<value_t>(begin_value_);
  }
  range_iterator<value_t> end() const {
   return range_iterator<value_t>(end_value_ );
  }
private:
  value_t begin_value_;
  value_t end_value_;
};




}



#endif //PROJECT_RANGE_HPP
