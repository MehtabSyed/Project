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
      cout << "Fuzz " ;
  }
  void PrintBuzz()
  {
      cout << "Buzz " ;
  }
  void PrintFuzzBuzz()
  {
      cout << "FuzzBuzz " ;
  }

void printNumber( int n)
{
    cout << n << " ";
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

     void fizz(function<void()> printFizz)
    {
        while(1)
        {
             unique_lock<mutex> lk(m);
         while(curr <=n &&
               (curr % 3 !=0 || (curr %15 ==0 )))
                cv.wait(lk);
            if(curr > n) {
                 cv.notify_all();
                return;
             }
            printFizz();
            curr++;
        
        
        cv.notify_all();
        }
    }

    // printBuzz() outputs "buzz".
    void buzz(function<void()> printBuzz) {
        while(1)
        {
             unique_lock<mutex> lk(m);
            while(curr <=n && ((curr % 5 !=0) || curr %15==0))
                cv.wait(lk);
            if(curr > n) {
                 cv.notify_all();
                return;
             }
        
            printBuzz();
            curr++;
             
            cv.notify_all();
        }
    }

      void fizzbuzz(function<void()> printFizzBuzz) {
        while(1)
        {
            unique_lock<mutex> lk(m);
            while(curr <=n && (curr % 15 !=0))
                cv.wait(lk);
              if(curr > n) {
                 cv.notify_all();
                return;
              }
            printFizzBuzz();
            curr++;
            
        
        
            cv.notify_all();
        }
        
    }

    // printNumber(x) outputs "x", where x is an integer.
    void number(function<void(int)> printNumber) {
        while(1)
        {
             unique_lock<mutex> lk(m);
            while(curr <=n && (curr % 3 ==0 || curr % 5 ==0))
                cv.wait(lk);
             if(curr > n) {
                 cv.notify_all();
                return;
             }
            printNumber(curr);
            curr++;
             
            
            cv.notify_all();
         }
        
    }
    
    
    
};

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    int i = 15;
    FizzBuzz* fizzbuzz =new FizzBuzz(i);
    thread fizz(&FizzBuzz::fizz,fizzbuzz,PrintFuzz);
      thread buzz(&FizzBuzz::buzz,fizzbuzz,PrintBuzz);
    thread fizzBuzz(&FizzBuzz::fizzbuzz,fizzbuzz,PrintFuzzBuzz);
    thread number(&FizzBuzz::number,fizzbuzz,printNumber);
    
    fizz.join();
    buzz.join();
    fizzBuzz.join();
    number.join();
    
    return 0;
}
