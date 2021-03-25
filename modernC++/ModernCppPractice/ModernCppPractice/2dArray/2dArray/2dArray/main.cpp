//
//  main.cpp
//  2dArray
//
//  Created by Mehtab Ali Syed (CS) on 08/02/21.
//  Copyright © 2021 Mehtab Ali Syed (CS). All rights reserved.
//

#include <iostream>
#include <vector>
#include "iterator"

template<typename T,size_t a,size_t b>
class Array2d
{
   //  int row;
   //   int col;
    std::vector<T> data;
    //array<T> data(x*y);
    size_t rSize=a;
    size_t cSize= b;
    size_t Size;
   
  
public:
    Array2d():data(a*b),rSize(a),cSize(b),Size(a*b) {}
    //Array2d(int r,int c):data(r*c),rSize(r),cSize(c),Size(r*c) {}
    
    explicit Array2d(std::initializer_list<T> l):rSize(a),cSize(b),Size(a*b),data(l) {};
    
    
   constexpr T const& get(int x ,int y) const {
    
        if(x < rSize && y < cSize)
            return data[x*cSize+y];
        throw std::out_of_range("index out of range");
    }
    
   constexpr T const& get(int index) const
    {
        
        if(index < Size)
            return data[index];
        
         throw std::out_of_range("index out of range");
        
    }
    void fill(T val)
      {
          std::fill(begin(data),end(data),val);
      }
    Array2d  & swap(Array2d& other)
    {
        data.swap(other.data);
      //  std::swap(data,other.data);
        return *this;
    }
    
   void set(int x ,int y,T val) {
       
          if(x < rSize && y < cSize)
                data[x*cSize +y] =val;
        else
        
            throw std::out_of_range("index out of range");
    }
    size_t GetSize() const
    {
        return Size;
    }

    
};
template<typename T, typename C,size_t const Size>
class dummy_array_iterator_type
{
public:
    dummy_array_iterator_type(C& collection, size_t const index):collection(collection),index(index){}
    bool operator !=(dummy_array_iterator_type const & other)
    {
        return index != other.index;
    }
    T const& operator*()
    {
        return collection.get(index);
    }
    
  
    
    dummy_array_iterator_type& operator++()
    {
       // if(index <=Size)
            index++;
            
        return *this;
    }
    
private:
    C& collection;
    size_t index;
    size_t cindex;
    
};
template <typename T,size_t const Size>
using dummy_array_iterator = dummy_array_iterator_type<T, Array2d<T, Size, Size>, Size>;

template<typename T,size_t const Size>
inline dummy_array_iterator<T,Size> begin(Array2d<T, Size, Size> & collection)
{
    return dummy_array_iterator<T,Size>(collection,0);
}

template<typename T ,size_t const Size>
inline dummy_array_iterator<T,Size> end(Array2d<T, Size, Size> & collection)
{
    return dummy_array_iterator<T, Size>(collection,collection.GetSize());
}

int main(int argc, const char * argv[]) {
    
  //  Array2d<int,2,2> arr(2,2);
    Array2d<int,2,2> arr{1,2,3,4};
 
    /*
    arr.set(0, 0, 1);
    arr.set(0,1,2);
    arr.set(1,0,3);
    arr.set(1,1,4);
    */
    
    for(auto&& itr :arr)
    {
        std::cout << itr << std::endl;
    }
    
    for(auto itr = begin(arr); itr!= end(arr);++itr)
    {
        std::cout << *itr << std::endl;
    }
    Array2d<int,2,2> arr1;
    arr1.fill(2);
    
    arr.swap(arr1);
    std::copy(begin(arr),end(arr),std::ostream_iterator<int>(std::cout," "));
    
    Array2d<int, 2, 2> arr3 = std::move(arr1);
    std::copy(begin(arr3),end(arr3),std::ostream_iterator<int>(std::cout, ","));
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
