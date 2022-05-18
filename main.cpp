#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include "vector.hpp"
// #include "map/RB_tree.hpp"
// #include "map/map.hpp"
#include "pair.hpp"

struct select_first
{
    template<class T>
      T operator()(const T& t)
      {
         return t.first;
      }
};

struct select_self
{
    template<class T>
      T operator()(const T& t)
      {
         return t;
      }
};


#include <time.h>

int main()
{
   std::map<int,int>::const_iterator;
   a.insert(ft::make_pair(1,1));
   ft::map<int,int>::iterator it = a.begin();
  ft::vector<ft::pair> v;

}

