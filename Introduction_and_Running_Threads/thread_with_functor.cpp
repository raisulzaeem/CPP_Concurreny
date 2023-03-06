#include <iostream>
#include <thread>

class Vehicle
{
public:
    void operator()()
    {
        std::cout << "Vehicle object has been created \n" << std::endl;
    }
};


int main()
{
    // // create thread 
    // std::thread t(Vehicle()); // C++'s most vexing parse

    std::thread t1( (Vehicle()) ); // Add an extra pair of parantheses
    
    std::thread t2 = std::thread( Vehicle() ); // Use copy initialization
    
    std::thread t3{ Vehicle() };// Use uniform initialization with braces

    // Whichever option we use, the idea is the same: the function object is copied into internal storage accessible to the new thread, 
    // and the new thread invokes the operator (). The Vehicle class can of course have data members and other member functions too.

    // do something in main()
    std::cout << "Finished work in main \n";

    // wait for thread to finish
    t1.join();
    t2.join();
    t3.join();

    // t.join();

    return 0;
}