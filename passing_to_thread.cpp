#include <iostream>
#include <thread>
#include <string>


// There is one more difference between calling a function directly and passing it to a thread: With the former, 
// arguments may be passed by value, by reference or by using move semantics - depending on the signature of the function. 
// When calling a function using a variadic template, the arguments are by default either moved or copied - depending on 
// wether they are rvalues or lvalues.


void printName(std::string name, int waitTime)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(waitTime));
    std::cout << "Name (from Thread) = " << name << std::endl;
}


// the signature of the thread function is modified to take a non-const reference to the string instead.
void printNameR(std::string &name, int waitTime)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(waitTime));
    name += " (from Thread)";
    std::cout << name << std::endl;
}


int main()
{
    std::string name1 = "MyThread1";
    std::string name2 = "MyThread2";

    // starting threads using value-copy and move semantics 
    std::thread t1(printName, name1, 50);
    std::thread t2(printName, std::move(name2), 100);


    // wait for threads before returning
    t1.join();
    t2.join();

    // print name from main
    std::cout << "Name (from Main) = " << name1 << std::endl;
    std::cout << "Name (from Main) = " << name2 << std::endl;

    std::string name("MyThread");

    // When passing the string variable name to the thread function, we need to explicitly mark it as a reference, so the compiler will treat it as such. 
    // This can be done by using the std::ref function. 
    std::thread t(printNameR, std::ref(name), 50);

    t.join();

    // print name from main
    name += " (from Main)";
    std::cout << name << std::endl;

    return 0;
}