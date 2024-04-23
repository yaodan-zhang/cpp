/* 
This program leverages constructors to print something with an empty main().
*/
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