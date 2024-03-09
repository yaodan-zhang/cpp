/* std::optional version of my_promise.h */
#ifndef MY_PROMISE_OPTIONAL_H
#  define MY_PROMISE_OPTIONAL_H
#include<memory>
#include<thread>
#include<mutex>
#include<condition_variable>
#include<exception>
#include<stdexcept>
#include <optional>
using std::shared_ptr;
using std::unique_ptr;
using std::make_shared;
using std::make_unique;
using std::move;
using std::mutex;
using std::condition_variable;
using std::lock_guard;
using std::unique_lock;
using std::exception_ptr;
using std::rethrow_exception;
using std::runtime_error;
using std::optional;

namespace mpcs {
template<class T> class MyPromise;

enum class State { empty, ready };

template<class T>
struct SharedState {
  State state{State::empty};
  optional<unique_ptr<T>> value;
  exception_ptr exception;
  mutex mtx;
  condition_variable cv;
};

template<typename T>
class MyFuture {
public:
  MyFuture(MyFuture const &) = delete; // Delete the copy constructor because we only want it from a promise
  MyFuture(MyFuture &&) = default; 
  // MyFuture(MyFuture &&other) : sharedState{move(other.sharedState)} {}
  T get() {
    unique_lock lck{sharedState->mtx};
    sharedState->cv.wait(lck, 
		[&] {return sharedState->state == State::ready; });
    if (sharedState->value) {
        return *sharedState->value.value();
    }
    rethrow_exception(sharedState->exception);
  }
private:
  friend class MyPromise<T>;
  MyFuture(shared_ptr<SharedState<T>> &sharedState) 
	  : sharedState(sharedState) {}
  shared_ptr<SharedState<T>> sharedState;
};

template<typename T>
class MyPromise
{
public:
  MyPromise() : sharedState{make_shared<SharedState<T>>()} {}

  void set_value(const T &value) {
    lock_guard lck(sharedState->mtx);
    try
    {
      sharedState->value = make_unique<T>(value);  
    }
    catch(...)
    {
      sharedState->exception = std::current_exception();
    }
    sharedState->state = State::ready;
    sharedState->cv.notify_one();
  }

  void set_exception(exception_ptr exc) {
    lock_guard lck(sharedState->mtx);
    sharedState->exception = exc;
    sharedState->state = State::ready;
    sharedState->cv.notify_one();
  }

  MyFuture<T> get_future() {
    return sharedState;
  }
private:
  shared_ptr<SharedState<T>> sharedState; 
};
}
#endif
