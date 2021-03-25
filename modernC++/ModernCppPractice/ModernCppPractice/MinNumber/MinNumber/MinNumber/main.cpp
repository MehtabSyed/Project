//
//  main.cpp
//  MinNumber
//
//  Created by Mehtab Ali Syed (CS) on 14/02/21.
//  Copyright © 2021 Mehtab Ali Syed (CS). All rights reserved.
//

//Minimum function with any number of arguments Write a function template that can take any number of arguments and returns the minimum value of them all, using operator < for comparison. Write a variant of this function template that can be parameterized with a binary comparison function to use instead of operator <.
//
//Bancila, Marius. The Modern C++ Challenge: Become an expert programmer by solving real-world problems (p. 30). Packt Publishing. Kindle Edition.

#include <iostream>
template <typename T>
T minimum(T const a, T const b) { return a < b ? a : b; }

template <typename T1, typename... T>
T1 minimum(T1 a, T... args)
{
   return minimum(a, minimum(args...));
}



template<class Compare,typename T>
T MinNumber(Compare Comp,T const t1,T const t2)
{
    return Comp(t1 ,t2) ? t1 : t2;
 //   std::cout << "I am empty function and "
   //         "I am called at last.\n" ;
}
template<class Comp,typename T,typename ... Types>
T MinNumber(Comp comp,T var, Types ...arg2)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl ;
    return MinNumber(comp,var ,MinNumber(comp,arg2...));
}

template <class Compare, typename T>
T minimumc(Compare comp, T const a, T const b) {
    return comp(a, b) ? a : b;
}
 template <class Compare, typename T1, typename... T>
T1 minimumc(Compare comp, T1 a, T... args){
   return minimumc(comp, a, minimumc(comp, args...));
}



int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    auto minNos = std::numeric_limits<long>::max();
    
    std::cout << "Min number  " << MinNumber(std::less<>(),1,5,2,3) << std::endl;
    
    auto x = minimum(5, 4, 2, 3);

    std::cout << "X is " << x << std::endl;
    
    auto y = minimumc(std::less<>(), 3, 2, 1, 8);

    std::cout << "Y is " << y << std::endl;
    
    return 0;
}
