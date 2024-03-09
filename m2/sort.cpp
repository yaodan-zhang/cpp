/*This program investigates the performance of different sorting functions to a vector.
The goal is to get the median of the vector. */
#include<algorithm>
#include<iostream>
using namespace std;

// Part 1 : Sort the vector naively
double median_sort (vector<double> v) {
    sort(v.begin(), v.end());
    int n = v.size();
    return n%2 == 0? (v.at(n/2-1)+v.at(n/2))/2 : v.at(n/2);
}

// Part 2: Using partial sort
// It should be more efficient than sort because only the first half
// of the vector is sorted.
double median_partial_sort (vector<double> v) {
    int n = v.size();
    partial_sort (v.begin(), v.begin() + (n/2) + 1, v.end());
    return n%2 == 0? (v.at(n/2-1)+v.at(n/2))/2 : v.at(n/2);
}

// Part 3: nth_element
// It should be the most efficient algorithms among all three sorting algorithms
// because it only sorts the nth element.
double median_nth_element (vector<double> v) {
    int n = v.size();
    nth_element(v.begin(), v.begin() + n/2, v.end());
    nth_element(v.begin(), v.begin() + n/2 - 1, v.end());
    return n%2 == 0? (v.at(n/2-1)+v.at(n/2))/2 : v.at(n/2);
}

// Part 4: template function
template <class T>
T median_template (vector<T> v) {
    sort(v.begin(), v.end());
    int n = v.size();
    return n%2 == 0? (v.at(n/2-1)+v.at(n/2))/2 : v.at(n/2);
}

int main () {
    double input;
    vector<double> V;

    cout << "Enter the content of a double-type vector, with one element at a time:" << endl;
    cout << "(Press q to end)" << endl;

    // Create the vector.
    while (cin >> input) {
        V.push_back(input);
    }

    cout << "The median of the vector is " << median_template(V) << endl;

    return 0;
}