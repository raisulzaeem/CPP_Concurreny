#include <iostream>
#include <thread>


// What if we wish to run a member function other than the function call operator, such as a member function of an existing object? 
// Luckily, the C++ library can handle this use-case: 
// For calling member functions, the std::thread function requires an additional argument for the object on which to invoke the member function.
// std::thread(&Class::method, <<object>> , arg);

class Vehicle
{
public:
    Vehicle() : _id(0) {}
    void addID(int id) { 
        std::cout << "add ID=" << id << std::endl;
        _id = id;}
    void printID()
    {
        std::cout << "Vehicle ID=" << _id << std::endl;
    }

private:
    int _id;
};

int main()
{
    // create thread
    Vehicle v1, v2;
    std::thread t1 = std::thread(&Vehicle::addID, v1, 1); // call member function on object v
    std::thread t2 = std::thread(&Vehicle::addID, &v2, 2); // call member function on object v

    // wait for thread to finish
    t1.join();
    t2.join();

    // print Vehicle id
    v1.printID();
    v2.printID();

    return 0;
}