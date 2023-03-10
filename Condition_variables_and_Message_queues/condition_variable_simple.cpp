#include<iostream>
#include<thread>
#include<vector>
#include<future>
#include<mutex>
#include<condition_variable>

long balance{0};
std::mutex mtx;
std::condition_variable cv;

void drawMoney(long money){
    std::unique_lock<std::mutex> uLock(mtx);

    // condition_variable::wait takes a unique_lock argument, which it will release while waiting.
    // condition_variable::notify_one() method is called, the object will check the lambda(if given). 
    // If it returns true, it will continue the rest of the code locking the mutex once again.
    // Otherwise it will keep waiting.
    cv.wait(uLock, [money]{return (balance>=money)? true: false;});
    balance = balance-money;
    std::cout<<"Money drawn : "<<money<<"\nCurrent Balance : "<<balance<<std::endl;
}

void addMoney(long money){
    std::lock_guard<std::mutex> lockGuard(mtx);
    balance = balance+money;
    std::cout<<"Money Added : "<<money<<"\nCurrent Balance : "<<balance<<std::endl;
    cv.notify_one();

}

int main(){

    std::vector<std::future<void>> futures;
    std::vector<std::thread> threads;


    for (int i=500; i<=5000; i+=100){
        // futures.emplace_back(std::async(addMoney,i));
        threads.emplace_back(std::thread(drawMoney,i));
    }


    for (int i=500; i<=5000; i+=100){
        // futures.emplace_back(std::async(addMoney,i));
        threads.emplace_back(std::thread(addMoney,i));
    }

    for(std::thread& thread: threads){
        thread.join();
    }

    
}