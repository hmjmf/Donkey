//
// Created by 启翔 张 on 2017/12/24.
//

#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <fstream>
#include <signal.h>
#include <thread>

void dosm(){
    while (1) {
        std::cout << 1 << std::endl;
    }
}

int main(int argc, char** argv,  char *envp[]) {


    std::thread my_t(dosm);
    my_t.detach();

    return 0;
}