/*Uses std::promise to create my own
implementation of std::packaged_task*/
#include<thread>
#include<future>
#include<iostream>
#include<stdexcept>
using std::forward;

//Make this part into a header file
namespace mpcs {
template<typename T> // How my_packaged_task is called.
class my_packaged_task;

// Define a specialization.
template<typename R, typename ...Args>
class my_packaged_task<R(Args...)> {
    //Any callable using Args... and returns an R type, e.g. a functor
    using Func = std::function<R(Args...)>;

    public:
    template<typename T> // Can't assume the type passed into the constructor
    my_packaged_task(T &&t) : callable(forward<T>(t)) {}
    //my_packaged_task(Func f) : callable(f){}

    void operator()(Args ...args){
        try{
            result.set_value(callable((args)...));
        }
        catch (...){
            result.set_exception(std::current_exception());
        }
    }
    std::future<R> get_future(){
        // The compiler can tell this is end of the life time and return a move
        return result.get_future();
    }

    private:
    Func callable;
    std::promise<R> result;
};
};

using namespace mpcs;

size_t calculateSomething(size_t x,size_t y) {
    size_t sum = 0;
    for (size_t i=0;i<1000'000'000;i++){
        sum += x*y*i;
    }
    return sum;
}

int main(){
    my_packaged_task<size_t(size_t,size_t)> task(calculateSomething);
    std::future<size_t> result = task.get_future();
    std::cout << "before calculation is done..." << std::endl;
    task(4,3);
    std::cout << result.get() << std::endl;
    return 0;
}