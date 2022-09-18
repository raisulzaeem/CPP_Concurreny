#include <iostream>
#include <thread>


int main(){
    unsigned int nThreads = std::thread::hardware_concurrency();
    std::cout<<"This machine supports concurrency with "<<nThreads<<" concurrent threads available"<<std::endl;

    // A running program consists of at least one thread. 
    // When the main function is executed, we refer to it as the "main thread". 
    // Threads are uniquely identified by their thread ID, which can be particularly useful for debugging a program.

    std::cout << "Hello concurrent world from main! Thread id = " << std::this_thread::get_id() << std::endl;
}

