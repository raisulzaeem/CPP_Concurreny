#include <iostream>
#include <thread>


int main(){
    unsigned int nThreads = std::thread::hardware_concurrency();
    std::cout<<"This machine supports concurrency with "<<nThreads<<" concurrent threads available"<<std::endl;

    std::cout << "Hello concurrent world from main! Thread id = " << std::this_thread::get_id() << std::endl;
}

