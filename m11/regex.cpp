/*

    Use std::regex to extract decimals from a set of numbers.

References: 
1.https://en.cppreference.com/w/cpp/regex/match_results/operator_at
2.https://en.cppreference.com/w/cpp/language/string_literal
3.https://www.freecodecamp.org/news/what-does-b-in-regex-mean-word-boundary-and-non-word-boundary-metacharacters/#howtousethewordboundarybmetacharacter
4.https://en.cppreference.com/w/cpp/regex/regex_iterator
*/
#include <iostream>
#include <string>
#include <regex>

// Remark: Compare runtime with ctre which should be faster since it's compile-time, use -O2 for compiler optimization (production)

int main() {
    // The input set of numbers
    std::string input = "Here are some numbers: 1.23, 4, 5.6, 7.89";

    // Regular expression pattern for a decimal with capture groups
    std::regex pattern(R"(\b(\d+)\.(\d+)\b)");

    // Iterator for matching
    std::sregex_iterator iter(input.begin(), input.end(), pattern);
    auto end = std::sregex_iterator();

    // Loop through matches and print out the decimals as:
    //1 is before the decimal and 23 is after the decimal
    //5 is before the decimal and 6 is after the decimal
    //7 is before the decimal and 89 is after the decimal
    while (iter != end) {
        std::smatch match = *iter;
        std::cout << match[1] << " is before the decimal and " << match[2] << " is after the decimal" << std::endl;
        ++iter;
    }

    return 0;
}
