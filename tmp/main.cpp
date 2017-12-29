//
// Created by 启翔 张 on 2017/12/28.
//
#include<iostream>    //std::cout std::endl
#include<thread>      //std::thread
#include<future>      //std::future std::promise
#include<utility>     //std::ref
#include<chrono>      //std::chrono::seconds
#include<vector>

void initiazer(std::promise<int> &promiseObj){
    std::cout << "Inside thread: " << std::this_thread::get_id() << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    promiseObj.set_value(35);
}

int main(){
//    std::promise<int> promiseObj;
//    std::future<int> futureObj = promiseObj.get_future();
//    std::thread th(initiazer, std::ref(promiseObj));
//
//    std::cout << futureObj.get() << std::endl;
//
//    th.join();

    int num = 8;
    std::vector<std::promise<int>> promiseObj_v;
    for (int i = 0; i < num; i++){
        promiseObj_v.push_back( std::promise<int>());
    }
    std::vector<std::future<int>> futureObj_v;
    for (int i = 0; i < num; i++){
        futureObj_v.push_back(promiseObj_v[i].get_future());
    }

    std::vector<std::thread> thread_v;
    for (int i = 0; i < num; i++){
        thread_v.push_back(std::thread(initiazer, std::ref(promiseObj_v[i])));
    }
    for (int i = 0; i < num; i++){
        std::cout << futureObj_v[i].get() << std::endl;
    }
    for (int i = 0; i < num; i++){
        thread_v[i].join();
    }


    return 0;
}