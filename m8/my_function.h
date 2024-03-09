/*Use type erasure to create my own
implementation of std::function.
This is the most difficult homework for the course.*/
#ifndef MY_FUNC_H
#define MY_FUNC_H
#include <any>
#include <utility>
#include <type_traits>
#include <memory>
using namespace std;

namespace mpcs {
template<typename ReturnType, typename ... Args>
class abstractWrapper {
    public:
    virtual ~abstractWrapper() {}
    virtual ReturnType funcCall(Args ...args) = 0;
};

template <typename T, typename ReturnType, typename ...Args>
class funcWrapper : public abstractWrapper<ReturnType, Args...>{
public:
  funcWrapper(T t): t_(t) {}
  ~funcWrapper(){}
  ReturnType funcCall(Args ...args) {
    ReturnType res = t_(args...);
    return res;
  }
private:
  T t_;
};

template<typename T>
class my_function;

template<typename ReturnType, typename ...Args>
class my_function<ReturnType(Args...)> {
    public:
    template<typename T>
    my_function (T f) {
        callable = make_unique<funcWrapper<T, ReturnType, Args...>>(f);
    }
    ReturnType operator() (Args ...args) {
        /*if (is_same<ReturnType, void>::value) {
            callable->funcCall(args...);
            return;
        } else {*/
            ReturnType result = callable->funcCall(args...);
            return result;
        }
    //}
    private:
    unique_ptr<abstractWrapper<ReturnType,Args...>> callable;
};
}

#endif