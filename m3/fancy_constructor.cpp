/* This program leverages constructor to print without using anything in the main function.*/
#include "fancy_constructor.h"
using namespace mpcs51044;

struct A {
A() { std::cout << "Hello, world!" << std::endl;}
};
static A static_a;

// Empty main
int
main()
{
return 0;
}