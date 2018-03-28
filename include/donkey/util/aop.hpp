/*******************************************************
 *  aop
 *  My Website           https://zhangqixiang.cn
 *  My Github            https://github.com/hmjmf
 *  Email                zqx5449@gmail.com
 * 
 *  Created by 启翔 张 (QiXiang Zhang) on 2018/3/26.
 *  Copyright (c) 2018 . All rights reserved.
 *******************************************************/



#ifndef PROJECT_AOP_HPP
#define PROJECT_AOP_HPP

#include <iostream>
#include "util/comment.hpp"
using namespace std;


namespace Donkey{

class aspect{
  DISABLE_COPY_AND_ASSIGN(aspect);

public:
  template <typename Func>
  aspect(const Func& f):func_(f){}

  template <typename T>
  void invoke(T&& value){
    value.before();
    func_();
    value.after();
  }

  template <typename Head_t, typename... Tail_t>
  void invoke(Head_t&& head, Tail_t&&... tail){
    head.before();
    invoke(forward<Tail_t>(tail)...);
    head.after();
  }
private:
  function<void()> func_;
};

template <typename... AP>
void invoke(const function<void()> f){
  aspect sp(f);
  sp.invoke(AP()...);
}



}


#endif //PROJECT_AOP_HPP
