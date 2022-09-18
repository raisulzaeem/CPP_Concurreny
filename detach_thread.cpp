#include <iostream>
#include <thread>

// Programmers should be very careful though when using the detach()-method. 
// You have to make sure that the thread does not access any data that might get out of scope or be deleted. 
// Also, we do not want our program to terminate with threads still running. 
// Should this happen, such threads will be terminated very harshly without giving them the chance to properly 
// clean up their resources - what would usually happen in the destructor.

void threadFunction()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(500)); // simulate work
    std::cout << "Finished work in thread\n"; 
}

int main()
{
    // create thread
    std::thread t(threadFunction);

    // detach thread and continue with main
    t.detach();

    // do something in main()
    std::this_thread::sleep_for(std::chrono::milliseconds(50)); // simulate work
    std::cout << "Finished work in main\n";

    return 0;
}