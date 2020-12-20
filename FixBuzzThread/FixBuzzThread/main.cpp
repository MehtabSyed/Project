//
//  main.cpp
//  FixBuzzThread
//
//  Created by Mehtab Ali Syed (CS) on 20/12/20.
//  Copyright © 2020 Mehtab Ali Syed (CS). All rights reserved.
//

#include <iostream>
#include <thread>

using namespace std;
void PrintFuzz()
  {
      cout << "Fuzz" ;
  }
  void PrintBuzz()
  {
      cout << "Buzz" ;
  }
  void PrintFuzzBuzz()
  {
      cout << "FuzzBuzz" ;
  }
class FizzBuzz
{
    int n;
    int curr;
    condition_variable cv;
    mutex m;
public:
    FizzBuzz() =default;
    
    FizzBuzz(int n):n(n)
    {
        curr =1;
    }

  
    bool IsDivisible(int num ,int div)
    {
        if(num % 15 == 0 && div !=15)
        {
            return false;
        }
        
        if(num % div ==0)
            return true;
        else
            return false;
    }
    
    void DoWork(int div,function<void()> fn)
    {
        while(1)
        {
            unique_lock<mutex> lk(m);
            while(curr <=n && !IsDivisible(curr,div))
                cv.wait(lk);
            if(curr >n)
            {
                cv.notify_all();
                return;
            }
            fn();
            curr++;
            cv.notify_all();
        }
        
    }
    
    void DoWork(int div,function<void(int)> fn)
       {
           while(1)
           {
               unique_lock<mutex> lk(m);
               while(curr <=n && !IsDivisible(curr,div))
                   cv.wait(lk);
               if(curr >n)
               {
                   cv.notify_all();
                   return;
               }
               fn(curr);
               curr++;
               cv.notify_all();
           }
           
       }
    
    void fizz(function<void()> printFizz)
    {
        
        DoWork(3, printFizz);
        
    }
    
    void buzz(function<void()> printBuzz)
    {
        DoWork(5, printBuzz);
        
    }
    
    void fizzbuzz(function<void()> printFizzBuzz)
    {
        DoWork(15, printFizzBuzz);
    }

    void nmuber(function<void(int)> printNumber)
    {
        while(curr <= n)
        {
            if(!IsDivisible(curr,3) && !IsDivisible(curr, 5))
            {
                DoWork(curr,printNumber);
            }else{
                DoWork(curr-1, printNumber);
            }
        }
    }
    
    
    
};

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    int i = 15;
    FizzBuzz fizzbuzz(i);
    thread fizz(&FizzBuzz::fizz,fizzbuzz,PrintFuzz);
      thread buzz(&FizzBuzz::buzz,fizzbuzz,PrintFuzz);
    thread fizzBuzz(&FizzBuzz::fizzbuzz,fizzbuzz,PrintFuzzBuzz);
    
    fizz.join();
    buzz.join();
    fizzBuzz.join();
    
    return 0;
}
