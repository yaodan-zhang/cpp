/*
    Use Compile-Time Regular Expressions to extract decimals from a set of numbers.

References:
1.https://compile-time-regular-expressions.readthedocs.io/en/latest/api.html
2.https://compile-time-regular-expressions.readthedocs.io/en/latest/examples.html
*/

#include <iostream>
#include <string_view>
#include <ctre.hpp>

int main() {
    // The input set of numbers
    std::string_view input = "Here are some numbers: 1.23, 4, 5.6, 7.89";

    // Loop through matches and print out the decimals as:
    //1 is before the decimal and 23 is after the decimal
    //5 is before the decimal and 6 is after the decimal
    //7 is 