#include <vector>
#include <iostream>
#include "vector.hpp"
using namespace std; 

int main()
{
    std::vector <int> v(5,9);
    ft::vector <int> a(5,9);
    ft::vector <int> d(5,4);
    ft::vector<int>::iterator it = a.begin();
    ft::vector<int>::iterator it2 = a.end();
    ft::vector<int> b(it,it2);
    // v.reserve(10);
    // a.reserve(10);
    d.assign(5,9);
    //d.assign(it, it2);
    v.push_back(1);
    a.push_back(1);
    b.push_back(1);
    d.push_back(1);
    cout << "ft: " << v.capacity() << " " << v.size() << endl;
    cout << "std: " << a.capacity() << " " << a.size() << endl;
    cout << "std::it: " << a.capacity() << " " << a.size() << endl;
    for (size_t i = 0; i < v.size(); i++)
    {
        cout << v[i] << a[i] << b[i] << d[i] << endl;
    }
}