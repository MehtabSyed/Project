//
//  main.cpp
//  ParalletTransform
//
//  Created by Mehtab Ali Syed (CS) on 23/03/21.
//  Copyright © 2021 Mehtab Ali Syed (CS). All rights reserved.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;
template<typename T>
T Increment(T value)
{
    return ++value;
  
}


template<typename T,typename C>
//C ApplyFunction(C & cont)
C ApplyFunction(C & cont,std::function<T(T)> f)
{
   // typename C::value_type K;
  // std::function<int(int)> f =Increment<int>;
    C result;
    std::transform(cont.begin(), cont.end(), std::back_inserter(result), f);
    
    return result;
}


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    vector<int> vec={1,2,3};
    auto result = ApplyFunction<int>(vec,Increment<int>);
    
    copy(begin(result),end(result),ostream_iterator<int>(cout," "));
   // auto result = ApplyFunction(vec, Increment<int>);
    return 0;
}
