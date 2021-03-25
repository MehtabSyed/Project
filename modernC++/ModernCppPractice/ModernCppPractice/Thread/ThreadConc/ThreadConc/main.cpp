//
//  main.cpp
//  ThreadConc
//
//  Created by Mehtab Ali Syed (CS) on 01/03/21.
//  Copyright © 2021 Mehtab Ali Syed (CS). All rights reserved.
//

#include <iostream>
#include <thread>
#include <chrono>
#include <iomanip>
#include <mutex>
#include <vector>
#include <algorithm>
#include <list>
using namespace std;
void print_time()
{
    auto now = std::chrono::system_clock::now();
    auto stime = std::chrono::system_clock::to_time_t(now);
    auto ltime = std::localtime(&stime);
    
    std::cout << std::put_time(ltime,"%c") << std::endl;
}

void func3(int &i)
{
    using namespace std::chrono;
    i*=2;
    print_time();
    std::this_thread::sleep_for( 5s);
    print_time();
}
// This is an example of handling thread concurrency and moving elements betweeen list
template<typename T>
class Container
{
public:
    mutex m;
    vector<T> vec;
};
template<typename T>
void move_between(Container<T>& c1 ,Container<T>& c2,const T value)
{
    scoped_lock lock(c1.m,c2.m);
    c1.vec.erase(
                  remove(c1.vec.begin(), c1.vec.end(), value),
                 c1.vec.end());
    cout << "Pushing value :" << value << endl;
    c2.vec.push_back(value);
    
    
}
template<typename Container>
void print(const Container & container)
{
    copy(container.begin(),container.end(),ostream_iterator<typename Container::value_type >(cout, " "));
    cout << endl;
}

void DemoMoveElemenets()
{
    Container<int>  c1;
    Container<int>  c2;
    
    
    c1.vec.push_back(1);
    c1.vec.push_back(2);
    c1.vec.push_back(3);
    c2.vec.push_back(4);
    c2.vec.push_back(5);
    c2.vec.push_back(6);
    
    thread t1(move_between<int>,std::ref(c1) ,std::ref(c2),2);
    
    thread t2(move_between<int>, std::ref(c2), std::ref(c1),5);
    t1.join();
    t2.join();
    
    print(c1.vec);
    print(c2.vec);
    
    
    
}
template<typename Cont,typename T>
void remove_elements(Cont& container,std::function<bool(T &value)> Comp)
{
    auto itr = std::remove_if(begin(container), end(container), Comp);
    container.erase(itr,end(container));
}


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    vector<int> vec = {1,2,3,4,5,6};
        
    auto fn =[](auto val){return ((val %2)==0);};
    
  //  remove_elements(vec, fn);
   
    
    print(vec);
    
    list<int> l = {1,2,3,4,5,6};
 /*
    remove_elements<int>(l, fn);
    print<int>(l);
   */
    DemoMoveElemenets();
    int i =6;
    std::thread t(func3,std::ref(i));
    t.join();
    std::cout << "Value of i i " << i << endl;
    
    
    return 0;
}
