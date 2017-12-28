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
    for (int i = 0; i < 10; i++){
        sleep(1);
        std::cout << i << std::endl;
    }
}
void dosmel(){
    for (int i = 10; i < 20; i++){
        sleep(1);
        std::cout << i << std::endl;
    }
}

int main(int argc, char** argv,  char *envp[]) {


    std::thread my_t1(dosm);
    std::thread my_t2(dosmel);
    my_t1.join();
    my_t2.join();
    std::cout << "end" << std::endl;
    return 0;
}