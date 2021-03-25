//
//  main.cpp
//  PriorityQueue
//
//  Created by Mehtab Ali Syed (CS) on 10/03/21.
//  Copyright © 2021 Mehtab Ali Syed (CS). All rights reserved.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

template<typename T>
struct Comparator
{
    bool operator()(const T& p1, const  T & p2)
    {
        return (p1 < p2 );
        
    }
};
//template<typename T,class Compare =less<T>> //typename vector<T>::value_type>>
template<typename T,typename Compare =less<typename vector<T>::value_type>>
class PriorityQ {

    vector<T> heap;
    Compare comparer;
    
public:
    PriorityQ()=default;
    void push(const T & elem);
    void pop();
    T & top();
    size_t size() const noexcept;
    bool empty() const noexcept;
    void print() const noexcept;
    void swap(PriorityQ& other) noexcept
    {
        std::swap(heap,other.heap);
        std::swap(comparer,other.comparer);
    }
    
    
};
template<typename T,class Comp>
void swap(PriorityQ<T,Comp> &q1,PriorityQ<T,Comp> &q2 )
noexcept(noexcept(q1.swap(q2)))
{
    q1.swap(q2);
}
template<typename T,class Comp>
void PriorityQ<T,Comp>::print() const noexcept
{
    copy(heap.begin(),heap.end(),ostream_iterator<T>(cout," "));
    cout << endl;
}
template<typename T,class Comp>
bool PriorityQ<T,Comp>::empty() const noexcept
{
    return heap.empty();
}
template<typename T,class Comp>
size_t PriorityQ<T,Comp>::size() const noexcept
{
    return heap.size();
}

template<typename T,class Comp>
void PriorityQ<T,Comp>::push(const T & elem)
{
    heap.push_back(elem);
    push_heap(heap.begin(),heap.end(),comparer);
    
}

template<typename T,class Comp>
void PriorityQ<T,Comp>::pop()
{
    if(!heap.empty()) {
        pop_heap(heap.begin(),heap.end(),comparer);
        heap.pop_back();
        
    }
}
template<typename T,class Comp>
T& PriorityQ<T,Comp>::top()
{
    if(heap.empty()) {
        throw "Heap is emppty";
    
    }
    return heap.front();
}
  

int main(int argc, const char * argv[]) {
    
    PriorityQ<int,Comparator<int>> q,q2;
    
    for(int i : {1,3,5})
    {
        q2.push(i);
    }
    
    
    for(int i=0; i < 10 ;++i)
        q.push(i);
    // insert code here...
    q.print();
    
    q.pop();
    q.pop();
    cout << "Top of q is " << q.top() << endl;
    q.print();
    swap(q2,q);
    q.print();
    std::cout << "Hello, World!\n";
    return 0;
}

