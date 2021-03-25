
#include <iostream>
#include <future>
#include <mutex>
using namespace std;


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
    cout << "Operation 1 done " << endl;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    cout << __cplusplus << endl;
   auto f = std::async(launch::async,do_something());
    do_something_else();
    f.wait();
    
}