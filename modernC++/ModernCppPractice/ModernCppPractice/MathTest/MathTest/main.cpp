//
//  main.cpp
//  MathTest
//
//  Created by Mehtab Ali Syed (CS) on 02/02/21.
//  Copyright © 2021 Mehtab Ali Syed (CS). All rights reserved.
//

#include <iostream>
#include <numeric>
#include <vector>
#include <algorithm>
#include <map>
//#include "mathLib.hpp"
using namespace std;
int gcd2(int num1 ,int num2)
{
    while(num2!=0)
    {
        int r = num1 % num2;
         num1 = num2;
        num2 = r;
       
    }
    
    return num1;
    
}
/*
How is works
(1, 5
 gcd = 1
 5 ,6
 30
 8
 60
 */
int lcm2(int const x,int const y)
{
    int h = gcd2(x,y);
    return (x*(y/h));
    
}
template <class InputIt>
 int lcm(InputIt x,InputIt y)
 {
     
     return accumulate(x, y, 1,lcm2);
     
   
 }
/*
 if even sub 1
from given num till 3
{
    check if its divisble from an odd sum till num/2 return false_type
    else true
        
   
}
 */
int is_prime(int num)
{
    if(num ==1 || num ==2 || num ==3)
        return true;
    if(!(num &1))
        num--;
    if((num %3)==0)
        return 0;
    for(int i=num;i >= 3;i=-2)
    {
        bool found =false;
        for(int j=3;j*j <i;j+=6)
            if((i %j)==0 || (i%(j+2))==0) {
                found =true;
                break;
                
            }
        if(!found)
            return i;
               
    }
        
    return 0;
}
/*
 5. Sexy prime pairs Write a program that prints all the sexy prime pairs up to a limit entered by the user.


 */
using vvec =vector<vector<int>> ;

vvec sexy_pair(int limit)
{
   // check if its num is prime check if its sexy pair is fine
    //    add to list
    //    inc number by 6
        map<int,int> last_primes = {{1,0},{2,0},{3,0}};
        vvec ret;
        for(int i=5; i < limit; i+=2)
        {
            if(is_prime(i))
            {
                // is pair present ?
                
                auto itr = last_primes.find(i-6);
                if(itr!= last_primes.end())
                {
                    //if there add it .
                  //  vector<int> v ={i,itr->first};
                    
                    ret.push_back({i,itr->first});
                    
                }
                last_primes.insert_or_assign(itr, i ,0);
            }
        }
    
    return ret;


}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
//    cout <<"Check is num prime" << is_prime(11) << endl;
    cout << "Sexy primes are " << endl;
    vvec ret = sexy_pair(20);
    for(auto& v: ret )
    {
        cout << v[0] << "  " << v[1] << endl;
    }
    
    cout <<"Check is num prime" << is_prime(44) << endl;
    
    vector<double> v = { 5,6,8};
    cout << "LCM is " << lcm(begin(v),end(v)) << endl;
    cout << "Gcd is " << gcd2(6,8) << endl;
    return 0;
}
