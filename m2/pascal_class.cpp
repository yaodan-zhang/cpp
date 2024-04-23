/*
    This program makes Pascal's triangle into a class.
    Object-oriented programming style.
*/
#include <vector>
#include <numeric>
#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <format>
using namespace std;

using Row = vector<int>; // Row is a synonym for vector<int>
// typedef vector<int> Row;  // Old-fashioned version
using Triangle = vector<Row>;

class Pascal_Triangle {
    friend ostream& operator << (ostream& os, Pascal_Triangle const &pascalTriangle);
    
    private:
        int rows;
        Triangle triangle;

    public:
        Pascal_Triangle (int rows) {this->rows = rows;}
        Row nextRow (Row row);
        void constructTriangle ();
        int numDigits (int i);
        void printRow (ostream& os, Row row, int eltSize); 
};

Row Pascal_Triangle::nextRow(Row row) {
    Row result;
    int previous = 0;
    for (auto elt : row) {
        result.push_back(previous + elt);
        previous = elt;
    }
    result.push_back(previous);
    return result;
}

void Pascal_Triangle::constructTriangle() {
    Row previousRow = { 1 };
    for (int i = 0; i < rows; i++) {
        triangle.push_back(previousRow);
        previousRow = nextRow(previousRow);
    }
}

int Pascal_Triangle::numDigits(int i) {
    return std::to_string(i).size();
}

void Pascal_Triangle::printRow(ostream& os, Row row, int eltSize) {
    for (auto elt : row) {
        os << format("{:^{}}", elt, eltSize) << " ";
    }
    os << endl;
}

// Type safe
ostream& operator <<(ostream& os, Pascal_Triangle const &pascalTriangle) {
    int rows = pascalTriangle.rows;
    Row lastRow = pascalTriangle.triangle[rows - 1];

    int maxElement = *max_element(lastRow.begin(), lastRow.end());
    int eltSize = pascalTriangle.numDigits(maxElement);
    for (int i = 0; i < rows; i++) {
        string spaces((rows - i - 1) * (eltSize + 1) / 2, ' ');
        os << spaces;
        pascalTriangle.printRow(os, pascalTriangle.triangle[i], eltSize);
    }
    return os;
}


int main() {
    int constexpr rows = 18;

    Pascal_Triangle triangle(rows);

    triangle.constructTriangle();

    cout << triangle;

    return 0;
}
