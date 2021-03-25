//
//  main.cpp
//  RangeAdd
//
//  Created by Mehtab Ali Syed (CS) on 14/02/21.
//  Copyright © 2021 Mehtab Ali Syed (CS). All rights reserved.
//

//Write a general-purpose function that can add any number of elements to the end of a container that has a method push_back(T&& value).
//
//Bancila, Marius. The Modern C++ Challenge: Become an expert programmer by solving real-world problems (p. 30). Packt Publishing. Kindle Edition.

#include <iostream>
#include <vector>
#include <iterator>
template<typename Container, typename T>
void push_back(Container & Cont,T & val)
{
    Cont.push_back(val);
}

template<typename Container ,typename T, typename... Args>
void push_back1(Container& cont, T t1, Args&&... t2)
{
    cont.push_back(t1);
    push_back(cont, t2...);
}
// Push back using fold expression
template<typename Container , typename... Args>
void push_back(Container& cont,Args&&... t2)
{
    (cont.push_back(t2),...);
    //push_back(cont, t2...);
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    std::vector<int> vec = {1,2,3};
    
    push_back(vec, 2,3,4);
    
    std::copy(begin(vec),end(vec),std::ostream_iterator<int>(std::cout," "));
    return 0;
}
