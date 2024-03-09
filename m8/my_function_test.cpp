#include"my_function.h"
#include<iostream>
using namespace mpcs;

double num(int i)
{
    return double(i) + 0.35;
}

int main()
{
    my_function<int(int)> f = [](int i) { return i * i; };
    std::cout << f(4);
}