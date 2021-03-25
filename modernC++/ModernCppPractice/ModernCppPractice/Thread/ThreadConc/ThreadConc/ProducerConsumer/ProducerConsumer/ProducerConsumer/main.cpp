//
//  main.cpp
//  ProducerConsumer
//
//  Created by Mehtab Ali Syed (CS) on 03/03/21.
//  Copyright © 2021 Mehtab Ali Syed (CS). All rights reserved.
//

#include <iostream>
#include <mutex>
#include <condition_variable>
#include <thread>
using namespace std;
class Data
{
public:
    mutex m;
    condition_variable cv;
    int data;
    
};

auto  Producer= ([](Data &d)-> void
{
    while(d.data < 5)
    {
    {
        using namespace chrono_literals;
        this_thread::sleep_for(2s);
        
    }
    {
        unique_lock<mutex> lock(d.m);
        d.data++ ;
                cout << "Producing data " << d.data <<endl;
    }
    d.cv.notify_one();
    }
});

auto  Consumer= ([](Data &d)-> void
{
    while(d.data <5)
    {
    unique_lock<mutex> lk(d.m);
    d.cv.wait(lk);
                
    cout << "Consuming data " << d.data << endl;
    }
});


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
                Data d;
                d.data =0;
                
                 thread p(Producer,std::ref(d));
                 thread c (Consumer,std::ref(d));
                
    p.join();
    c.join();
    return 0;
}
