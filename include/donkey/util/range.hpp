/*******************************************************
 *  range
 *  My Website           https://zhangqixiang.cn
 *  My Github            https://github.com/hmjmf
 *  Email                zqx5449@gmail.com
 * 
 *  Created by 启翔 张 (QiXiang Zhang) on 2018/3/26.
 *  Copyright (c) 2018 . All rights reserved.
 *******************************************************/



#ifndef PROJECT_RANGE_HPP
#define PROJECT_RANGE_HPP

#include <stdexcept>

namespace Donkey{

template <typename value_t>
class range_impl{
private:
  class iterator;

public:
  range_impl(value_t begin, value_t end, value_t step):
      begin_(begin),
      end_(end),
      step_(step){
    if (step_ > 0 && begin_ > end_){
      throw std::logic_error("end must greater than begin.");
    } else if (step_<0 && begin_ <= end_){
      throw std::logic_error("end must less than begin.");
    }

    step_end_ = (end_ - begin_) / step_;
    if (begin_ + step_end_ * step_ != end_)
    {
      step_end_++;
    }
  }

  iterator begin(){
    return iterator(0, *this);
  }
  iterator end(){
    return iterator(step_end_, *this);
  }
  value_t operator[](int s){
    return begin_ + s * step_;
  }
  int size(){
    return step_end_;
  }

private:
  value_t begin_;
  value_t end_;
  value_t step_;
  int step_end_;

  class iterator{
  public:
    iterator(int start, range_impl& range)
        :current_step_(start),
         range_(range){
      current_value_ = range_.begin_ + current_step_ * range_.step_;
    }

    value_t operator*(){
      return current_value_;
    }

    const iterator* operator++(){
      current_value_ += range_.step_;
      current_step_++;
      return this;
    }

    bool operator==(const iterator& other){
      return current_step_ == other.current_step_;
    }

    bool operator!=(const iterator& other){
      return !(*this == other);
    }

    const iterator* operator--(){
      current_value_ -= range_.step_;
      current_step_--;
      return this;
    }
  private:
    value_t current_value_;
    int current_step_;
    range_impl& range_;
  };
};

template <typename T, typename V>
auto range(T begin, T end, V step_size)
-> range_impl<decltype(begin + end + step_size)>{
  //decltype(begin + end + step_size)
  // if begin:1,end:2.2,step_size:1  ->  float
  // if begin:'a',end:'z',step_size:1  ->  char
  return range_impl<decltype(begin + end + step_size)>(begin, end, step_size);
}

template <typename T>
range_impl<T> range(T begin, T end){
  return range_impl<T>(begin, end, 1);
}

template <typename T>
range_impl<T> range(T end){
  return range_impl<T>(T(), end, 1);
}
};

#endif //PROJECT_RANGE_HPP
