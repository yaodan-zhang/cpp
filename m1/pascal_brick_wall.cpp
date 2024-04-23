/*
This program uses "brick-wall" formatting to print out the first 8 rows of Pascal's triangle,
in which the numbers of each row are presented interleaved with the numbers on the rows above and below.

The brick size is the maximum size of any integer in the triangle, and the number is centered on its brick.
*/

#include<vector>
#include<iostream>
#include <tuple>
#include <cmath>
#include <format>
#define FMT_HEADER_ONLY
using namespace std;

// Input the number of lines n of the Pascal's triangle.
// Return the Pascal's triangle as a nested vector and the max number of digit an
// element can have in this triangle.
std::tuple <vector<vector<int>>, int> PascalTriangle (int n) {
    if (n == 1) return {{{1}}, 1};
    else if (n == 2) return {{{1}, {1,1}}, 1};
    
    vector<vector<int>> triangle = {{1}, {1,1}};
    int max_digit = 1;
    // Add remaining lines starting from the third line to the triangle.
    
    for (int i = 2; i < n; i++)
    {
        vector<int> line = {1}; // left boundary

        int new_number;
        // Add intermediate elements based on the previous line in the triangle.
        for (int j = 0; j < (triangle[i-1].size()-1); j++)
        {
            new_number = triangle[i-1][j] + triangle[i-1][j+1];
            line.push_back(new_number);
            max_digit = max (max_digit, ((int) log10((double) new_number)) + 1);
        }

        // right boundary
        line.push_back(1);

        triangle.push_back(line);
    }

    // Make the max_digit odd for asthetic purposes.
    return {triangle, max_digit % 2 == 0? (max_digit + 1): (max_digit + 2)};
}

int main() {
    int num_of_lines = 12;
    
    auto [PascalsTriangle, maxDigit] = PascalTriangle (num_of_lines);
    int indent = maxDigit/2; // Half of the brick-size for interleave formatting

    for (int i = 0; i < PascalsTriangle.size(); i++)
    {
        for (int space = 0; space < ((num_of_lines - i - 1) * indent); space++)
        {
            cout << " ";
        }
        for (int element : PascalsTriangle[i])
        {
            cout << format("{:^{}}", element, maxDigit);
        }
        cout << endl;
    }
    return 0;
}