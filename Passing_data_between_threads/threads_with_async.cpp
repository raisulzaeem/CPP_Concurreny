#include <iostream>
#include <thread>
#include <future>
#include <cmath>
#include <memory>

double divideByNumber(double num, double denom)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(500)); // simulate work

    if (denom == 0)
        throw std::runtime_error("Exception from thread: Division by zero!");

    return num / denom;
}


int main()
{
    // use async to start a task
    double num = 42.0, denom = 2.0;
    std::future<double> ftr = std::async(divideByNumber, num, denom); // async returns a future

    // with std::async, the system decides wether the associated function should be run asynchronously or synchronously. 
    // By adjusting the launch parameters of std::async manually, we can directly influence wether the associated thread function will be executed synchronously or asynchronously.

    // std::future<double> ftr = std::async(std::launch::deferred, divideByNumber, num, denom); --> synchronously
    // std::future<double> ftr = std::async(std::launch::async, divideByNumber, num, denom); --> asybchronously

    // retrieve result within try-catch-block
    try
    {
        double result = ftr.get();
        std::cout << "Result = " << result << std::endl;
    }
    catch (std::runtime_error e)
    {
        std::cout << e.what() << std::endl;
    }

    // Also, we do not need to call join() any more. With async, the thread destructor will be called automatically
    // - which reduces the risk of a concurrency bug.

    return 0;
}