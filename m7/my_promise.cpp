/*Uses a std::condition_variable to create my own versions of promise and future. */
#include <thread>
#include <iostream>
#include <mutex>
#include <condition_variable>
#include <exception>
#include <stdexcept>
using namespace std;

// my_future using condition variable
template<typename T>
class my_future{
    public:
    my_future(
        shared_ptr<mutex> ptrM, 
        shared_ptr<condition_variable> ptrCond,
        shared_ptr<T> ptrData,
        shared_ptr<bool> ptrReady,
        shared_ptr<exception_ptr> pExcept
    ){
        pMutex = ptrM;
        pCond = ptrCond;
        pData = ptrData;
        pReady = ptrReady;
        eptr = pExcept;
    }

    T get(){
        try
        {
            if (*eptr) {
                std::rethrow_exception(*eptr);
            } else {
                unique_lock<mutex> lk(*pMutex);
                (*pCond).wait(lk,[this]{return *(this->pReady);});
                return *pData;
            }
        }
        catch(const exception& e)
        {
            cout << "Caught exception: '" << e.what() << "'\n";
        }
    }

    private:
    shared_ptr<mutex> pMutex;
    shared_ptr<condition_variable> pCond;
    shared_ptr<T> pData;
    shared_ptr<bool> pReady;
    shared_ptr<exception_ptr> eptr;
};

// my_promise using cond
template<typename T>
class my_promise{
    public:
    my_promise(){
        pMutex = make_shared<mutex>();
        pCond = make_shared<condition_variable>();
        pData = make_shared<T>();
        pReady = make_shared<bool>(false);
        eptr = make_shared<exception_ptr>(nullptr);
    }
    my_future<T> get_future(){
        my_future<T> f(pMutex,pCond,pData,pReady,eptr);
        return move(f);
    }

    void set_value(T t){
        try
        {
            lock_guard lk(*pMutex);
            (*pData) = t;
            (*pReady) = true;
            (*pCond).notify_all();
        }
        catch(...)
        {
            *eptr = std::current_exception(); // capture
        }
    }

    private:
    shared_ptr<mutex> pMutex;
    shared_ptr<condition_variable> pCond;
    shared_ptr<T> pData;
    shared_ptr<bool> pReady;
    shared_ptr<exception_ptr> eptr;
};

size_t calculateSomething(size_t x,size_t y) {
    size_t sum = 0;
    for (size_t i=0;i<1000'000'000;i++){
        sum += x*y*i;
    }
    return sum;
}

int main(){
    my_promise<size_t> p;
    my_future<size_t> fi = p.get_future();

    cout << "before the value is set..." << endl;

    //Calculate the value in another thread and set it in the promise
    thread t(&my_promise<size_t>::set_value, p, calculateSomething(2,3));

    cout << "received " << fi.get() << endl;

    t.join();
}