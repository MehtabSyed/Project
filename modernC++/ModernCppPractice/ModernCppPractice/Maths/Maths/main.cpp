//
//  main.cpp
//  Maths
//
//  Created by Mehtab Ali Syed (CS) on 07/02/21.
//  Copyright © 2021 Mehtab Ali Syed (CS). All rights reserved.
//

#include <iostream>
#include "vector"
#include <numeric>
#include <cmath>

using namespace std;

int find_abundant_number(int num)
{
    vector<int> divisors,ret;
    int sum=0;
    for(int i =2; i <= sqrt(num);++i)
    {
        
        if((num % i)==0) {
            sum+=(i==(num/i))  ? (i): i +num/i;
            //divisors.push_back(i);
        }
    }
   
    
    return sum;
    
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Enter a number\n";
    int num;
    cin >> num;
   // for(auto i=1; i<  num;++i)
    {
        
        auto sum = find_abundant_number(num);
        if(sum > num)
            
        {
            cout << "Num :" << num << "Abundance " << sum -num << endl;
        }
        
    }
    
    return 0;
}
