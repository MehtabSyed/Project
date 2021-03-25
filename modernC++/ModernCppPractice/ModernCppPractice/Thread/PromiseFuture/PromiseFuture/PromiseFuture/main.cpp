//
//  main.cpp
//  PromiseFuture
//
//  Created by Mehtab Ali Syed (CS) on 04/03/21.
//  Copyright © 2021 Mehtab Ali Syed (CS). All rights reserved.
//

#include <iostream>
#include <future>
#include <mutex>
#include <chrono>
using namespace std;


// Promise and future is used the set the value returned from a function , you cannot call it in a loop

void produce_value(std::promise<int>& p)
{
    int i =0;
 //   while(i <3)
    {
    {
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(2s);
    }
    try {
        throw runtime_error("An error has occurred");
        p.set_value(i++);
        cout << "Setting the value \n";
        }
        catch(...)
        {
            p.set_exception(std::current_exception());
        }
    }
}

void consume_value(std::future<int>& f)
{
    int i =0;
   // while(i <3)
    try
    {
        auto value = f.get();
    
        cout << "Value is " << value << endl;
        i = value;
    }
    catch(exception const & e)
    {
        cout << e.what() << endl;
        
    }
}
mutex g_mutex;
void do_something()
{
    {
        using namespace chrono_literals;
        this_thread::sleep_for(3s);
    }
    lock_guard<mutex> lk(g_mutex);
    cout << "Operation 1 done " << endl;
}
void do_something_else()
{
    {
        using namespace chrono_literals;
        this_thread::sleep_for(1s);
    }
    lock_guard<mutex> lk(g_mutex);
    cout << "Operation 2 done " << endl;
}

int compute()
{
    {
        using namespace chrono_literals;
        this_thread::sleep_for(1s);
        
    }
    return 42;
}

int compute_2()
{
    {
        using namespace chrono_literals;
        this_thread::sleep_for(3s);
    }
    return 22;
}


int main(int argc, const char * argv[]) {
    // insert code here...
    cout << __cplusplus << endl;
    auto d = std::async(launch::async, compute_2);
    
    auto value =compute_2();
    
    value += d.get();
    
    cout << "Value after computation is " << value << endl;
    
    
   auto f = std::async(launch::async,do_something);
   // auto f1 = std::async(std::launch::async,
     //                    [](){ do_something();});
    do_something_else();
    
    
#if Promise
    promise<int>   p;
    
      future<int> f= p.get_future();
    thread t1(produce_value,std::ref(p));
    
    std::cout << "Hello, World!\n";
    
    thread t2(consume_value,std::ref(f));
    
    t1.join();
    t2.join();
#endif
    return 0;
}
