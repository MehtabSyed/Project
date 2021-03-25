//
//  main.cpp
//  VariadicTemplates
//
//  Created by Mehtab Ali Syed (CS) on 14/03/21.
//  Copyright © 2021 Mehtab Ali Syed (CS). All rights reserved.
//

#include <iostream>
#include <tuple>
using namespace std;

template<typename... T>
auto make_even_tuple(T... a)
{
    static_assert(sizeof...(a)%2 ==0,"Expected even number of arguments");
    std::tuple<T...> t {a...};
    return t;
}

template<typename T>
T add(T value)
{
    return value;
}
template<typename T,typename... Ts>
T add(T head,Ts... rest)
{
return head + add(rest...);

}


template<typename T,typename... Ts>
T add2(Ts... rest)
{
    return (... + rest);

}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    auto t1 = make_even_tuple(1,2,3,4);
    
    cout << get<0>(t1)  <<endl;
    
    int x = add(1,2,3,4);
    
    cout << "Value of x :" << x << endl;
    
    int y = add(5,5,5);
    cout << "Value of y :" << y << endl;
  //  auto t2 = make_even_tuple(1,2,3);
    return 0;
}
