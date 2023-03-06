#include <iostream>
#include <thread>


// Note: If you compile without the -pthread flag, you will see an error of the form: undefined reference to pthread_create. 
// You will need to use the -pthread flag for all other multithreaded examples in this course going forward.

// The main function finishes before the thread because the delay inserted into the thread function is much larger than in the main path of execution.
// The call to join() at the end of the main function ensures that it will not prematurely return. 
// As an experiment, comment out t.join() and execute the program. What do you expect will happen?

// Ans: Specifically for C++ threads, std::terminate will be called, effectively aborting the program.
// https://en.cppreference.com/w/cpp/thread/thread/%7Ethread
// If the other threads are detached, then they are just cleaned up by the OS.
// EDIT: to clarify, std::terminate is called even if all other threads have been terminated, if those threads have not been joined or detached.


// If thread A creates thread B and then thread A terminates, then thread B will continue to execute.
// The exception to this is when the main thread (that is, the thread that runs the main() function) terminates. 
// When this happens, the process terminates and all other threads stop. 
// If any thread calls exit, then all threads terminate.

void randomFunction()
{

    // If any thread calls exit, then all threads terminate.
    // exit(0);

    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // simulate work
    std::cout << "Finished work in thread\n"; 
}

int main()
{
    // create thread
    std::thread t(randomFunction);

    // do something in main()
    std::this_thread::sleep_for(std::chrono::milliseconds(50)); // simulate work
    std::cout << "Finished work in main\n";

    // wait for thread to finish
    t.join();
    // exit(0);

    return 0;
}