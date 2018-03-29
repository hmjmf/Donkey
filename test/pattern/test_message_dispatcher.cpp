/*******************************************************
 *  test_message_dispatcher
 *  My Website           https://zhangqixiang.cn
 *  My Github            https://github.com/hmjmf
 *  Email                zqx5449@gmail.com
 * 
 *  Created by 启翔 张 (QiXiang Zhang) on 2018/3/28.
 *  Copyright (c) 2018 . All rights reserved.
 *******************************************************/



#include <iostream>
#include "gtest/gtest.h"
#include "pattern/message_dispatcher.hpp"
#include "util/coding.hpp"
#include <string>

using namespace std;
string s_test_message_dispatcher;
void Call1()
{
  s_test_message_dispatcher += "call1";
}

int Call2(int a)
{
  return a;
}
enum EnumMessage
{
  Message1,
  Message2
};

template<int key, typename R, typename... Args>
R dispatch(Args... args)
{
  auto tpkey = std::make_tuple(Message1, Message2);
  auto tpval = std::make_tuple(Call1, Call2);
  auto pairs = Donkey::pattern::zip_tuple(tpkey, tpval);

  return Donkey::pattern::apply(std::get<key>(pairs).second, args...);
}

TEST(message_dispatcher, base){
  dispatch<Message1, void>();
  s_test_message_dispatcher += Donkey::coding::to_str(dispatch<Message2, int>(1));
  EXPECT_EQ(s_test_message_dispatcher, "call11");
}