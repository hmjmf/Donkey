//
// Created by 启翔 张 on 2018/1/2.
//

#include "gtest/gtest.h"
#include <glog/logging.h>
#include "SkipList.hpp"

TEST(B,c){
    Donkey::SkipList<int>t();
    EXPECT_EQ(1,1);
}


int main(int argc, char **argv) {
    FLAGS_alsologtostderr = 1;
    google::InitGoogleLogging(argv[0]);
    google::SetLogDestination(google::GLOG_FATAL, "./log_FATAL"); //level 3
    google::SetLogDestination(google::GLOG_ERROR, "./log_ERROR"); //level 2
    google::SetLogDestination(google::GLOG_WARNING, "./log_WARNING"); //level 1
    google::SetLogDestination(google::GLOG_INFO, "./log_INFO"); //level 0

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
