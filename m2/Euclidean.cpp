/*This program investigates the naive approach, using inner product, and using std::accumilate 
to calculate vector length. */
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

// Define a unary operation for raising to the power of 2.
// The usage is in transform() in Part 1.
inline double pow2 (double a) {return a * a;}

// Define a binary operation for the 4-argument version of std::accumulate used in Part 2.
inline double myBinaryOp (double a, double b) {return a + pow2(b);}

int main () {
    double input;

    vector<double> V;
    vector<double> squared_V;

    cout << "Enter the content of a double-type vector, with one double at a time:" << endl;
    cout << "(Press q to end)" << endl;

    // Get the input vector from the user.
    while (cin >> input) {
        V.push_back(input);
    }

    // Part 1
    // Square the input vector.
    squared_V.resize(V.size());

    transform(V.begin(), V.end(), V.begin(), squared_V.begin(), multiplies<double>());
    //transform(V.begin(), V.end(), squared_V.begin(), pow2);

    cout << "The vector before squared: " << endl;

    cout << "{" ;
    for (auto v : V) {
        cout << v << ", ";
    }
    cout << "}";

    /*for (vector<double>::iterator i = V.begin(); i != V.end(); ++i){
        std::cout << *i << ", ";
    }*/
    
    cout << endl;

    cout << "The vector after squared: " << endl;

    cout << "{";
    for (auto sv : squared_V) {
        cout << sv << ", ";
    }
    cout << "}";

    /*for (vector<double>::iterator si = squared_V.begin(); si != squared_V.end(); ++si){
        std::cout << *si << ", ";
    }*/

    cout << endl;

    // Part 2
    // Calculate the Euclidean distance of the vector from the origin.
    double dis1;
    dis1 = sqrt (accumulate (squared_V.begin(), squared_V.end(), 0.0));

    // A simple way using inner product.
    double dis2;
    dis2 = sqrt (inner_product (V.begin(), V.end(), V.begin(), 0.0));

    // Another simpler way using the 4-argument accumulate
    double dis3;
    dis3 = sqrt (accumulate (V.begin(), V.end(), 0.0, myBinaryOp));

    cout << "The distance between the vector and the origin is " << dis3 << "." << endl;

    return 0;
}