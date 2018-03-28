/*******************************************************
 *  test_aop
 *  My Website           https://zhangqixiang.cn
 *  My Github            https://github.com/hmjmf
 *  Email                zqx5449@gmail.com
 * 
 *  Created by 启翔 张 (QiXiang Zhang) on 2018/3/26.
 *  Copyright (c) 2018 . All rights reserved.
 *******************************************************/



#include <iostream>
#include "gtest/gtest.h"
#include "util/aop.hpp"
#include <string>
#include "util/coding.hpp"

std::string s;
struct AA
{
  void before()
  {
    s += "Before from AA;";
  }

  void after()
  {
    s += "After from AA;";
  }
};

struct BB
{
  void before()
  {
    s += "Before from BB;";
  }

  void after()
  {
    s += "After from BB;";
  }
};

struct CC
{
  void before()
  {
    s += "Before from CC;";
  }

  void after()
  {
    s += "After from CC;";
  }
};

struct TT
{
  void g()
  {
    s += "real g function;";
  }

  void h(int a)
  {
    s += "real h function";
    s += Donkey::coding::to_str(a);
    s += ";";
  }
};

struct DD
{
  void before()
  {

  }

  void after()
  {

  }
};

void GT()
{
  s += "real GT function;";
}

void HT(int a)
{
  s += "real HT function";
  s += Donkey::coding::to_str(a);
  s += ";";
}


TEST(aop, base){
  TT tt;
  std::function<void()> ff = std::bind(&TT::g, &tt);
  //组合了两个切面AA BB
  s = "";
  Donkey::invoke<AA,BB>([&ff](){ff();}); //织入成员函数
  EXPECT_EQ(s,"Before from AA;"
              "Before from BB;"
              "real g function;"
              "After from BB;"
              "After from AA;");

  s = "";
  Donkey::invoke<AA,BB>([&tt](){tt.g();}); //织入对象
  EXPECT_EQ(s,"Before from AA;"
              "Before from BB;"
              "real g function;"
              "After from BB;"
              "After from AA;");


  s = "";
  int aa = 3;
  Donkey::invoke<AA,BB>(&GT); //织入方法
  EXPECT_EQ(s,"Before from AA;"
              "Before from BB;"
              "real GT function;"
              "After from BB;"
              "After from AA;");


  s = "";
  Donkey::invoke<AA,BB>([aa](){HT(aa);});//织入带参的方法
  EXPECT_EQ(s,"Before from AA;"
              "Before from BB;"
              "real HT function3;"
              "After from BB;"
              "After from AA;");

  //织入带参数的成员函数和对象
  std::function<void(int)> ff1 = std::bind(&TT::h, &tt, std::placeholders::_1);
  s = "";
  Donkey::invoke<AA,BB,CC,DD>([&ff1,aa](){ff1(aa);}); //组合了四个切面
  EXPECT_EQ(s,"Before from AA;"
              "Before from BB;"
              "Before from CC;"
              "real h function3;"
              "After from CC;"
              "After from BB;"
              "After from AA;");

  s = "";
  Donkey::invoke<AA,BB>([&tt,aa](){tt.h(aa);});
  EXPECT_EQ(s,"Before from AA;"
              "Before from BB;"
              "real h function3;"
              "After from BB;"
              "After from AA;");
}