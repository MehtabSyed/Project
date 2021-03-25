//
//  main.cpp
//  AnyAllNoneContainer
//
//  Created by Mehtab Ali Syed (CS) on 14/02/21.
//  Copyright © 2021 Mehtab Ali Syed (CS). All rights reserved.
//

#include <iostream>
#include <vector>


template<typename Container,typename C>
bool contains(Container & cont, C& value)
{
    auto ret= std::any_of(begin(cont),end(cont),[&value](C i){ return i==value;} );
    return ret;
}

template<typename Container,typename... Args>
bool contains_any(Container& cont,Args&&... t1)
{
    auto ret= (contains(cont,t1)||...);
    
    return ret;
}
template<typename Container,typename... Args>
bool  contains_all(Container && cont,Args&&... t1)
{
    auto ret=(contains(cont,t1)&&...);
    return ret;
}
template<typename Container,typename... Args>
bool contains_none(Container && cont, Args&&... t)
{
    auto ret =!(contains_any(cont,std::forward<Args>(t)...));
    return ret;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    std::vector<int> vec= {1,2,3};
    auto ret = contains_any(vec, 3,6);
    assert(ret);
    ret = contains_all(vec,2,3);
    assert(ret);
    assert(contains_none(vec, 4,6,7));
   // assert(contains_any(vec,4,5));
    return 0;
}
