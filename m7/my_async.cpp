/*
Uses std::packaged_task to create my own implementation of async.
We don't do a join when using async because we don't want to wait until the thread is complete,
we only need a guarantee that it will be returned somewhere in the future (or throw an exception).
*/

#include <thread>
#include <future>
#include <functional>
#include <iostream>

template<typename Func, typename ...Args>
auto my_async(Func f, Args... args) {
    using RetType = decltype(f(args...));

    std::packaged_task<RetType(Args...)> task {f};

    auto result = task.get_future();

    // Create a thread
    std::thread t(std::move(task), args...);
    // Run the thread independently
    t.detach();

    return move(result);
}

size_t calculateSomething(size_t x,size_t y) {
    size_t sum = 0;
    for (size_t i=0;i<1000'000'000;i++){
        sum += x*y*i;
    }
    return sum;
}

// A value that may overflow, we only want to consider the return time
// to demonstrate the future usage, so we ignore the accuracy of the result.
size_t calculateSomethingElse(size_t x,size_t y,size_t z) {
    size_t sum = 0;
    for (size_t i=0;i<10'000'000'000;i++){
        sum += x*y*z*i;
    }
    return sum;
}

int main(){
    auto a = my_async(calculateSomething, 4,3);
    auto b = my_async(calculateSomethingElse, 7,8,9);
    std::cout << "before the calculations are done..." << std::endl;
    std::cout << a.get() << std::endl;
    std::cout << b.get() << std::endl;
    return 0;
}