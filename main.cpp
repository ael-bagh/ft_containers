#include <vector>
#include <iostream>
#include "vector.hpp"
using namespace std; 

int main()
{
    ft::vector <int> v(5,9);
    ft::vector <int> a(5,9);
    // v.reserve(10);
    // a.reserve(10);
    v.push_back(1);
    a.push_back(1);    
    cout << "ft: " << v.capacity() << " " << v.size() << endl;
    cout << "std: " << a.capacity() << " " << a.size() << endl;
    for (size_t i = 0; i < v.size(); i++)
    {
        cout << v[i] << a[i] << endl;
    }
}