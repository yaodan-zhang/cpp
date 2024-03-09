// This program prints out the first 8 rows of Pascal's triangle without formatting.

#include<vector>
#include<iostream>
using namespace std;

// Input the number of lines n of the Pascal's triangle.
vector<vector<int>> PascalTriangle (int n) {
    if (n == 1) return {{1}};
    else if (n == 2) return {{1}, {1,1}};
    
    vector<vector<int>> triangle = {{1}, {1,1}};
    // Add remaining lines starting from the third line to the triangle.
    
    for (int i = 2; i < n; i++)
    {
        vector<int> line = {1}; // left boundary

        // Add intermediate elements based on the previous line in the triangle.
        for (int j = 0; j < (triangle[i-1].size()-1); j++)
        {
            line.push_back(triangle[i-1][j] + triangle[i-1][j+1]);
        }

        // right boundary
        line.push_back(1);

        triangle.push_back(line);
    }

    return triangle;
}

int main() {
    int num_of_lines = 8;
    
    vector<vector<int>> PascalsTriangle = PascalTriangle (num_of_lines);

    for (int i = 0; i < PascalsTriangle.size(); i++)
    {
        for (int element : PascalsTriangle[i])
        {
            cout << element << " ";
        }
        cout << endl;
    }
    return 0;
}