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

int binarySum(vector<int> A, int i, int n)//page 144
{
    if(n == 1)
        return A[i];
        
    return (binarySum(A, i, (n/2)) + binarySum(A, i + (n/2), (n/2)));
}

int main()
{

    vector<int> A;
    A.push_back(10);
    A.push_back(23);
    
    vector<int> B;
    B.push_back(9);
    B.push_back(18);

    cout << "Linear Sum: " << linearSum(A, 3) << "\n";
    cout << "Binary Sum: " << binarySum(B, 0, 2) << "\n";
    
    return 0;
}