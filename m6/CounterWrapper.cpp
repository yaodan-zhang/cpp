/*Create a Counter class template wrapper that can
be used to count calls to any function.*/
#include<iostream>
#define FMT_HEADER_ONLY
#include <format>
using namespace fmt;
using namespace std;

template <typename F> 
class Counter{
    public:
    Counter(F f): _impl(f){
        count = 0;
    }
    int count;
    auto operator()(auto && ...args)
    {
        count += 1;
        return _impl(forward<decltype(args)>(args)...);
    }
    private:
        F _impl;
};

int f(double d) { 
    return static_cast<int>(2*d);
}

Counter cf(f);

int main()
{
    cf(1.3);
    cf(2.4);
    cout << format("f was called {} times\n", cf.count);
    return 0;
}