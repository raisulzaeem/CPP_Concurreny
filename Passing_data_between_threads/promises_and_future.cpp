#include <iostream>
#include <thread>
#include <future>

void modifyMessage(std::promise<std::string> && prms, std::string message)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(4000)); // simulate work
    std::string modifiedMessage = message + " has been modified"; 
    prms.set_value(modifiedMessage);
}

int main()
{
    // define message
    std::string messageToThread = "My Message";

    // After defining a message, we have to create a suitable promise that can take a string object.
    // create promise and future
    std::promise<std::string> prms;

    // To obtain the corresponding future, we need to call the method get_future() on the promise.
    std::future<std::string> ftr = prms.get_future();

    // start thread and pass promise as argument
    // Promises can not be copied, because the promise-future concept is a two-point communication channel for one-time use. 
    // Therefore, we must pass the promise to the thread function using std::move
    std::thread t(modifyMessage, std::move(prms), messageToThread);

    // print original message to console
    std::cout << "Original message from main(): " << messageToThread << std::endl;

    // retrieve modified message via future and print to console
    // we start listening on the other end of the communication channel by calling the function get() on the future. 
    // This method will block until data is available - which happens as soon as set_value has been called on the promise (from the thread).
    // If the result is movable (which is the case for std::string), it will be moved - otherwise it will be copied instead.
    std::string messageFromThread = ftr.get();
    // After get() has been called once, the future is no longer usable.
    // If get() is called a second time, an exception is thrown.
    std::cout << "Modified message from thread(): " << messageFromThread << std::endl;

    // thread barrier
    t.join();

    return 0;
}