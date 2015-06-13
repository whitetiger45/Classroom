//algorithm from Data Structures and Algorithms in C++
//Michael T. Goodrich * Roberto Tamassia * David Mount
//Page 141
#include <iostream>
#include <vector>

using namespace std;

int linearSum(vector<int> A, int n)
{
    if (n == 1)
        return A[0];
        
    else
        return (linearSum(A, n-1) + A[n- 1]);
}

int main()
{

    vector<int> A;
    A.push_back(10);
    A.push_back(23);

    cout << "Sum: " << linearSum(A, 3) << "\n";
    
    return 0;
}