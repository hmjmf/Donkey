//
// Created by 启翔 张 on 2017/12/26.
//
#include "util/coding.hpp"
namespace Donkey{
namespace coding {




std::string uint_to_hex_str(unsigned int num) {
  std::string hexstr = "";
  char szch[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };
  unsigned char *tmptr = (unsigned char *)&num;
  int len = sizeof(num);
  // 小端字节序，逆序打印
  for (int i = 0; i < len; i++){
    unsigned char ch = tmptr[i] & 0xF0;
    ch = ch >> 4;
    hexstr.append(1, szch[ch]);
    ch = tmptr[i] & 0x0F;
    hexstr.append(1, szch[ch]);
  }
  return hexstr;
}

}
}