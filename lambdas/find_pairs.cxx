// //Author: Bryan Kanu
// #include <vector>
// #include <iostream>
// #include <algorithm>
// #include <functional>
 
// int main()
// {
//     std::vector<int> c { 1,2,3,4,5,6,7 };
//     std::vector<int> d { 10, 20, 30, 40, 50 };
//     std::vector<int> e;
//     int x = 5;
 
//     // auto check = [](int n, int x) { return n > x; };
//     auto check2 = [](int n, std::vector<int> x,  std::vector<int> y ) 
//     { 
//         for(auto i: x)
//         { 
//             for(auto l: y)
//                 if((i*i) +  n > l) std::cout << i * i + n << " > " << l << "\n";
//         } 
 
//     };
 
//     std::cout << "c: ";
//     for (auto i: c) {
//         check2(i, c, d) ;
//     }
//     std::cout << '\n';
 
// }
//Author Bryan Kanu
#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>

void merge(std::vector<int> &, std::vector<int> &, int,int,int);
void mergesort(std::vector<int> & a, std::vector<int>& b, int low, int high)
{
    int pivot;
    if(low<high)
    {
        pivot=(low+high)/2;
        mergesort(a,b,low,pivot);
        mergesort(a,b,pivot+1,high);
        merge(a,b,low,pivot,high);
    }
}
void merge(std::vector<int> & a, std::vector<int> & b, int low, int pivot, int high)
{
    int h,i,j,k;
    h=low;
    i=low;
    j=pivot+1;
 
    while((h<=pivot)&&(j<=high))
    {
        if(a[h]<=a[j])
        {
            b[i]=a[h];
            h++;
        }
        else
        {
            b[i]=a[j];
            j++;
        }
        i++;
    }
    if(h>pivot)
    {
        for(k=j; k<=high; k++)
        {
            b[i]=a[k];
            i++;
        }
    }
    else
    {
        for(k=h; k<=pivot; k++)
        {
            b[i]=a[k];
            i++;
        }
    }
    for(k=low; k<=high; k++) a[k]=b[k];
}


int main()
{
    std::vector<int> c { 7, 23, 9, 18, 8 };
    std::vector<int> d { 28, 20, 50, 45, 11 };
    std::vector<int> e(c.size());
    int x = 5;
    
    // std::cout << "c before mergeSort: \n";
    
    // for(auto i : c)
    // {
    //  std::cout << i << ", ";
    // }
    // std::cout <<"\n";
    mergesort(c,e,0,c.size());
    
    // std::cout << "c after mergeSort: \n";
    
    // for(auto i : c)
    // {
    //  std::cout << i << ", ";
    // }

    std::make_heap(d.begin(), d.end());
    // auto check = [](int n, int x) { return n > x; };
    auto check2 = [](int n, std::vector<int> x,  std::vector<int> y ) 
    { 
        for(auto i: x)
        { 
            for(auto l: y)
                if((i*i) +  n > l) std::cout << i * i + n << " > " << l << "\n";
        } 
            
    };
    
    std::cout << "c: ";
    for (auto i: c)
    {
        check2(i, c, d);
    }
    std::cout << '\n';
 
}