#include <iostream>
#include <thread>

// Executing the code several times more shows that the two versions of program output interchange in a seemingly random manner. 
// This element of randomness is an important characteristic of concurrent programs and we have to take measures to deal with it 
// in a controlled way that prevent unwanted behavior or even program crashes.

void threadFunction()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(50)); // simulate work
    std::cout << "Finished work 1 in thread\n"; 

    std::this_thread::sleep_for(std::chrono::milliseconds(50)); 
    std::cout << "Finished work 2 in thread\n"; 
}

int main()
{
    // create thread
    std::thread t(threadFunction);

    // If we wanted to ensure that the thread function completed its work before the main function started its own work 
    // (because it might be waiting for a result to be available), we could achieve this by repositioning the call to join.
    
    // t.join();

    // do something in main()
    std::this_thread::sleep_for(std::chrono::milliseconds(50)); // simulate work
    std::cout << "Finished work 1 in main\n";

    std::this_thread::sleep_for(std::chrono::milliseconds(50)); 
    std::cout << "Finished work 2 in main\n";
    
    // wait for thread to finish
    t.join();

    return 0;
}