#include <iostream>
#include <thread>
#include <vector>
#include <future>

int myAmount{0};

void putMoney(int money) {

    int oldMoney = myAmount;
    std::this_thread::sleep_for(std::chrono::microseconds(1));
    myAmount = oldMoney+money;

}

int main() {

    std::vector<std::future<void>> ftrs;
    std::vector<std::thread> threads;
    
    for (int i=0; i<10; i++){
        ftrs.push_back(std::async(std::launch::async, putMoney, 1));
        threads.push_back(std::thread(putMoney, 1));
    }

    for (unsigned int i=0; i<ftrs.size(); ++i){
        ftrs.at(i).wait();
        threads.at(i).join();
    }
    // myAmount can be 20 and but not guaranteed.
    std::cout<<myAmount<<std::endl;
}