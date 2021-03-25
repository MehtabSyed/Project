//
//  main.cpp
//  CircularQ
//
//  Created by Mehtab Ali Syed (CS) on 13/03/21.
//  Copyright © 2021 Mehtab Ali Syed (CS). All rights reserved.
//

#include <iostream>
#include <vector>
using namespace std;

template<typename T>
class CircularQ;

template<typename T>
class CircularQ_Iterator
{
public:
    CircularQ_Iterator(CircularQ<T> const & q,int const pos,bool const last):
    cq(q),index(pos),last_(last) {}
    
    CircularQ_Iterator & operator++()
    {
        if(last_)
            throw "Passed the end operator";
        index = (index + 1) % cq.len;
        last_ = (index == cq.next_pos());
        return *this;
    }
    CircularQ_Iterator operator++(int)
    {
        auto tmp = this;
        ++(*this);
        return tmp;
    }
    bool operator ==(CircularQ_Iterator const & other)
    {
        return index == other.index && last_ ==other.last_;
    }
    bool operator !=(CircularQ_Iterator const & other)
    {
        return !(*this == other);
    }
    T const & operator*() const
    {
        return cq.data[index];
    }
    T const & operator->() const
    {
        return cq.data[index];
    }
    
    
private:
    CircularQ<T> const & cq;
    size_t index;
    bool last_;
    
};


template<typename T>
class CircularQ
{
    typedef CircularQ_Iterator<T>  const_iterator;
    std::vector<T> data;
    int front;
    //int back;
    int len;
    int curr;
public:
    CircularQ(size_t size):data(size),front(-1),len(size),curr(0){};
    void push(T value)
    {
        front = next_pos();
        
        if(curr < len)
            curr++;
        data[front] =value;
       
    };
    void pop()
    {
        if(empty())
            throw std::runtime_error("Empty buffer");
        
          //  auto pos = first_pos();
            curr--;
        
    }
    T getFront()
    {
        if(empty())
            throw std::out_of_range("Out of queue range");
        
        return data[first_pos()];
    }
    
    bool empty() const
    {
        return (curr==0);
    };
    bool isfull()
    {
        return (curr==len);
    }
    
    size_t size()
    {
        return curr;
    };
    int capacity()
    {
        return size();
    }
    void swap(CircularQ &q)
    {
        if(this != q)
        {
            std::swap(*this,q);
        }
        
    }
    
   const_iterator begin() const
    {
        return const_iterator(*this,first_pos(),empty());
    }
    
    const_iterator  end() const
    {
        return const_iterator(*this,next_pos(),true);
    }
    
    friend class CircularQ_Iterator<T>;
private:
    int next_pos() const noexcept {
         if(curr ==0)
             return 0;
        else
        {
            return (front+1)%  len;
        }
        
    }
    int first_pos() const noexcept
    {
        if(curr ==0)
            return 0;
        else
        {
            return (front + len -curr +1)% len;
        }
    }
};
template <typename T>
void print(CircularQ<T> & buf)
{
   for (auto & e : buf)
   {
      std::cout << e << ' ';
   }

   std::cout << std::endl;
}


class Iterator {
    
};
int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    CircularQ<int> q(5) ;
    for(int i : {1,5,6,7,8,9,10})
    {
        q.push(i);
    }
    print(q);
    assert(q.empty()==false);
    assert(q.size() ==5);
    assert(q.isfull()==true);
    std:: cout << "Front is" << q.getFront();
    while(q.size())
    {
        q.pop();
    }
    assert(q.empty()==true);
    try {
    std:: cout << "Front is" << q.getFront();
    }
    catch(std::exception& e )
    {
        cout << "Exception is " << e.what() <<endl;
    }
    return 0;
}
