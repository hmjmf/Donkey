/*******************************************************
 *  coding
 *  My Website           https://zhangqixiang.cn
 *  My Github            https://github.com/hmjmf
 *  Email                zqx5449@gmail.com
 * 
 *  Created by 启翔 张 (QiXiang Zhang) on 2018/3/26.
 *  Copyright (c) 2018 . All rights reserved.
 *******************************************************/



#include "util/coding.hpp"
namespace Donkey{
namespace coding {




std::string uint_to_hex_str(unsigned int num) {
  char str[sizeof(num) * 2 + 1];
  sprintf(str,"%x",num);
  return str;
}

}
}