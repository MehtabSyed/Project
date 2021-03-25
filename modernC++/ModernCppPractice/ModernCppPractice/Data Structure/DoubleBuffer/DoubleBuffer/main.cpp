//
//  main.cpp
//  DoubleBuffer
//
//  Created by Mehtab Ali Syed (CS) on 16/03/21.
//  Copyright © 2021 Mehtab Ali Syed (CS). All rights reserved.
//

#include <iostream>
#include <vector>
#include <thread>
#include <iterator>
#include <mutex>
using namespace std;
#if 0
class DoubleBuffer1
{
public:
    void ReadBuffer(string& buffer)
    {
        
        buffer = m_buffer[index];
        
        
    }
    void WriteBuffer(string& buffer)
    {
        m_buffer[!index] = buffer;
        index = !index;
    }
    DoubleBuffer1():index(1),m_buffer(2) {
        
    }
    
private:
    vector<string> m_buffer;
    atomic<int> index;
};
#endif

template<typename T>
class DoubleBuffer
{
    typedef T value_type;
    typedef T& reference;
    typedef T const & const_reference;
    typedef T*  pointer;
    DoubleBuffer() = delete ;
public:
    explicit DoubleBuffer(size_t size):readbuf(size),writebuf(size){}
    
    template<class Output>
    void ReadBuffer(Output  it)
    {
       // std::unique_lock<std::mutex> lock(m);
        std::unique_lock<mutex> lock2(m);
        //unique_lock<std::mutex> lock(m);
        std::copy(std::cbegin(readbuf),std::cend(readbuf),it);
    };
    void WriteBuffer(T const* const ptr, size_t const size)
    {
        std::unique_lock<std::mutex> lock(m);
        std::copy(ptr,ptr + size,std::begin(writebuf));
        writebuf.swap(readbuf);
    }
    pointer data() const
    {
        std::unique_lock<std::mutex> lock(m);
        return readbuf.data();
    }
    reference operator[](size_t const pos) const
    {
        return readbuf[pos];
    }
    const_reference operator[](size_t const pos)
    {
        return readbuf[pos];
    }
    
    
   void swap(DoubleBuffer<T> & other)
    {
        std::swap(readbuf, other.readbuf);
        std::swap(writebuf,other.writebuf);
    }
    
   
private:
    std::mutex m;
    vector<T>   readbuf;
    vector<T>    writebuf;
};

template<typename T>
void print_buffer(DoubleBuffer<T>& buff) 
{
    buff.ReadBuffer(std::ostream_iterator<T>(cout," "));
    
    //buff.ReadBuffer(std::ostream_iterator<T>(std::cout," "));
    cout << endl;
}


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    DoubleBuffer<int> db(10);
   
    //fill_n(buff.begin(), 10, '5');
   // string buff(5,'-');
    std::thread t([&db]()
    {
        for(int i = 0 ; i < 1000;++i)
        {
            int data[]= {i, i +1,i +2,i+3,i+4,i + 5, i + 6,i + 7,i + 8,i + 9};

            db.WriteBuffer(data, 10);
        
            using namespace chrono_literals;
            this_thread::sleep_for(100ms);
            
        }
    });
    
    auto start = std::chrono::system_clock::now();
    do {
        print_buffer(db);
        //auto x= ;
    }while(chrono::duration_cast<chrono::seconds>(chrono::system_clock::now() - start).count()< 100);
    //}while (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - start).count() < 12);
    t.join();
    return 0;
}
