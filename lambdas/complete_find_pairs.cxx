//Author Bryan Kanu
//mergesort algorithm from http://simplestcodings.blogspot.com/2010/08/merge-sort-implementation-in-c.html
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
    std::vector<int> c { 7, -8, 9, 18, -14 };
    std::vector<int> d { -18, -9, 14, -7, 8 };
    std::vector<int> e(c.size()+1);
    
    std::cout << "c before mergeSort: \n";
    
    for(auto i : c)
    {
     std::cout << i << ", ";
    }
    std::cout <<"\n";
    
    mergesort(c,e,0,c.size()-1);
    
    std::cout << "c after mergeSort: \n";
    
    for(auto i : c)
    {
     std::cout << i << ", ";
    }

    std::make_heap(d.begin(), d.end());
    auto check= [](int a, std::vector<int> b) 
    { 
        for(auto i: b)
        { 
            if((a+i) == 0) std::cout << a  << " + " << i << " = 0\n";
        } 
            
    };
    
    std::cout << "\n\nFind Pairs:\n";
    for (auto i: c)
    {
        check(i, d);
    }
    std::cout << '\n';
 
}