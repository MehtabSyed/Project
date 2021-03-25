//
//  main.cpp
//  Atomic
//
//  Created by Mehtab Ali Syed (CS) on 06/03/21.
//  Copyright © 2021 Mehtab Ali Syed (CS). All rights reserved.
//

#include <iostream>
#include <atomic>
#include <vector>
#include <thread>

using namespace std;

void AtomicCounter()
{
    std::atomic<int> counter= {0};
       
       vector<thread> threads;
       
       for(int i =0;i < 10;++i)
       {
           threads.emplace_back([&counter](){
               for(int i =0 ;i< 10;++i)
                   ++counter;
           });
       }
       
       for(auto &t:threads)
           t.join();
       
    cout << "Counter is " << counter << endl;
}
void AtomicFlag()
{
    atomic_flag lock = ATOMIC_FLAG_INIT;
    int counter = 0;
       vector<thread> threads;
       
       for(int i =0;i < 10;++i)
       {
           threads.emplace_back([&](){
               while(lock.test_and_set(memory_order_acquire));
                   ++counter;
               lock.clear(memory_order_release);
           });
       }
       
       for(auto &t:threads)
           t.join();
       
    cout << "Atomic Flag Counter is " << counter << endl;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    AtomicFlag();
    
    AtomicCounter();
   
    
    return 0;
}
