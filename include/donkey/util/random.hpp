//
// Created by 启翔 张 on 2017/12/27.
//

#ifndef PROJECT_RANDOM_HPP
#define PROJECT_RANDOM_HPP

#include <time.h>
#include <stdlib.h>
#include <Donkey.hpp>
#include <random>
#include "glog/logging.h"

namespace Donkey{
namespace random{


DONKEY_EXPORT int uniform(int min = -RAND_MAX, int max = RAND_MAX);
DONKEY_EXPORT double normal(int m = 0, int s = 1);



DONKEY_EXPORT std::string random_string(const uint length, bool lower = true,
                                        bool caps = true, bool num = true,
                                        bool special = false);


}
}


#endif //PROJECT_RANDOM_HPP
